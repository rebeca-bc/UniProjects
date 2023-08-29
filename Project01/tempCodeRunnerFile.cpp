#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include "Log.h"

using namespace std;

int main()
{
    //create vector in which to read 
    vector<LogObject> logs;

    //create input and output file 
    ifstream input("log.txt");
    ofstream output("log_sorted.txt");

    if(! input.is_open())
    {
        cout<<"Error loading and opening input file";
        return 1;
    }

    if(! output.is_open())
    {
        cout<<"Error loading and opening output file";
        return 1;
    }

    //create variable to read into 
    string line;
    //create a temporrary variable to read into and then save into vector
    LogObject temp{};

    //start reading the file
    while (getline(input, line))
    {
        //create char arrays to save the strings and then pass them to the actual struct values. 
        char month[3], ip[13], message[50];

        //depending on what's read save into a part of our structs inside the vector
        // out reading format is string, int, int, int, int, int, string, string till you reach the endl;

        sscanf(line.c_str(), "%s %d %d %d:%d:%d %s %[^\n]", month, &temp.day, &temp.year, &temp.hour, &temp.minutes, &temp.seconds, ip, message);
        
        //change back to strings
        temp.month = string(month);
        temp.ip = string(ip);
        temp.message = string(message);

        //add temp to the vector
        logs.push_back(temp);
    }

    // initialize int for the answer & ask for the type of sorting
    string answer;

    cout<<"With which method do you want to cronologically sort your data"<<endl<<"a) merge sort"<<endl<<"b) quick sort"<<endl;
    cin>> answer;

    if(answer == "a" || answer == "merge sort" || answer == "merge" || answer == "Merge sort")
    {
        mergeSort(logs, 0, logs.size()-1);
    }

    for(const LogObject& log:logs)
    {
        output<<log.month<< " " <<log.day<< " " <<log.year<< " ";
        output<<log.hour<<":"<<log.minutes<<":"<<log.seconds<< " ";
        output<<log.ip<< " "<<log.message<<endl;
    }

    //close files to avoid leaks
    input.close();
    output.close();

    return 0;
}
