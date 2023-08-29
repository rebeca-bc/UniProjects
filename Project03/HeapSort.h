#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

//str5uct for the records of the vessels
struct Record 
{
    string date;
    string time;
    char entryPoint;
    string ubi;
};

void readRecords(vector<Record>& mediterranean, vector<Record>& redSea) 
{
    //open and revise the efectiveness
    ifstream inputFile("canalsuez.txt");
    if (!inputFile) 
    {
        cout << "Error opening the input file." << endl;
        return;
    }

    Record record;
    while (inputFile >> record.date >> record.time >> record.entryPoint >> record.ubi)
    {
        //save to respective vector
        if (record.entryPoint == 'M')
        {
            mediterranean.push_back(record);
        }
        else if (record.entryPoint == 'R')
        {
            redSea.push_back(record);
        }
    }

    inputFile.close();
}

void writeOrderedListToFile(const vector<Record>& orderedList) 
{
    //create file and see if it could be opened
    ofstream outputFile("ordered_list.txt");
    if (!outputFile) 
    {
        cout << "Error opening the output file." << endl;
        return;
    }

    //write to file to see the ordered list
    for (const auto& record : orderedList) 
    {
        outputFile << record.date << " " << record.time << " " << record.entryPoint << " " << record.ubi << endl;
    }

    outputFile.close();

    cout << endl << "Ordered list written in 'ordered_list.txt' successfully" << endl <<endl;
}


void displayRecords(const vector<Record>& records) 
{
    for (const auto& record : records) 
    {
        cout << record.date << " " << record.time << " " << record.entryPoint << " " << record.ubi << endl;
    }
}

bool sortByUBIDateTime(const Record& r1, const Record& r2) 
{
    // Check if the UBIs are different
    if (r1.ubi != r2.ubi)
    {
        // Sort by UBI in ascending order
        return r1.ubi < r2.ubi;
    }

    // Check if the dates are different
    if (r1.date != r2.date)
    {
        // Sort by date in ascending order
        return r1.date < r2.date;
    }

    // Sort by time in ascending order
    return r1.time < r2.time;
}


void heapify(vector<Record>& records, int n, int i) 
{
    int largest = i;

    //make childs of main node
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //check if child exists and if it is larger than root
    if (left < n && sortByUBIDateTime(records[left], records[largest]))
    {
        largest = left;
    }
    if (right < n && sortByUBIDateTime(records[right], records[largest]))
    {
        largest = right;
    }

    if (largest != i) 
    {
        //if the largest isnt the root then swap to make root largest
        swap(records[i], records[largest]);
        //recursively call to keep ordering and heapifying
        heapify(records, n, largest);
    }
}

void heapSort(vector<Record>& records) 
{
    int n = records.size();

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(records, n, i);
    }

    for (int i = n - 1; i > 0; i--) 
    {
        swap(records[0], records[i]);
        heapify(records, i, 0);
    }
}

#endif 