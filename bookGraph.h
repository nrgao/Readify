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
    map<string, vector<pair<string, double>> > data;
    map<string, string> bookdescriptions;
    map<string, vector<string>> attributes;

    public:
    void insert(string title, string author, string genre, string date, string publisher, string description);
    vector<string> recommend(string title, string author);
    vector <string> getAttributes(string id);

};
#endif //BOOKGRAPH_H
