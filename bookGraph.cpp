//
// Created by nrg91 on 8/2/2025.
//

#include "bookGraph.h"
#include <iostream>
using namespace std;

void BookGraph::insert(string title, string author, string genre, string date, string publisher, string description)
{
    string uniqueBook = title + " " + author;
    attributes[uniqueBook] = {author, genre, publisher, date, description};
    /*/
    if (data.find(uniqueBook) == data.end())
    {
        data[uniqueBook] = {};
        for (auto it = data.begin(); it != data.end(); it++)
        {
            string key = it->first;
            vector <pair<string, double>> value = it -> second;
            vector<string> details = attributes[key];
            vector<string> current = attributes[uniqueBook];
            double simscore = 0;
            if (details[0] == current[0])
            {
                simscore += 7;
            }
            if (details[1] == current[1])
            {
                simscore += 10;
            }
            if (details[2] == current[2])
            {
                simscore += 1;
            }

            int timediff = abs(stoi(details[3]) - stoi(current[3]));

            simscore -= timediff / 10.0;

            value.push_back(make_pair(uniqueBook, simscore));

            data[uniqueBook].push_back(make_pair(it -> first, simscore));
        }
    }
    /*/
}

vector<string> BookGraph::recommend(string title, string author)
{
    string id = title + " " + author;
    vector<string> current = attributes[id];
    int simscore;
    int maxscore = -100;
    string maxid;
    cout << id << endl;
    for (auto it = attributes.begin(); it != attributes.end(); it++)
    {
        simscore = 0;
        if (it -> first != id)
        {
            vector<string> details = it -> second;
            if (details[0] == current[0])
            {
                simscore += 7;
            }
            if (details[1] == current[1])
            {
                simscore += 10;
            }
            if (details[2] == current[2])
            {
                simscore += 1;
            }

            int timediff = abs(stoi(details[3]) - stoi(current[3]));

            simscore -= timediff / 10.0;
        }
        if (maxscore < simscore)
        {
            maxscore = simscore;
            maxid = it -> first;
        }
    }

    string mostsimilar = maxid;
    int space = mostsimilar.rfind(' ');
    string booktitle = mostsimilar.substr(0, space);
    string authorname = mostsimilar.substr(space + 1);
    cout << "Recommended book based on similarity score (Title, Author): " << booktitle << ", "<< authorname<<endl;
    return {booktitle, authorname, attributes[mostsimilar][1], attributes[mostsimilar][2], attributes[mostsimilar][3], attributes[mostsimilar][4]};
}
