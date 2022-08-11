#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
unsigned int Num=0;
class Robot
{
private :
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
    public:
Robot():rent(0),isrented(false),day(0),month(0),year(0)      // At first, Every robot never been rented
{

}

~Robot()
{

}

void add_robot()                                             // The method to add robots from the user
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

void add_robot(string name_,unsigned int id_,unsigned int price_,string func_)       // The method to add robots from the programmer
{
    name = name_;
    id = id_;
    price = price_;
    func = func_;
    Num++;
}

void display_robots(Robot R[])                                                       // The method to display all robots
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

void robot_rent(Robot R[])                                                                       // the method to rent a robot
{
    display_robots(R);                                                                                  // First, display robots to user
    cout << "Choose robot ID\n";
    unsigned int id_;
    cin >> id_;
    for(int i=0;i<Num;i++)
        if(id_==R[i].id)                                                                        // enter the informations to rent it
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

void robot_search(Robot R[])                                                                         // The method to search for robot by its name by the user
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

void robot_search(Robot R[],string name_)                                                            // The method to search for a robot by its name by the programmer
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
};

unsigned int Num1=0;
class User:private Robot
{
private:
     string name;
        string mail;
        string phone;
        vector <int> rent;
    public:
User()
{

}

~User()
{

}

void add_user()                                                                   // The method to add a user by the user
{
    cout << "Enter the name: ";
    cin >> name;
    cout << "Enter the phone number: ";
    cin >> phone;
    cout << "Enter the E-mail: ";
    cin >> mail;
    Num1++;                                                                             // if you add a user, increment the number of users
}

void add_user(string name_,string phone_,string mail_)                               // The method to add a user by the programmer
{
    name = name_;
    phone = phone_;
    mail = mail_;
    Num1++;
}

void display_users(User U[])                                                          // The method to display all users
{
    cout << "Number of users = " << Num << endl;
    cout << "Name\t\tTelephone\t\tE-Mail\t\tRented robots\n";

    for(int i=0;i<Num1;i++)
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

void user_search(User U[])                                                                // The method to search for a user by name by the user
{
    string name_;
    cout << "Enter the name: ";
    cin >> name_;
    for(int i=0;i<Num1;i++)
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

void user_search(User U[],string name_)                                                 // The method to search for a user by his name by the programmer
{
    for(int i=0;i<Num1;i++)
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

void user_rent(User U[],Robot R[])                                                          // The method to rent a robot for a user
{
    display_users(U);                                                                              // display users to select which one will rent
    cout << "Choose user (name) to rent a robot: ";
    string name_;
    cin >> name_;
    unsigned int id_;
    Robot::robot_rent(R);                                                                           // Renting him the robot by ID
    cout << "Re-Enter the ID to confirm the process: ";
    cin >> id_;
    for(int i=0;i<Num1;i++)
        if(!(name_.compare(U[i].name)))
        {
            U[i].rent.push_back(id_);
            cout << "Robot " << id_ << " rented successfully to " << name_ << endl;
        }
}
};

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




