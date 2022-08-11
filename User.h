#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include "Robot.h"
using namespace std;

class User:private Robot
{
    public:
        User();
        ~User();
        void add_user();
        void add_user(string name_,string phone_,string mail_);
        void display_users(User U[]);
        void user_search(User U[]);
        void user_search(User U[],string name_);
        void user_rent(User U[],Robot R[]);

    protected:

    private:
        string name;
        string mail;
        string phone;
        vector <int> rent;
};

#endif // USER_H
