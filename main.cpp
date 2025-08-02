//
// Created by nrg91 on 8/1/2025.
//
#include "library.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

struct Book {
    string title;
    string authors;
    string description;
    string publisher;
    int price;
    string monthPublished;
    int yearPublished;
};

Book parseBookCSV(const string& line) {
    stringstream ss(line);
    string token;
    Book book;

    getline(ss, book.title, ','); //title
    
    getline(ss, book.authors, ','); //authors

    getline(ss, book.description, ','); //description

    getline(ss, book.publisher, ','); //publisher

    getline(ss, token, ','); //price
    book.price = stoi(token);

    getline(ss, book.monthPublished, ','); //monthPublished

    getline(ss, token, ','); //yearPublished
    book.yearPublished = stoi(token);

    return book;
}

int main()
{
    ifstream file("BooksDatasetClean.csv");
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<Book> books;
    string line;

    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        books.push_back(parseBookCSV(line));
    }

    file.close();

    library booklibrary;
    // for (const auto& b : books) {
    //     booklibrary.insertBook(b.title, b.authors, b.description, b.publisher, b.price, b.monthPublished, b.yearPublished);
    // }

    cout << "Welcome to Readify, your personal book storage and recommendation tool!";
    cout << "Menu" << endl;
    cout << "1. Book Search" << endl;
    cout << "2. Open Library" << endl;
    cout << "3. Exit Application" << endl;
    cout << "\n";
    bool open = true;
    

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
                cout << "Please provide the title and author of the book you wish to remove in the following format: title, author";
                getline(cin, line);
                int space = line.find(' ');
                string title = line.substr(0, space - 1);
                string author = line.substr(space + 1);
                booklibrary.removeBook(title, author);
            }
            else if (line == "d")
            {
                cout << "Please provide the title and author of the book you wish to examine in the following format: title, author";
                getline(cin, line);
                int space = line.find(' ');
                string title = line.substr(0, space - 1);
                string author = line.substr(space + 1);
                booklibrary.examineBook(title, author);
            }
            else if (line == "e")
            {

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

    cout << "Thank you for using Readify.";
    return 0;
}