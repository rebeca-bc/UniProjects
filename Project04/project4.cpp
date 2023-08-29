//Rebeca Borrego Cavazos 542497 Declaro haber realizado esta actividad con integridad académica
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "Graph.h"
#include "HashTable.h"

using namespace std;

int main()
{
    string inputFile;
    cout<<"\n⊹˚₊‧─────────────── Hello ────────────────‧₊˚⊹"<<endl;

    //ask for the name of the file
    cout<<"Name of input file (with extension) :"<<endl;
    cin>>inputFile;

    //create input and output file && check if possible
    ifstream input(inputFile);

    if(!input.is_open())
    {
        cout<<"Error opening input file"<<endl;
        return 0;
    }

    //create vector for the vertices
    vector<string> vertexes;
    //create a vector for the whole file
    vector<string> file;

    //read the first line
    string firstLine, line;
    getline(input, firstLine);
    int numPaths = stoi(firstLine);

    //read the whole file into a vector
    while(getline(input, line))
    {
        file.push_back(line);
    }

    //get the number of vertexes 
    int numVertexes = stoi(file[numPaths]);

    //save vertexes into a vector
    for(int i = numPaths + 1; i < numVertexes + numPaths + 1; i++)
    {
        vertexes.push_back(file[i]);
    }

    //turn vector to hashtable
    vector<Node<string>*> hashT = HashTable(vertexes);

    //create the graph from the vertexes
    Graph<string> portGraph(vertexes);

    //start reading the first part of the file
    for(int i = 0; i < numPaths; i++)
    {
        //create edge temp variable to store what's read and further save it into the graph
        Edge<string> temp;

        //char variables to read
        char source[15], target[15];

        //read line and save data into edge
        string line1 = file[i];

        sscanf(line1.c_str(), "%s %s %d" , source, target, &temp.weight);

        temp.source = string(source);
        temp.target = string(target);

        //add the edge to the graph
        portGraph.addEdge(temp);
    }


    //variable to start my while 
    string start, finish, tryagain = "yes";
    cout<<"\n⊹˚₊‧─────────── Ports & Routes ────────────‧₊˚⊹"<<endl;

    while(tryagain == "yes" || tryagain == "Yes" || tryagain == "YES" || tryagain == "y" || tryagain == "Y")
    {

        //ask to the user for the start and finish ports
        cout<<"What's the departure port?"<<endl;
        cin>>start;
        start[0] = toupper(start[0]);

        while (findInHash(hashT, start) == false && (start != "Antwerp"))
        {
            cout<<endl<<"Invalid port, please try again"<<endl<<endl;
            cout<<"Here are the valid ports:"<<endl;
            cout<<"- Alexandria"<<endl<<"- Algeciras"<<endl<<"- Ambarli"<<endl<<"- Balboa"<<endl<<"- Bandar"<<endl<<"- Barcelona"<<endl<<"- Bremen"<<endl<<"- Busan"<<endl<<"- Cai_Me"<<endl<<"- Callao"<<endl<<"- Cartagena"<<endl<<"- Charleston"<<endl<<"- Chennai"<<endl<<"- Chittagong"<<endl;
            cin>>start;
            start[0] = toupper(start[0]);
        }

        cout<<"What's the arrival port?"<<endl;
        cin>>finish;
        finish[0] = toupper(finish[0]);

        while (findInHash(hashT, finish) == false && (finish != "Cartagena" || finish != "Chittagong"))
        {
            cout<<endl<<"Invalid port, please try again"<<endl<<endl;
            cout<<"Here are the valid ports:"<<endl;
            cout<<"- Alexandria"<<endl<<"- Algeciras"<<endl<<"- Ambarli"<<endl<<"- Antwerp"<<endl<<"- Balboa"<<endl<<"- Bandar"<<endl<<"- Barcelona"<<endl<<"- Bremen"<<endl<<"- Busan"<<endl<<"- Cai_Me"<<endl<<"- Callao"<<endl<<"- Chennai"<<endl;
            cin>>finish;
            finish[0] = toupper(finish[0]);
        }

        //dont allow for people to write down the same departure and arrival port
        if(start == finish)
        {
            cout<<"You're already in the "<<start<<" port."<<endl;
            return 0;
        }
        else
        {
            //to find the optimal path we call dijkstra's algorithm
            bool path = portGraph.dijkstra(start, finish);

            if (!path)
            {
                cout << "No direct route found between " << start << " and " << finish << endl;
                continue; // Skip the remaining code and ask for another route
            }


            cout<<endl;

            //to find the longest path between ports
            portGraph.longestPath(start);

            cout<<endl<<"\n⊹˚₊‧────────────────────────────────‧₊˚⊹"<<endl;
        }

        //ask if the user wants to try again
        cout<<"Do you want to try another route? (yes or no)"<<endl;
        cin>>tryagain;
    }

    //say goodbye to user
    cout<<"\n⊹˚₊‧────────────────────────────────‧₊˚⊹" <<endl<<"Thank you for using the program, have a nice day!"<<endl<<endl;

    return 0;
}
