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
    map<string, vector<string>> bookToAuthor;
    map<int, vector<pair<string, string>>> priorityToBook;
    map <string, int> bookToPriority;
    map<string, vector<pair<string, double>> > bookGraph;
    vector<int> maxHeap;
    map<string, vector<string>> attributes;

    public:
    void insertBook(string title, string author, string genre, string date, string publisher, int priority);

    void viewLibrary();

    void topBook();

    void removeBook(string title, string author);

    void examineBook(string title, string author);

};
#endif //LIBRARY_H
