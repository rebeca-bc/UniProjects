#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

template<typename T>
struct Node
{
    T data;
    Node<T>* next;
    Node<T>* previous;
    Node(const T& value) : data(value), previous(nullptr), next(nullptr) {};
};

template<typename T>
int hashFunction(const T& key)
{
    int hash = 0;

    for (int i = 0; i < key.size(); i++)
    {
        if(key[i] % 2 != 0)
        {
            hash += key[i] * 1.2;
        }
        else
        {
            hash += key[i];
        }
    }

    hash = hash % 101;

    return hash;
}

template<typename T>
vector<Node<T>*> HashTable(vector<T>& vec)
{
    //create a vector for the hash table 
    vector<Node<T>*> hashTable(101, nullptr);

    //loop through the vector
    for (const T& value : vec)
    {
        int index = hashFunction(value);
        
        //create the new node
        Node<T>* newNode = new Node<T>(value);

        //see if the status is empty
        if(hashTable[index] == nullptr)
        {
            //insert the number into the hash table
            hashTable[index] = newNode;
        }
        else
        {
            //when a collision happens add the new node on front of the linked list
            newNode->previous = hashTable[index];
            hashTable[index]->next = newNode;

        }

    }

    return hashTable;
}


template<typename T>
bool findInHash(vector<Node<T>*> hash, const T& value)
{
    //get the index of the value
    int index = hashFunction(value);

    //create a pointer to the head of the linked list
    Node<T>* head = hash[index];

    //loop through the linked list
    while(head != nullptr)
    {
        //check if the value is in the linked list
        if(head->data == value)
        {
            return true;
        }
        else
        {
            head = head->next;
        }
    }

    return false;
}

#endif