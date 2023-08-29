#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TreeNode 
{
    string ubi;
    int count;
    set<string> departureDates;
    set<string> departureTimes;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const string& ubi) : ubi(ubi), count(1), left(nullptr), right(nullptr) {}
};

void insertBST(TreeNode*& root, const string& ubi, const string& date, const string& time) 
{
    if (!root)
    {
        // If root is null, create a new Node with ubi
        root = new TreeNode(ubi);

        //insert corresponding date and time.
        root->departureDates.insert(date);
        root->departureTimes.insert(time);
        return;
    }


    //found 
    if (ubi == root->ubi) 
    {
        root->count++;
        root->departureDates.insert(date);
        root->departureTimes.insert(time);
    } 
    //if ubi smaller
    else if (ubi < root->ubi) 
    {
        //recursive call on its own left child
        insertBST(root->left, ubi, date, time);
    } 
    else 
    {
        //recursive call on its own right 
        insertBST(root->right, ubi, date, time);
    }
}

bool searchBST(TreeNode* root, const string& ubi)
{
    //root is nullptr, return false
    if (!root)
    {
        return false;
    }

    //found
    if (ubi == root->ubi)
    {
        return true;
    }

    //keep recursively looking
    if (ubi < root->ubi)
    {
        return searchBST(root->left, ubi);
    }
    else
    {
        return searchBST(root->right, ubi);
    }

}

void buildBST(const vector<Record>& records, TreeNode*& root) 
{
    // Iterate over each record in the input vector
    for (const auto& record : records) 
    {
        // Insert the record's ubi, date, and time into the BST
        insertBST(root, record.ubi, record.date, record.time);
    }
}

void searchVessel(TreeNode* root) 
{
    string ubi;

    //ask what to look 4
    cout << "Enter the UBI of the vessel to search: ";
    cin >> ubi;

    //&pointer to look from root
    TreeNode* node = root;
    while (node) 
    {
        if (ubi == node->ubi) 
        {
            cout << "⋆⋆⋆⋆⋆ Vessel " << ubi << " found ⋆⋆⋆⋆⋆" << endl;
            //print number of times it appeared
            cout << "Count: " << node->count << endl;
            cout << "Departure Dates and Times: ";
            auto itDate = node->departureDates.begin();
            auto itTime = node->departureTimes.begin();

            //iterate over the two vectors simultaneously
            while (itDate != node->departureDates.end() && itTime != node->departureTimes.end()) 
            {
                cout << endl << "- " << *itDate << " at " << *itTime;
                ++itDate;
                ++itTime;
            }

            cout << endl;

            return;
        } 
        else if (ubi < node->ubi) 
        {
            node = node->left;
        } 
        else 
        {
            node = node->right;
        }
    }

    cout << "Vessel not found!" << endl;
}