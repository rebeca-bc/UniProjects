//Rebeca Borrego Cavazos 542497 
//Declaro haber realizado esta actividad con integridad académica
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include "DoublyLinkedList.h"

using namespace std;

#include "DateValidation.h"

int main()
{

    //create doubly linked list
    DoublyLinkedList<LogObject> loglist;

    //create input and output file && check is possible
    ifstream input("log.txt");
    ofstream output("log_sorted.txt");
    if(!input.is_open() || !output.is_open()) 
    {
        cout << "Failed to open file!" << endl;
        return 1; 
    }

    //variables to read string line into and to save the log into
    string line;
    LogObject temp;

    //start reading the file
    while (getline(input, line))
    {
        char month[4], ip[15], message[50];

        sscanf(line.c_str(), "%s %d %d %d:%d:%d %s %[^\n]", month, &temp.day, &temp.year, &temp.hour, &temp.minutes, &temp.seconds, ip, message);
        
        //change back to strings and save into struct
        temp.month = string(month);
        temp.ip = string(ip);
        temp.message = string(message);
        temp.key = getKey(temp);

        //add temp to the doubly linked list
        loglist.addLast(temp);
    }

    //head & tail variables
    Node<LogObject>* head = loglist.getHead();
    Node<LogObject>* tail = loglist.getTail();    

    if(head == nullptr || tail == nullptr)
    {
        cout<<"List is empty"<<endl;
        return 2;
    }

    // initialize int for the answer & ask for the type of sorting
    string answer;
    cout<<"With which method do you want to chronologically sort your data"<<endl<<"a) merge sort"<<endl<<"b) quick sort"<<endl;
    cin>> answer;
    loglist.sort(loglist, head, tail, answer);
        
    //write the sorted result into an output file
    for(Node<LogObject>* i = head; i != nullptr; i = i->next)
    {
       output<<i->logObj.month<< " " <<i->logObj.day<< " " <<i->logObj.year<< " "<<i->logObj.hour<<":"<<i->logObj.minutes<<":"<<i->logObj.seconds<< " "<<i->logObj.ip<< " "<<i->logObj.message<<endl;
    }
    int lower, upper;

    //variables to find the lower and upper bounds of the range
    Node<LogObject>* lower_b = nullptr;
    Node<LogObject>* upper_b = nullptr;
    int size = loglist.getSize();

    //ask for the range of dates && validate all inputs 
    for(int i = 0; i < 2; i++)
    {
        if(i == 0)
        {
            cout<<endl<<"Start of date range: "<<endl;
        }
        else
        {
            cout<<endl<<"Finish of date range: "<<endl;
        }

        cout<<"Year: ";
        cin>>temp.year;
        cout<<"Month (written): ";
        cin>>temp.month;
        while(! validateMonth(temp.month))
        {
            cout<<"Month: ";
            cin>>temp.month;
        }

        cout<<"Day: ";
        cin>>temp.day;
        while(! validateDay(temp))
        {
            cout<<"Day: ";
            cin>>temp.day;
        }

        cout<<"Hour: ";
        cin>>temp.hour;
        while(! validateHour(temp.hour))
        {
            cout<<"Hour: ";
            cin>>temp.hour;
        }

        cout<<"Minutes: ";
        cin>>temp.minutes;
        while(! validateMinSec(temp.seconds))
        {
            cout<<"Minutes: ";
            cin>>temp.minutes;
        }

        cout<<"Seconds: ";
        cin>>temp.seconds;
        while(! validateMinSec(temp.seconds))
        {
            cout<<"Seconds: ";
            cin>>temp.seconds;
        }
        long int key = getKey(temp);
        
        if(i == 0)
        {
            //get the lower bound 
            lower_b = loglist.binarySearch(key);
        }
        else
        {
            //get the upper range 
            upper_b = loglist.binarySearch(key);
        }

    }

    //error if impossible range
    if(lower_b->logObj.key > upper_b->logObj.key)
    {
        cout<<"Your upper bound is smaller than your lower bound"<<endl;
        return 3;
    }

    //print from the lower to the upper boundary 
    cout<<"-----------------"<<endl;
    for(Node<LogObject>* i = lower_b; i != upper_b->next; i = i->next)
    {
        cout<<i->logObj.month<< " " <<i->logObj.day<< " " <<i->logObj.year<< " "<<i->logObj.hour<<":"<<i->logObj.minutes<<":"<<i->logObj.seconds<< " "<<i->logObj.ip<< " "<<i->logObj.message<<endl;
    }
    cout<<endl;

    ///close files to avoid leaks
    input.close();
    output.close();

    return 0;

}