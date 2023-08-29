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

template <typename T>
int binarySearch(vector<T> &array, long int value, char rangetype)
{
    int start = 0, end = array.size(), midp;

    while(start < end - 1)
    {
        midp = (start + end) / 2;
        if(array[midp].key < value)
        {
            start = midp;
        }
        else if(array[midp].key > value)
        {
            end = midp;
        }
        else if(array[midp].key == value)
        {
            if(rangetype == 'l')
            {
                while(array[midp].key == value)
                {
                    midp--;
                }

                return midp;
            }
            else
            {
                while(array[midp].key == value)
                {
                    midp++;
                }
            }
        }
    }

    if(value > array[end-1].key)
    {
        return end;
    }
    else if(value < array[0].key)
    {
        return start;
    }

    return midp;
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

template <typename T>
void merge(vector<T>& array, int l, int m, int r)
{
    //create and fill both subarrays
    vector<T> left(array.begin()+l, array.begin()+m+1);

    vector<T> right(array.begin()+m+1, array.begin()+r+1);

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size())
    {
        if (left[i].key < right[j].key)
        {
            array[k] = left[i];
            i++;
        }
        else
        {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left.size())
    {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < right.size())
    {
        array[k] = right[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(vector<T> &array, int l, int r)
{
    if(l<r)
    {
        int m = (l+r)/2;
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, m, r);
    }
}

template <typename T>
int pivotIndex(vector<T> &array, int start, int end)
{
    long int pivot = array[end].key;
    int index = start - 1;

    for(int i = start; i < end; i++)
    {
        if(array[i].key < pivot)
        {
            index++;
            swap(array[i], array[index]);
        }
    }

    index++;
    swap(array[end], array[index]);
  
    return index;
}

template <typename T>
void quickSort(vector<T> &array, int start, int end)
{
    if(start < end)
    {
        int pivot = pivotIndex(array, start, end);

        quickSort(array, start, pivot - 1);
        quickSort(array, pivot + 1, end);
    }
}
