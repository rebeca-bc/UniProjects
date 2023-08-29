#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include "Log.h"

using namespace std;

bool validateMonth(string &month);
bool validateDay(LogObject obj);
bool validateHour(int hour);
bool validateMinSec(int min_or_sec);
bool leapYear(int year);

int main()
{
    //create vector in which to read 
    vector<LogObject> logs;

    //create input and output file && check is possible
    ifstream input("log.txt");
    ofstream output("log_sorted.txt");
    if(!input.is_open() || !output.is_open()) 
    {
        cout << "Failed to open file!" << endl;
        return 1; 
    }

    // Variables para calcular el tiempo de ejecución
    chrono::high_resolution_clock::time_point begin;
    chrono::high_resolution_clock::time_point end;

    string line;
    LogObject temp;

    //start reading the file
    while (getline(input, line))
    {
        char month[4], ip[15], message[50];

        sscanf(linec_str(), "%s %d %d %d:%d:%d %s %[^\n]", month, &temp.day, &temp.year, &temp.hour, &temp.minutes, &temp.seconds, ip, message);
        
      //change back to strings
      temp.month = string(month);
      temp.ip = string(ip);
      temp.message = string(message);
      temp.key = getKey(temp);

      //add temp to the vector
      logs.push_back(temp);
    }

    // initialize int for the answer & ask for the type of sorting
    string answer;


    cout<<"With which method do you want to chronologically sort your data"<<endl<<"a) merge sort"<<endl<<"b) quick sort"<<endl;
    cin>> answer;

    if(answer == "a" || answer == "merge sort" || answer == "merge" || answer == "Merge sort")
    {
        startTime(begin);
        mergeSort(logs, 0, logs.size() - 1);
        getTime(begin, end);
    }
    else if(answer == "b" || answer == "quick sort" || answer == "quick" || answer == "Quick sort")
    {
        startTime(begin);
        quickSort(logs, 0, logs.size() - 1);
        getTime(begin, end);
    }

    //print the sorted result into an output file
    for(int i = 0; i < logs.size(); i++)
    {
       output<<logs[i].month<< " " <<logs[i].day<< " " <<logs[i].year<< " "<<logs[i].hour<<":"<<logs[i].minutes<<":"<<logs[i].seconds<< " "<<logs[i].ip<< " "<<logs[i].message<<endl;
    }

    int lower, upper;

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
        cout<<"Month: ";
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
            lower = binarySearch(logs, key, 'l');
        }
        else
        {
            //get highest spot
            upper = binarySearch(logs, key, 'u');
        }
    }

    //error if impossible range
    if(lower>upper)
    {
        cout<<"Your upper bound is smaller than your lower bound"<<endl;
        return 2;
    }

    cout<<"-----------------";
    for(int i = lower; i < upper; i++)
    {
        cout<<logs[i].month<< " " <<logs[i].day<< " " <<logs[i].year<< " "<<logs[i].hour<<":"<<logs[i].minutes<<":"<<logs[i].seconds<< " "<<logs[i].ip<< " "<<logs[i].message<<endl;
    }
    cout<<endl;

    //close files to avoid leaks
    input.close();
    output.close();

    return 0;
}

//functions to validate dates
bool validateMonth(string &m)
{
    m = m.substr(0,3);
    m[0] = toupper(m[0]);
    int num = monthToInt(m);

    if(num == 1 || num == 2 || num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9 || num  == 10 || num == 11 || num == 12)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool leapYear(int year)
{
    if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool validateDay(LogObject temp)
{
    if(temp.day <= 0 || temp.day > 31)
    {
        return false;
    }

    if (temp.month == "Feb")
    {
        if (leapYear(temp.year) && temp.day > 29)
        {
            return false;
        }
        else if(! leapYear(temp.year) && temp.day > 28)
        {
            return false;
        }
    }
    else if(temp.month == "Apr" || temp.month == "Jun" || temp.month == "Sep" || temp.month == "Nov" && temp.day > 30)
    {
        return false;
    }

    return true;
}

bool validateHour(int h)
{
    if(h > 23 || h < 0) 
    {
        return false;
    }
    return true;
}

bool validateMinSec(int m_or_s)
{
    if(m_or_s < 0 || m_or_s >= 60)
    {
        return false;
    }
    return true;
}


