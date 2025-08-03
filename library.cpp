//
// Created by nrg91 on 8/1/2025.
//
#include "library.h"

#include <iostream>
#include <ostream>
#include <algorithm>

void library::insertBook(string title, string author, string genre, string date, string publisher, int priority)
{
    if (priorityCounter.find(priority) == priorityCounter.end())
    {
        priorityCounter[priority] = 1;
    }
    else
    {
        priorityCounter[priority] += 1;
    }
    if (bookToAuthor.find(title) == bookToAuthor.end())
    {
        bookToAuthor[title] = {author};
    }
    else
    {
        bookToAuthor[title].push_back(author);
    }

    if (priorityToBook.find(priority) == priorityToBook.end())
    {
        priorityToBook[priority] = {make_pair(title, author)};
    }
    else
    {
        priorityToBook[priority].push_back(make_pair(title, author));
    }

    // Insert priority value into maxHeap
    maxHeap.push_back(priority);
    int index = maxHeap.size() - 1;
    while (index > 0 && maxHeap[index] > maxHeap[index / 2])
    {
        int temp = maxHeap[index];
        maxHeap[index] = maxHeap[index / 2];
        maxHeap[index / 2] = temp;
        index /= 2;
    }

    string uniqueBook = title + " " + author;
    bookToPriority[uniqueBook] = priority;
    attributes[uniqueBook] = {author, genre, publisher, date};

    if (bookGraph.find(uniqueBook) == bookGraph.end())
    {
        bookGraph[uniqueBook] = {};
        for (auto it = bookGraph.begin(); it != bookGraph.end(); it++)
        {
            string key = it->first;
            vector <pair<string, double>> &value = it -> second;
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

            bookGraph[uniqueBook].push_back(make_pair(it -> first, simscore));
        }
    }

}

void library::topBook()
{
    if (!maxHeap.empty())
    {
        vector<pair<string, string>> books = priorityToBook[maxHeap[0]];
        for (int i = 0; i < books.size(); i++)
        {
            cout << books[i].first << ", " << books[i].second << endl;
        }
    }
    else
    {
        cout << "There are no books in your library." << endl;
    }

}

void library::viewLibrary()
{
    int counter = 1;
    for (auto it = bookToPriority.begin(); it != bookToPriority.end(); it++)
    {
        string book = it -> first;
        int index = book.rfind(' ');
        string title = book.substr(0, index);
        string author = book.substr(index + 1);
        cout<<counter<<". "<< title << ", " << author << endl;
        counter++;
    }
}

bool library::examineBook(string title, string author)
{
    string id = title + " " + author;
    int most = -100;
    int least = 100;
    int maxindex;
    int minindex;
    if (bookGraph.find(id) != bookGraph.end()) {
        vector<pair<string, double>> compare = bookGraph[id];
        if (compare.size() > 1)
        {
            cout << "Title: " << title << endl;
            cout << "Author: " << attributes[id][0] << endl;
            cout << "Genre: " << attributes[id][1] << endl;
            cout << "Publisher: " << attributes[id][2] << endl;
            cout << "Publication Year: " << attributes[id][3] << endl;

            for (int i = 0; i < compare.size(); i++)
            {
                string book = compare[i].first;
                double simscore = compare[i].second;
                if (simscore > most)
                {
                    most = simscore;
                    maxindex = i;
                }
                if (simscore < least)
                {
                    least = simscore;
                    minindex = i;
                }
            }

            string mostsimilar = compare[maxindex].first;
            string leastsimilar = compare[minindex].first;

            int space = mostsimilar.rfind(' ');
            string similartitle = mostsimilar.substr(0, space);
            string similarauthor = mostsimilar.substr(space + 1);
            space = leastsimilar.rfind(' ');
            string differenttitle = leastsimilar.substr(0, space);
            string differentauthor = leastsimilar.substr(space + 1);

            // finish formatting and printing

        }
        else
        {
            cout << "Title: " << title << endl;
            cout << "Author: " << attributes[id][0] << endl;
            cout << "Genre: " << attributes[id][1] << endl;
            cout << "Publisher: " << attributes[id][2] << endl;
            cout << "Publication Year: " << attributes[id][3] << endl;
        }
        return true;
    }
    return false;
}

bool library::removeBook(string title, string author)
{
    /*/
    map<string, vector<string>> bookToAuthor;
    map<int, vector<pair<string, string>>> priorityToBook;
    map<string, int> bookToPriority;
    map<string, vector<pair<string, double>> > bookGraph;
    vector<int> maxHeap;
    map<string, vector<string>> attributes;
    /*/

    if (attributes.find(title + " " + author) != attributes.end())
    {
        bookToAuthor[title].erase(remove(bookToAuthor[title].begin(), bookToAuthor[title].end(), author), bookToAuthor[title].end());
        for (auto it = priorityToBook.begin(); it != priorityToBook.end(); it++)
        {
            vector<pair<string, string>> &books = it -> second;
            for (auto it2 = books.begin(); it2 != books.end();)
            {
                if (it2 -> first == title && it2 -> second == author)
                {
                    it2 = books.erase(it2);
                }
                else
                {
                    it2++;
                }
            }
        }

        string id = title + " " + author;

        int priority = bookToPriority[id];
        vector<int> newHeap;

        bookToPriority.erase(id);
        attributes.erase(id);
        bookGraph.erase(id);

        for (auto it = bookGraph.begin(); it != bookGraph.end(); it++)
        {
            vector<pair<string, double>> &books = it -> second;
            for (auto it2 = books.begin(); it2 != books.end();)
            {
                if (it2 -> first == id)
                {
                    it2 = books.erase(it2);
                }
                else
                {
                    it2++;
                }
            }
        }
        priorityCounter[priority] -= 1;
        int counter = 0;
        for (int i = 0; i < maxHeap.size(); i++)
        {
            if (maxHeap[i] != priority)
            {
                newHeap.push_back(maxHeap[i]);
                int index = newHeap.size() - 1;
                while (index > 0 && newHeap[index] > newHeap[index / 2])
                {
                    int temp = newHeap[index];
                    newHeap[index] = newHeap[index / 2];
                    newHeap[index / 2] = temp;
                    index /= 2;
                }
            }
            else
            {
                if (counter < priorityCounter[priority])
                {
                    newHeap.push_back(maxHeap[i]);
                    int index = newHeap.size() - 1;
                    while (index > 0 && newHeap[index] > newHeap[index / 2])
                    {
                        int temp = newHeap[index];
                        newHeap[index] = newHeap[index / 2];
                        newHeap[index / 2] = temp;
                        index /= 2;
                    }
                }
            }
        }
        maxHeap = newHeap;
        return true;
    }

    return false;
}
