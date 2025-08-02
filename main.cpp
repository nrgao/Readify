//
// Created by nrg91 on 8/1/2025.
//
#include "library.h"
#include <iostream>
#include <vector>
#include "csv.hpp"  
using namespace std;
using namespace csv;  

struct Book {
    string title;
    string authors;
    string description;
    string publisher;
    int price;
    string monthPublished;
    int yearPublished;
};

int main()
{
    vector<Book> books;

    try {
        CSVReader reader("BooksDatasetClean.csv");

        for (auto& row : reader) {
            Book b;

            b.title = row["title"].get<string>();
            b.authors = row["authors"].get<string>();
            b.description = row["description"].get<string>();
            b.publisher = row["publisher"].get<string>();

            try {
                b.price = row["price"].get<int>();
            } catch (...) {
                b.price = 0;
            }

            b.monthPublished = row["monthPublished"].get<>();

            try {
                b.yearPublished = row["yearPublished"].get<int>();
            } catch (...) {
                b.yearPublished = 0;
            }

            books.push_back(b);
        }
    } catch (const exception& e) {
        cerr << "Error reading CSV file: " << e.what() << endl;
        return 1;
    }

    library booklibrary;
    // You can now insert books into your library like:
    // for (const auto& b : books) {
    //     booklibrary.insertBook(b.title, b.authors, b.description, b.publisher, b.price, b.monthPublished, b.yearPublished);
    // }

    cout << "Welcome to Readify, your personal book storage and recommendation tool!" << endl;
    cout << "Menu" << endl;
    cout << "1. Book Search" << endl;
    cout << "2. Open Library" << endl;
    cout << "3. Exit Application" << endl;
    cout << "\n";
    bool open = true;
    string line;

    while (open)
    {
        getline(cin, line);
        if (line == "1")
        {
            cout << "Please input a book in the following format: (title, author)." << endl;
        }
        else if (line == "2")
        {
            cout << "Library Options:" << endl;
            cout << "a. View Books" << endl;
            cout << "b. Top Book" << endl;
            cout << "c. Remove Book" << endl;
            cout << "d. Examine Book" << endl;
            cout << "e. Exit Library" << endl;
            cout << "\n";

            getline(cin, line);
            if (line == "a")
            {
                booklibrary.viewLibrary();
            }
            else if (line == "b")
            {
                booklibrary.topBook();
            }
            else if (line == "c")
            {
                cout << "Please provide the title and author of the book you wish to remove in the following format: title, author" << endl;
                getline(cin, line);
                int space = line.find(' ');
                string title = line.substr(0, space - 1);
                string author = line.substr(space + 1);
                booklibrary.removeBook(title, author);
            }
            else if (line == "d")
            {
                cout << "Please provide the title and author of the book you wish to examine in the following format: title, author" << endl;
                getline(cin, line);
                int space = line.find(' ');
                string title = line.substr(0, space - 1);
                string author = line.substr(space + 1);
                booklibrary.examineBook(title, author);
            }
            else if (line == "e")
            {
                // Exit library menu, do nothing
            }
        }
        else
        {
            open = false;
        }
        cout << "\n\n";
        cout << "Menu" << endl;
        cout << "1. Book Search" << endl;
        cout << "2. Open Library" << endl;
        cout << "3. Exit Application" << endl;
        cout << "\n";
    }

    cout << "Thank you for using Readify." << endl;
    return 0;
}
