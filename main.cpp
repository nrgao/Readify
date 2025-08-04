//
// Created by nrg91 on 8/1/2025.
//
#include "library.h"
#include "bookGraph.h"
#include <iostream>
#include <vector>
#include <string>
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
    BookGraph bookgraph;

    for (int i = 0; i < books.size(); i++)
    {
        Book book = books[i];
        bookgraph.insert(book.title, book.authors, book.category, to_string(book.yearPublished), book.publisher, book.description);
    }

    cout << "\n";
    cout << "Welcome to Readify, your personal book storage and recommendation tool!" << endl;
    cout << "\n";
    cout << "Menu" << endl;
    cout << "1. Book Search" << endl;
    cout << "2. Book Recommendation Engine" << endl;
    cout << "3. Open Library" << endl;
    cout << "4. Exit Application" << endl;
    cout << "\n";
    bool open = true;
    string line;
    int priority;

    while (open)
    {
        getline(cin, line);
        if (line == "1")
        {
            cout << "Please input a book in the following format: (Title, Author)." << endl;
            getline(cin, line);
            int space = line.rfind(' ');
            string title = line.substr(0, space - 1);
            string author = line.substr(space + 1);
            vector<string> bookdetails = bookgraph.getAttributes(title + " " + author);
            if (bookdetails.empty())
            {
                cout << "Unfortunately, the provided book is not in our database.";
                cout << "\n";
            }
            else
            {
                cout << "Book Information: \n" << endl;
                cout << "Title: " << title << endl;
                for (int i = 0; i < bookdetails.size(); i++)
                    if (i == 0)
                        cout << "Author: " << bookdetails[i] << endl;
                    else if (i == 1)
                        cout << "Genre: " << bookdetails[i] << endl;
                    else if (i == 2)
                        cout << "Publisher: " << bookdetails[i] << endl;
                    else if (i == 3)
                        cout << "Publication Year: " << bookdetails[i] << endl;
                    else if (i == 4)
                    {
                        if (bookdetails[i].length() == 0)
                            cout << "Description: " << "N/A" << endl;
                        else
                            cout << "Description: " << bookdetails[i] << endl;
                    }
            }

        }
        else if (line == "2")
        {
            cout << "Please input a book in the following format: (Title, Author)." << endl;
            getline(cin, line);
            int space = line.rfind(' ');
            string title = line.substr(0, space - 1);
            string author = line.substr(space + 1);
            vector<string> recbook = bookgraph.recommend(title, author);
            cout << "\n";
            cout << "Book Details:" << endl;
            cout << "\n";
            if (recbook.empty())
            {
                cout << "Unfortunately, the provided book is not in our database.";
            }
            else
            {
                for (int i = 0; i < recbook.size(); i++)
                    if (i == 0)
                        cout << "Title: " << recbook[i] << endl;
                    else if (i == 1)
                        cout << "Author: " << recbook[i] << endl;
                    else if (i == 2)
                        cout << "Genre: " << recbook[i] << endl;
                    else if (i == 3)
                        cout << "Publisher: " << recbook[i] << endl;
                    else if (i == 4)
                        cout << "Publication Year: " << recbook[i] << endl;
                    else if (i == 5)
                    {
                        if (recbook[i].length() == 0)
                            cout << "Description: " << "N/A" << endl;
                        else
                            cout << "Description: " << recbook[i] << endl;
                        cout << "\n";
                    }

                cout << "Add book to library? (y/n)" << endl;
                getline(cin, line);

                if (line == "y")
                {
                    cout << "Please provide a priority level for this book. This value should be an integer between 0 and 100, with higher values indicting greater priority." << endl;

                    getline(cin, line);
                    priority = stoi(line);
                    booklibrary.insertBook(recbook[0], recbook[1], recbook[2], recbook[4], recbook[3], recbook[5], priority);
                    cout << "Book succesfully added to library." << endl;
                }
            }

        }
        else if (line == "3") {
            while (line != "f")
            {
                cout << "Library Options:" << endl;
                cout << "a. View Books" << endl;
                cout << "b. Top Book" << endl;
                cout << "c. Remove Book" << endl;
                cout << "d. Examine Book" << endl;
                cout << "e. Add Book" << endl;
                cout << "f. Exit Library" << endl;
                cout << "\n";

                getline(cin, line);
                if (line == "a")
                {
                    cout << "Your Library: \n" << endl;
                    booklibrary.viewLibrary();
                    cout << "\n";
                }
                else if (line == "b")
                {
                    cout << "Highest priority book(s): \n" << endl;
                    booklibrary.topBook();
                    cout << "\n";
                }
                else if (line == "c")
                {
                    cout << "Please provide the title and author of the book you wish to remove in the following format: title, author" << endl;
                    getline(cin, line);
                    int space = line.rfind(' ');
                    string title = line.substr(0, space - 1);
                    string author = line.substr(space + 1);
                    bool exist = booklibrary.removeBook(title, author);
                    if (exist == false)
                    {
                        cout << "This book does not exist within your library." << endl;
                    }
                    else
                    {
                        cout << "Book Successfully removed from library." << endl;
                    }
                    cout << "\n";
                }
                else if (line == "d")
                {
                    cout << "Please provide the title and author of the book you wish to examine in the following format: title, author" << endl;
                    getline(cin, line);
                    int space = line.rfind(' ');
                    string title = line.substr(0, space - 1);
                    string author = line.substr(space + 1);
                    bool exist = booklibrary.examineBook(title, author);
                    if (exist == false)
                    {
                        cout << "This book does not exist within your library." << endl;
                    }
                    cout << "\n";
                }
                else if (line == "e")
                {
                    cout << "Please provide the title and author of the book you wish to add (Title, Author)." << endl;
                    getline(cin, line);
                    int space = line.rfind(' ');
                    string title = line.substr(0, space - 1);
                    string author = line.substr(space + 1);
                    string id = title + " " + author;
                    vector <string> details = bookgraph.getAttributes(id);
                    if (!details.empty())
                    {
                        cout << "Please provide a priority level for this book. This value should be an integer between 0 and 100, with higher values indicating greater priority." << endl;
                        getline(cin, line);
                        booklibrary.insertBook(title, author, details[1], details[3], details[2], details[4], stoi(line));
                        cout << "Book succesfully added to library." << endl;
                        cout << "\n";
                    }
                    else
                    {
                        cout << "This book does not exist within our database. Do you wish to manually provide additional information about the book? (y/n)" << endl;
                        getline(cin, line);
                        if (line == "y")
                        {
                            cout << "Please provide the following information: " << endl;
                            cout << "Genre: ";
                            getline(cin, line);
                            string genre = line;
                            cout << "Publisher: ";
                            getline(cin, line);
                            string publisher = line;
                            cout << "Publication Year: ";
                            getline(cin, line);
                            string year = line;
                            cout << "Description: ";
                            getline(cin, line);
                            string description = line;
                            cout << "Manual entry complete. What is the priority level of this book?" << endl;
                            getline(cin, line);
                            booklibrary.insertBook(title, author, genre, year, publisher, description, stoi(line));
                            cout << "Book successfully added to library" << endl;
                            cout << "\n";
                        }
                        else
                        {
                            // pass
                        }

                    }
                }
                else if (line == "f")
                {
                    // Exit library menu, do nothing
                }
            }
        }
        else if (line == "4")
        {
            open = false;
        }
        cout << "\n";
        cout << "Menu" << endl;
        cout << "1. Book Search" << endl;
        cout << "2. Book Recommendation Engine" << endl;
        cout << "3. Open Library" << endl;
        cout << "4. Exit Application" << endl;
        cout << "\n";
    }

    cout << "Thank you for using Readify." << endl;
    return 0;
}
