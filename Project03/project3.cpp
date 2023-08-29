#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <set>
#include "HeapSort.h"
#include "BST.h"

using namespace std;

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

int main() 
{
    // Variables para calcular el tiempo de ejecución
    chrono::high_resolution_clock::time_point begin;
    chrono::high_resolution_clock::time_point end;

    vector<Record> mediterranean;
    vector<Record> redSea;
    TreeNode* ubiBST = nullptr;
    vector<Record>* listToOrder = nullptr;

    int choice;
    while (true) 
    {
        cout << "\n⊹˚₊‧────────────── Menu ──────────────‧₊˚⊹" << endl;
        cout << "1. Read file" << endl;
        cout << "2. Order both lists" << endl;
        cout << "3. Search for information" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "\n⊹˚₊‧──────────── Section 1 ────────────‧₊˚⊹" << endl;
                readRecords(mediterranean, redSea);
                cout << "Records read successfully!" << endl;
                break;
            
          
            case 2: 
            
                if (mediterranean.empty() && redSea.empty())
                {
                    cout << "No records found. Please read the file first." << endl;
                    break;
                }
                cout << "\n⊹˚₊‧──────────── Section 2 ────────────‧₊˚⊹" << endl;
                char listChoice;
                cout << "Which list do you want to order?"<<endl;
                cout<<"A: Mediterranean"<<endl<<"B: Red Sea "<<endl;
                cin >> listChoice;

                if (listChoice == 'M'||listChoice == 'a'||listChoice == 'a')
                {
                    listToOrder = &mediterranean;
                }
                else if (listChoice == 'R'||listChoice == 'B'||listChoice == 'b')
                {
                    listToOrder = &redSea;
                }
                else 
                {
                    cout << "Invalid list choice!" << endl;
                    break;
                }

                char orderChoice;
                cout << endl << "In which order do you want to sort?"<<endl;
                cout<<"A: Ascending"<<endl<<"B: Descending "<<endl;
                cin >> orderChoice;

                if (orderChoice == 'A' || orderChoice == 'a')
                {
                    startTime(begin);
                    heapSort(*listToOrder);
                    getTime(begin, end);
                }
                  
                else if (orderChoice == 'B' || orderChoice == 'b')
                {
                    startTime(begin);
                    heapSort(*listToOrder);
                    reverse(listToOrder->begin(), listToOrder->end());
                    getTime(begin, end);
                }

                else 
                {
                    cout << "Invalid order choice!" << endl;
                    break;
                }

                writeOrderedListToFile(*listToOrder);
              
                break;
            
          
            case 3: 
            
                if (mediterranean.empty() && redSea.empty()) 
                {
                    cout << "No records found. Please read the file first." << endl;
                    break;
                }

                cout << "\n⊹˚₊‧──────────── Section 3 ────────────‧₊˚⊹" << endl;
                if (!ubiBST)
                    buildBST(mediterranean, ubiBST);

                searchVessel(ubiBST);
                break;
            
          
            case 4:
            
                cout << endl << "⊹˚₊‧────────────────────────────────────‧₊˚⊹"<<endl<<"               Exiting Menu..." << endl << endl;
                return 0;
            
            
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
