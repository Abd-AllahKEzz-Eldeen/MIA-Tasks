#include "Robot.h"
#include <iostream>
#include <ctime>
using namespace std;
unsigned int Num=0;
Robot::Robot():rent(0),isrented(false),day(0),month(0),year(0)      // At first, Every robot never been rented
{

}

Robot::~Robot()
{

}

void Robot::add_robot()                                             // The method to add robots from the user
{
    cout << "Enter the name: ";
    cin >> name;
    cout << "Enter the ID: ";
    cin >> id;
    cout << "Enter the price: ";
    cin >> price;
    cout << "Enter the function: ";
    cin >> func;
    Num++;                                                              // if you add a robot, increment the number of robots
}

void Robot::add_robot(string name_,unsigned int id_,unsigned int price_,string func_)       // The method to add robots from the programmer
{
    name = name_;
    id = id_;
    price = price_;
    func = func_;
    Num++;
}

void Robot::display_robots(Robot R[])                                                       // The method to display all robots
{
    time_t t=time(NULL);                                                                    // To determine the date of today
    tm *tptr=localtime(&t);
    cout << "Number of robots = " << Num << endl;
    cout << "Name\t\tID\t\tPrice\t\tFunction\t\tRented days\t\tAvailability\n";
    for(int i=0;i<Num;i++)
    {
        cout << R[i].name << "\t\t";
        cout << R[i].id << "\t\t";
        cout << R[i].price << "\t\t";
        cout << R[i].func << "\t\t";
        cout << R[i].rent << "\t\t\t";

        unsigned int M=R[i].month,D=R[i].day+R[i].duration;           // comparing the duration + the day robot has been rented on with today to determine if the robot is available again or not
        if(R[i].isrented)                                             // if the duration+ the day robot has been rented on greater than the month days, So, flip the month
        {
        if((D>31)&&((R[i].month==1)||(R[i].month==3)||(R[i].month)==5||(R[i].month==7)||(R[i].month==8)||(R[i].month==10)||(R[i].month==12)))
            {
                M++;
                D-=31;
            }
        else if((D>30)&&((R[i].month==4)||(R[i].month==6)||(R[i].month==9)||(R[i].month==11)))
            {
                M++;
                D-=30;
            }
        else if((D>28)&&(R[i].month==2))
            {
                M++;
                D-=28;
            }
        }


        if((R[i].isrented)&&((tptr->tm_mday<D)||((tptr->tm_mday>D)&&(((tptr->tm_mon)+1)!=M))))          // if the day hasn't come yet,so it's not available
                cout << "Not available\n";
            else                                                                                        // else it's available
            {
                R[i].isrented=false;
                cout << "Available\n";
                R[i].day=0;
                R[i].month=0;
                R[i].year=0;
            }

    }
}

void Robot::robot_rent(Robot R[])                                                                       // the method to rent a robot
{
    display_robots(R);                                                                                  // First, display robots to user
    cout << "Choose robot ID\n";
    unsigned int id_;
    cin >> id_;
    for(int i=0;i<Num;i++)
        if(id_==R[i].id)                                                                                // enter the informations to rent it
            {
                R[i].isrented=true;
                R[i].rent++;
                cout << "Day of renting in form Day/Month/Year\n";
                scanf("%d/%d/%d",&R[i].day,&R[i].month,&R[i].year);
                cout << "How many days would you rent this robot? ";
                cin >> R[i].duration;
                break;
            }

}

void Robot::robot_search(Robot R[])                                                                         // The method to search for robot by its name by the user
{
    string name_;
    cout << "Enter the name: ";
    cin >> name_;
    for(int i=0;i<Num;i++)
        if(!(name_.compare(R[i].name)))                                                                     // if the robot exist, display its informations
        {
            cout << "Name: " << R[i].name << endl;
            cout << "ID: " << R[i].id << endl;
            cout << "Price: " << R[i].price << endl;
            cout << "Function: " << R[i].func << endl;
            cout << "Days have been rented: " << R[i].rent << endl;
            if(R[i].isrented)
                cout << "Availability : Not available\n";
            else
                cout << "Availability : Available\n";
        }
}

void Robot::robot_search(Robot R[],string name_)                                                            // The method to search for a robot by its name by the programmer
{
    for(int i=0;i<Num;i++)
        if(!(name_.compare(R[i].name)))
        {
            cout << "Name: " << R[i].name << endl;
            cout << "ID: " << R[i].id << endl;
            cout << "Price: " << R[i].price << endl;
            cout << "Function: " << R[i].func << endl;
            cout << "Days have been rented: " << R[i].rent << endl;
            if(R[i].isrented)
                cout << "Availability : Not available\n";
            else
                cout << "Availability : Available\n";
        }

}

