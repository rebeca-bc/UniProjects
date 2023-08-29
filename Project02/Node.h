#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

struct LogObject
{
    string month;
    int day;
    int year;
    int hour;
    int minutes;
    int seconds;
    string ip, message;
    long int key;

};


template <typename T>
struct Node
{
    T logObj;
    Node<T>* next;
    Node<T>* previous;
    Node(T logObj, Node<T>* next, Node<T>* previous);
    Node(T logObj);
    Node(): logObj(), next(nullptr), previous(nullptr) {}
};

template <typename T>
Node<T>::Node(T logObj)
{
    this->logObj = logObj;
    this->next = nullptr;
    this->previous = nullptr;
}

template <typename T>
Node<T>::Node(T logObj, Node<T>* next, Node<T>* previous)
{
    this->logObj = logObj;
    this->next = next;
    this->previous = previous;
}

int monthToInt(string month) 
{
    if (month == "Jan") 
    {
        return 1;
    } else if (month == "Feb") 
    {
        return 2;        
    } else if (month == "Mar") 
    {
        return 3;        
    } else if (month == "Apr") 
    {
        return 4;        
    } else if (month == "May") 
    {
        return 5;        
    } else if (month == "Jun") 
    {
        return 6;        
    } else if (month == "Jul") 
    {
        return 7;        
    } else if (month == "Aug") 
    {
        return 8;        
    } else if (month == "Sep") 
    {
        return 9;        
    } else if (month == "Oct") 
    {
        return 10;        
    } else if (month == "Nov") 
    {
        return 11;        
    } else if (month == "Dec") 
    {
        return 12;
    }        
    return 14;
}

double getKey(LogObject object)
{
    int int_month = monthToInt(object.month);

    //create a string stream to save several ints. 
    ostringstream temp;
    temp << setfill('0') << setw(4) << object.year
         << setw(2) << int_month << setw(2) << object.day
         << setw(2) << object.hour << setw(2) << object.minutes
         << setw(2) << object.seconds;

    return stol(temp.str());

}

void startTime(chrono::high_resolution_clock::time_point &begin)
{
    // start time
    begin = std::chrono::high_resolution_clock::now();
}

void getTime(chrono::high_resolution_clock::time_point begin, chrono::high_resolution_clock::time_point end)
{
    end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Tiempo de ejecución: %.8f seconds.\n", elapsed.count() * 1e-9);
}

