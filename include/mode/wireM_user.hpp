//
// Created by 邦邦 on 2022/7/5.
//

#ifndef WM_WIREM_USER_HPP
#define WM_WIREM_USER_HPP
#include "mysql_orm/sql/dql.h"

class wireM_user:public bb::dql{
    wireM_user(){
        if(run_() != 0){
            bb::Log::obj().error("mode创建的时候出现问题");
        }
        update_();
    }
public:
    static wireM_user &obj(){
        static wireM_user wire_m_user;
        return wire_m_user;
    }
protected:
    int run_(){
        std::array<std::string,2> obj_info = getName_();
        DB_name_ = obj_info[0];
        table_name_ = obj_info[1];
        if(createDB(DB_name_) == 0 && useDB(DB_name_) == 0){
            if(isTable(table_name_) == 0){
                if(create_() != 0){return -1;}
            }
            return useTable(table_name_);
        }
        delTable();
        return 0;
    }
    int create_(){
        return createTable(table_name_,[](auto *data){
            data->int_("grade")->nullable_()->comment_("等级");
            data->int_("phone")->nullable_()->comment_("手机号");
            data->string_("email")->nullable_()->comment_("邮箱");
            data->string_("password")->nullable_()->comment_("密码");
            data->dateAt_();
        });
    }
    void update_(){
        //delDB_("db_a1");
    }
    void delTable_(const std::string &db_name={},const std::string &table_name={}){
        if(!db_name.empty()){
            DB_name_ = db_name;
        }
        if(!table_name.empty()){
            table_name_ = table_name;
        }
        useDB(DB_name_);
        delTable();
    }
    void delDB_(const std::string &db_name={}){
        if(!db_name.empty()){
            DB_name_ = db_name;
        }
        delDB(DB_name_);
    }
};

#endif //WM_WIREM_USER_HPP