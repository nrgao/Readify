//
// Created by nrg91 on 8/2/2025.
//

#ifndef BOOKGRAPH_H
#define BOOKGRAPH_H


class BookGraph
{
    map<string, vector<pair<string, double>> > data;
    map<string, string> bookdescriptions;

    public:
    void insert(string title, string author, string genre, string date, string publisher, string description);
    string recommend(string title, string author);

};
#endif //BOOKGRAPH_H
