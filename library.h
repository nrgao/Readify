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

class Library
{
    map<int, int> priorityCounter; // maps priority to frequency
    map<string, vector<string>> bookToAuthor; // maps book to authors
    map<int, vector<pair<string, string>>> priorityToBook; // maps priority to books
    map <string, int> bookToPriority; // maps books to priorities
    map<string, vector<pair<string, double>> > bookGraph; // adjacency list storing books and edges representing similarity
    vector<int> maxHeap; // priority queue storing priority values
    map<string, vector<string>> attributes; // maps books to attributes

    public:
    // insert book into library based on attributes
    void insertBook(string title, string author, string genre, string date, string publisher, string description, int priority);
    // print books in library
    void viewLibrary();
    // print top priority book(s)
    void topBook();
    // remove book from library and all associated data structures
    bool removeBook(string title, string author);
    // examine book details and compare similarity to other books
    bool examineBook(string title, string author);

};
#endif //LIBRARY_H
