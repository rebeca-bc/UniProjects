#ifndef Graph_h_
#define Graph_h_

#include <iostream>
#include <vector>
#include "Edge.h"
#include <queue>
#include <stack>
using namespace std;

template<typename T>
class Graph
{
    private:
        vector<T> vertexes;
        vector<vector<Edge<T>>> adjList;
        int numVertexes;
    public:
        Graph();
        Graph(vector<T> v);
        int findVertex(T v);
        int smallestCost(vector<int>& cost, vector<bool>& processed);
        void addEdge(Edge<T> e);
        void addVertex(vector<T> v);
        void removeEdge(Edge<T> e);
        void print(); 
        bool dijkstra(T start, T finish);
        void longestPath(T start);
        void DFSLongestPath(int index, vector<bool>& visited, vector<T>& currentPath, int currentPathLenght, vector<T>& longestPath, int& maxLength);
    };

template<typename T>
Graph<T>::Graph()
{
    numVertexes = 0;
}
 
template<typename T>
int Graph<T>::findVertex(T vertex)
{
    auto i = find(vertexes.begin(), vertexes.end(), vertex);
    if(i != vertexes.end())
    {
        return distance(vertexes.begin(), i);
    }
    else
    {
        return -1;
    }

}

template<typename T>
Graph<T>::Graph(vector<T> v)
{
    numVertexes = v.size();
    this->vertexes = v;

    for(int i = 0; i < numVertexes; i++)
    {
        vector<Edge<T>> temp;
        adjList.push_back(temp);
    }
}

template <typename T>
void Graph<T>::addVertex(vector<T> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        vertexes.push_back(v[i]);
        numVertexes++;
        vector<Edge<T>> temp;
        adjList.push_back(temp);
    }
}

template<typename T>
void Graph<T>::addEdge(Edge<T> e)
{
    int source = findVertex(e.source);
    int target = findVertex(e.target);

    if (source != -1 && target != -1)
    {
        e.weight = abs(e.weight);  // Ensure non-negative weight
        adjList[source].push_back(e);
    }
    else
    {
        cout << "Vertex not found" << endl;
    }
}

template<typename T>
void Graph<T>::print()
{
    for(int i = 0; i < numVertexes; i++)
    {
        cout << vertexes[i] << " -> ";
        for(int j = 0; j < adjList[i].size(); j++)
        {
            cout << adjList[i][j].target << " " << adjList[i][j].weight << " | ";
        }
        cout << endl;  // Add this line to print a line break after each vertex
    }
}

template<typename T>
bool Graph<T>::dijkstra(T start, T finish)
{
    int startIndex = findVertex(start);
    int finishIndex = findVertex(finish);

    // Vector for processed nodes with false
    vector<bool> processed(numVertexes, false);
    // Vector for the cost of each vertex, set to infinity to track the weights of shorter paths
    vector<int> cost(numVertexes, INT_MAX);
    // Vector to keep the path origin, set to -1
    vector<int> path(numVertexes, -1);

    // Starting vertex, set its cost to 0 and change its processed value to true
    cost[startIndex] = 0;

    // Check if there are any false values left in processed (not processed yet)
    while (find(processed.begin(), processed.end(), false) != processed.end())
    {
        // Find the vertex with the smallest cost and mark it as processed
        int index = smallestCost(cost, processed);
        processed[index] = true;

        // Stop the algorithm if we reach the finish vertex
        if (index == finishIndex)
            break;

        // Update the cost of the adjacent vertices
        for (auto& edge : adjList[index])
        {
            int neighborIndex = findVertex(edge.target);
            if (!processed[neighborIndex])
            {
                int newCost = cost[index] + edge.weight;
                if (newCost < cost[neighborIndex])
                {
                    cost[neighborIndex] = newCost;
                    path[neighborIndex] = index;
                }
            }
        }
    }

    // Check if there is a valid path from start to finish
    if (path.size() == 0 || path[finishIndex] == -1)
    {
        cout << endl << "No path between " << start << " & " << finish << endl;
        return false;
    }

    // Retrieve the optimal route using a stack
    stack<int> pathStack;
    int currentIndex = finishIndex;
    while (currentIndex != startIndex)
    {
        pathStack.push(currentIndex);
        currentIndex = path[currentIndex];
    }
    pathStack.push(startIndex);

    // Print the optimal route
    cout << endl << "\n⊹˚₊‧──────────── Ruta Óptima ─────────────‧₊˚⊹" << endl << "De " << start << " a " << finish << endl << "- Puertos: ";
    while (!pathStack.empty())
    {
        int index = pathStack.top();
        cout << vertexes[index] << " ";
        pathStack.pop();
    }
    cout << endl;

    // Print the distance in nautical miles
    cout << "- Distancia: " << cost[finishIndex] << " millas náuticas";
    return true;

}

template<typename T>
int Graph<T>::smallestCost(vector<int>& cost, vector<bool>& processed)
{
    int min = INT_MAX, minindex = 0;
    for (int i = 0; i < cost.size(); i++)
    {
        if (!processed[i] && cost[i] < min)
        {
            min = cost[i];
            minindex = i;
        }
    }
    return minindex;
}

template<typename T>
void Graph<T>::longestPath(T start)
{
    int startIndex = findVertex(start);

    vector<bool> visited(numVertexes, false);  
    vector<T> currentPath;
    vector<T> longestPath;
    int maxLength = 0;
    int currentPathLength = 0;

    DFSLongestPath(startIndex, visited, currentPath, currentPathLength, longestPath, maxLength);

    cout<<endl<<"\n⊹˚₊‧──────────── Longest Route ─────────────‧₊˚⊹"<<endl<<"From " << start << endl << "- Ports: ";
    for (const auto& port : longestPath)
    {
        cout << port << " ";
    }
    cout << endl << "- Distance: " << maxLength << " nautical miles" << endl;
}

template<typename T>
void Graph<T>::DFSLongestPath(int index, vector<bool>& visited, vector<T>& currentPath, int currentPathLength, vector<T>& longestPath, int& maxLength)
{
    visited[index] = true;
    currentPath.push_back(vertexes[index]);

    for (auto& edge : adjList[index])
    {
        int neighborIndex = findVertex(edge.target);
        if (!visited[neighborIndex])
        {
            // Calculate the new current path length
            int edgeWeight = edge.weight;  // Assuming 'weight' is the member variable in your Edge class
            int newCurrentPathLength = currentPathLength + edgeWeight;

            DFSLongestPath(neighborIndex, visited, currentPath, newCurrentPathLength, longestPath, maxLength);
        }
    }

    if (currentPathLength > maxLength)
    {
        maxLength = currentPathLength;
        longestPath = currentPath;
    }

    currentPath.pop_back();
    visited[index] = false;
}

#endif