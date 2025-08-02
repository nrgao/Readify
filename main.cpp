//
// Created by nrg91 on 8/1/2025.
//
#include "library.h"
#include <iostream>

int main()
{
    library booklibrary;
    booklibrary.insertBook("bob", "bob", "bob", "1000", "bob", 5);

    cout << "Welcome to Readify, your personal book storage and recommendation tool!";
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