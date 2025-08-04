//
// Created by nrg91 on 8/1/2025.
//

#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

class library
{
    map<int, int> priorityCounter;
    map<string, vector<string>> bookToAuthor;
    map<int, vector<pair<string, string>>> priorityToBook;
    map <string, int> bookToPriority;
    map<string, vector<pair<string, double>> > bookGraph;
    vector<int> maxHeap;
    map<string, vector<string>> attributes;

    public:
    void insertBook(string title, string author, string genre, string date, string publisher, string description, int priority);

    void viewLibrary();

    void topBook();

    bool removeBook(string title, string author);

    bool examineBook(string title, string author);

};
#endif //LIBRARY_H
