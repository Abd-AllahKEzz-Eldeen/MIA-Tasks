#include "User.h"
#include "Robot.h"
#include <iostream>
using namespace std;
unsigned int Num=0;

User::User()
{

}

User::~User()
{

}

void User::add_user()                                                                   // The method to add a user by the user
{
    cout << "Enter the name: ";
    cin >> name;
    cout << "Enter the phone number: ";
    cin >> phone;
    cout << "Enter the E-mail: ";
    cin >> mail;
    Num++;                                                                             // if you add a user, increment the number of users
}

void User::add_user(string name_,string phone_,string mail_)                               // The method to add a user by the programmer
{
    name = name_;
    phone = phone_;
    mail = mail_;
    Num++;
}

void User::display_users(User U[])                                                          // The method to display all users
{
    cout << "Number of users = " << Num << endl;
    cout << "Name\t\tTelephone\t\tE-Mail\t\tRented robots\n";

    for(int i=0;i<Num;i++)
    {
        cout << U[i].name << "\t\t";
        cout << U[i].phone << "\t\t";
        cout << U[i].mail << "\t\t";
        if(!U[i].rent.size())                                                               // if the user didn't rent any robot before, print none
            cout << "None";
        else
            for(int j=0;j<U[i].rent.size();j++)                                             // else print the ids of the robot he has rented before
                cout << U[i].rent[j] << ",";
        cout << endl;
    }
}

void User::user_search(User U[])                                                                // The method to search for a user by name by the user
{
    string name_;
    cout << "Enter the name: ";
    cin >> name_;
    for(int i=0;i<Num;i++)
        if(!(name_.compare(U[i].name)))                                                          // if his name exist, display his informations
        {
            cout << "Name: " << U[i].name << endl;
            cout << "Telephone: " << U[i].phone << endl;
            cout << "E-Mail: " << U[i].mail << endl;
            cout << "Rented robots: ";
             if(U[i].rent.size()==0)
                cout << "None";
            else
                for(int j=0;j<U[i].rent.size();j++)
                    cout << U[i].rent[j] << ",";
            cout << endl;
        }
}

void User::user_search(User U[],string name_)                                                 // The method to search for a user by his name by the programmer
{
    for(int i=0;i<Num;i++)
        if(!(name_.compare(U[i].name)))
        {
            cout << "Name: " << U[i].name << endl;
            cout << "Telephone: " << U[i].phone << endl;
            cout << "E-Mail: " << U[i].mail << endl;
            cout << "Rented robots: ";
             if(U[i].rent.size()==0)
                cout << "None";
            else
                for(int j=0;j<U[i].rent.size();j++)
                    cout << U[i].rent[j] << ",";
            cout << endl;
        }
}

void User::user_rent(User U[],Robot R[])                                                          // The method to rent a robot for a user
{
    display_users(U);                                                                              // display users to select which one will rent
    cout << "Choose user (name) to rent a robot: ";
    string name_;
    cin >> name_;
    unsigned int id_;
    Robot::robot_rent(R);                                                                           // Renting him the robot by ID
    cout << "Re-Enter the ID to confirm the process: ";
    cin >> id_;
    for(int i=0;i<Num;i++)
        if(!(name_.compare(U[i].name)))
        {
            U[i].rent.push_back(id_);
            cout << "Robot " << id_ << " rented successfully to " << name_ << endl;
        }
}


