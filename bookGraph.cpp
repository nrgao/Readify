//
// Created by nrg91 on 8/2/2025.
//

#include "bookGraph.h"
#include <iostream>
using namespace std;

// insert into partial graph using attributes
void BookGraph::insert(string title, string author, string genre, string date, string publisher, string description)
{
    string uniqueBook = title + " " + author; // get unique book id
    attributes[uniqueBook] = {author, genre, publisher, date, description}; // set attributes in map
}

vector<string> BookGraph::recommend(string title, string author) // recommend book based on simscore
{
    string id = title + " " + author; // get unique id
    if (attributes.find(id) == attributes.end()) // if not in graph
        return {};
    vector<string> current = attributes[id]; // get attributes
    int simscore;
    int maxscore = -100;
    string maxid;
    for (auto it = attributes.begin(); it != attributes.end(); it++) // check against all other books
    {
        simscore = 0;
        if (it -> first != id) // compute simscore using weighted sum
        {
            vector<string> details = it -> second;
            if (details[0] == current[0]) // shared author
            {
                simscore += 7;
            }
            if (details[1] == current[1]) // shared genre
            {
                simscore += 10;
            }
            if (details[2] == current[2]) // shared publisher
            {
                simscore += 1;
            }

            int timediff = abs(stoi(details[3]) - stoi(current[3])); // publication date difference

            simscore -= timediff / 10.0;
        }
        if (maxscore < simscore) // update if necessary
        {
            maxscore = simscore;
            maxid = it -> first;
        }
    }

    // get most similar and print
    string mostsimilar = maxid;
    int space = mostsimilar.rfind(' ');
    string booktitle = mostsimilar.substr(0, space);
    string authorname = mostsimilar.substr(space + 1);
    cout << "Recommended book based on similarity score (Title, Author): " << booktitle << ", "<< authorname<<endl;
    return {booktitle, authorname, attributes[mostsimilar][1], attributes[mostsimilar][2], attributes[mostsimilar][3], attributes[mostsimilar][4]};
}

vector <string> BookGraph::getAttributes(string id) // get attributes of a particular book
{
    if (attributes.find(id) != attributes.end())
        return attributes[id];
    else
        return {};
}

