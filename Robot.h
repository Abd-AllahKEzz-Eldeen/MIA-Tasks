#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>
using namespace std;

class Robot
{
    public:
        Robot();
        ~Robot();
        void display_robots(Robot R[]);
        void add_robot();
        void add_robot(string name_,unsigned int id_,unsigned int price_,string func_);
        void robot_search(Robot R[]);
        void robot_search(Robot R[],string name_);
        void robot_rent(Robot R[]);
    protected:

    private:
        string name;
        string func;
        unsigned int id;
        unsigned int rent;
        unsigned int price;
        bool isrented;
        unsigned int day;
        unsigned int month;
        unsigned int year;
        unsigned int duration;

};

#endif // ROBOT_H
