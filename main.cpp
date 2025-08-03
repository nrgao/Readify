//
// Created by nrg91 on 8/1/2025.
//
#include "library.h"
#include <iostream>
#include <vector>
#include "include/csv.hpp"
using namespace std;
using namespace csv;  

struct Book {
    string title;
    string authors;
    string description;
    string category;
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

            //extract title
            b.title = row["Title"].get<string>();

            //extract first author and exclude "By "
            string rawAuthors = row["Authors"].get<string>();
            size_t byPos = rawAuthors.find("By ");
            if (byPos != string::npos) {
                rawAuthors = rawAuthors.substr(byPos + 3);
            }
            size_t commaPos = rawAuthors.find(", ");
            if (commaPos != string::npos) {
                b.authors = rawAuthors.substr(0, commaPos);
            } else {
                b.authors = rawAuthors; 
            }

            //extract description
            b.description = row["Description"].get<string>();

            //extract publisher
            b.publisher = row["Publisher"].get<string>();

            //extract first category
            string rawCategory = row["Category"].get<string>();
            commaPos = rawCategory.find(',');
            if (commaPos != string::npos) {
                b.category = rawCategory.substr(0, commaPos);
            } else {
                b.category = rawCategory;
            }
            
            //extract price
            try {
                b.price = row["Price"].get<int>();
            } catch (...) {
                b.price = 0;
            }

            //extract monthPublished and yearPublished
            b.monthPublished = row["Publish Date (Month)"].get<>();
            try {
                b.yearPublished = row["Publish Date (Year)"].get<int>();
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

    booklibrary.insertBook("bob", "bob", "bob", "1000", "bob", 100);
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
