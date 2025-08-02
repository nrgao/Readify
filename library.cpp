//
// Created by nrg91 on 8/1/2025.
//
#include "library.h"

void library::insertBook(string title, string author, string genre, string date int priority)
{
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
    attributes[uniqueBook] = {author, genre, date};

    if (bookGraph.find(uniqueBook) == bookGraph.end())
    {
        int length = bookGraph.size();

    }

}

string library::topBook()
{
    vector<pair<string, string>> books = priorityToBook[maxHeap[0]];
}
