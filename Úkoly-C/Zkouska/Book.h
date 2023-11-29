#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class Book
{
    private:
    long id;
    string name;
    string author;
    bool available;

    public:
    Book(string book);
    string getName();
    long getId();
    long setID(Book book);
    bool operator < (const Book& obj)const;
    bool operator==(const Book& obj);

    friend ostream& operator<<(ostream& out, const Book& obj);
    friend class Library;
};