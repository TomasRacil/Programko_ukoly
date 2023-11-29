#pragma once
#include <iostream>
#include <string>
#include <list>
#include<vector>
#include "Book.h"

using namespace std;

class Library
{
    private:
    string path;
    list<Book> books;
    list<Book> getAvailableBooks();

    public:
    Library(string path_to_file);
    void addBook(Book book);
    /* long getUniqueId();
    void showAbailableBooks();
    void findBookAndBorrowIt(string name);
    ~Library(); */

    friend ostream& operator << (ostream& out, const Library& obj);

};