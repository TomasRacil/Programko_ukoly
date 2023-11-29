#include "Library.h"


using namespace std;

Library::Library(string path_to_file)
{
    this->path = path_to_file;
	ifstream file;
	file.open(path_to_file);
	string line;
    while (getline(file, line)) {
			this->books.push_back(Book(line));
			line.erase();
	}
	if (!line.empty()) {
		this->books.push_back(Book(line));
		line.erase();
	}
    file.close();
	this->books.sort();
}
    void Library::addBook(Book book)
    {
        books.push_back(book);
        books.sort();
    }

     /* long Library::getUniqueId()
    {
        Book foundBooks = Book(string book);
    for (Book b : books)
    {
        if (b.id == id)
            foundBooks.addEvent(b);//přidá se k found events

    }
    return foundBooks;
    }  */ 
     /* void Library::showAbailableBooks()
     {

     }
    void findBookAndBorrowIt(string name);
    ~Library(); */

    ostream& operator << (ostream& out, const Library& obj)
    {
    for (Book b : obj.books)
    {
        out<<b<<endl<<endl;
    }
    return out;
    }  