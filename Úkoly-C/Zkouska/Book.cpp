#include <iostream>
#include <sstream>
#include <vector>
#include "Book.h"

using namespace std;

Book::Book(string book)
{
    stringstream event_ss(book);
    string item;
    vector<string> items;
    while (getline(event_ss, item, ';'))
    {
        items.push_back(item);
    }

    this->id = stol(items[0]);
    this->name = items[1];
    this->author = items[2];
    if (items[3] == "Available" || items[3] == "Available ")
    {
        this->available = true;
    }
    else
    {
        this->available = false;
    }
}

string Book::getName()
{
    return name;
}

long Book::getId()
{
    return id;
}

bool Book::operator<(const Book &obj) const
{
    if ((author.compare(obj.author)) < 0)
        return true;
    else
        return false;
}

bool Book::operator==(const Book &obj)
{
    if (author.compare(obj.author) == 0)
        return true;
    else
        return false;
}

ostream &operator<<(ostream &out, const Book &obj)
{
    out << "%" << obj.id << "%" << ";";
    out << "%" << obj.name << "%" << ";";
    out << "%" << obj.author << "%" << ";";
    out << "%" << obj.available << "%";
    return out;
}

