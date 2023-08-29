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
    // Variables para calcular el tiempo de ejecución
    chrono::high_resolution_clock::time_point begin;
    chrono::high_resolution_clock::time_point end;

    //create doubly linked list
    DoublyLinkedList<LogObject> loglist;

    //create input and output file && check is possible
    ifstream input("log1.txt");
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

    // initialize int for the answer & ask for the type of sorting
    string answer;
    cout<<"With which method do you want to chronologically sort your data"<<endl<<"a) merge sort"<<endl<<"b) quick sort"<<endl;
    cin>> answer;

    //head & tail variables
    Node<LogObject>* head = loglist.getHead();
    Node<LogObject>* tail = loglist.getTail();    

    if(head == nullptr || tail == nullptr)
    {
        cout<<"List is empty"<<endl;
        return 2;
    }


    //call on the appropriate sort 
    if(answer == "a" || answer == "merge sort" || answer == "merge" || answer == "Merge sort")
    {
        startTime(begin);
        loglist.mergeSort(head);
        getTime(begin, end);
    }
    else if(answer == "b" || answer == "quick sort" || answer == "quick" || answer == "Quick sort")
    {
        startTime(begin);
        loglist.quickSort(head, tail);
        getTime(begin, end);
    }
    loglist.print();