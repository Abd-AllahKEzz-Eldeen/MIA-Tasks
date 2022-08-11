#include <iostream>
using namespace std;
#include "Robot.h"
#include "User.h"
int main()
{
    Robot r[20];
    User u[100];
    r[0].add_robot("Alien",1,500,"Hairstylist");
    r[1].add_robot("Boom",2,350,"Cleaning");
    r[2].add_robot("CR7",3,700,"Footballing");
    u[0].add_user("Jack","01523156423","jack@haha.com");
    u[1].add_user("Morsi","01215623156","morsi@boom.com");
    u[2].add_user("Ram","01315624462","ram@love.com");
    unsigned int i=3,j=3;
    while(1)
    {

        unsigned int n;
        cout << "1- Add Robot\n";
        cout << "2- Add user\n";
        cout << "3- Display all users\n";
        cout << "4- Display all robots\n";
        cout << "5- Search for robot by name\n";
        cout << "6- Search for user by name\n";
        cout << "7- Rent robot to user\n";
        cout << "8- Exit\n";
        cin >> n;

        switch(n)
        {
        case 1:r[i].add_robot();i++;break;
        case 2:u[j].add_user();j++;break;
        case 3:u[j].display_users(u);break;
        case 4:r[i].display_robots(r);break;
        case 5:r[i].robot_search(r);break;
        case 6:u[j].user_search(u);break;
        case 7:u[j].user_rent(u,r);break;
        }
        if(n==8) break;
    }
}
