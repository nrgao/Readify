//
// Created by nrg91 on 8/2/2025.
//

#ifndef BOOKGRAPH_H
#define BOOKGRAPH_H
#include <map>
#include <string>
#include <vector>
using namespace std;

class BookGraph
{
   // map<string, vector<pair<string, double>> > data;
    //map<string, string> bookdescriptions; // maps boo
    map<string, vector<string>> attributes; // partial graph that maps books to attributes

    public:
    // insert book into graph
    void insert(string title, string author, string genre, string date, string publisher, string description);
    // computes edge weights and recommends the most similar book
    vector<string> recommend(string title, string author);
    // retrieves book attributes
    vector <string> getAttributes(string id);

};
#endif //BOOKGRAPH_H
