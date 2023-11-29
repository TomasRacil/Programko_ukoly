#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>

using namespace std;

class Book
{
    private:
        long id;
        string nazev;
        string autor;
        bool dostupnost;

    public:
        Book(string book); // vtvoří knihu ze stringu o struktuře
        bool operator <(const Book& obj) const; //true pokud je autor dříve v abecedě než autor obj.
        bool operator ==(const Book& obj) const;//true pokud jsou ID stejná
        void setID(long id); //nastaví ID knihy
        string getNazev();
        long getID();
        bool getDostupnost();
        void setDostupnost(bool dostupnost);

    friend ostream& operator<<(ostream& out, const Book& obj);//vrací ostream ve formátu %id%;%nazev%;%autor%;%dostupnost%

};

class Library
{
    private:
        string path; //cesta/název souboru s knihami
        list<Book> books; //množina knih, kontajner si zolte; vždy seřazeno podle autora
        list<Book> getAvailableBooks(); //rací libovoolný kontajner dostupných knih
    public:
        Library(string path_to_file); //konstruktor, který naplní knihy z .txt do kontejneru. Uloží cestu k souboru do objektu.
        void addBook(Book book); //přidá knihu transakci za předpokladu, že v systému již neexistuje kniha se stejným ID
        long getUniqueId(); //vrátí kladné ID, které v systému ještě nebylo použito
        void showAvailableBooks(); //Vypíše všechny dostupné knihy
        void findBookAndBorrowIt(string name); //Najde knihu podle jména, nebo jeho části. Pokud najde více knih vytiskne je. Pokud nenajde žádnou informuje uživatele. Pokud najdeprávě jednu, vypíše ji a  zeptá se zdali si ji chce uživatel půjčit. Pokud ano změní její dostupnost.
    ~Library() //uloží změny do txt souboru
    {
        fstream fs;
        fs.open(path, ios::out);
        if (fs.is_open()) 
        {
            for(auto it = books.begin(); it != books.end(); it++)
            {
                fs<<*it<<endl;
            }
        }
        fs.close();
    }

    friend ostream& operator<<(ostream& out, const Library & obj);

};

int main()
{
    Book book("9;Animal Farm;Orwell George;Available");
    std::cout<<book<<std::endl<<std::endl;


    Library library("data.txt");
    std::cout<<library<<std::endl<<std::endl;


    library.addBook(book);
    std::cout<<std::endl;


    book.setID(library.getUniqueId());
    library.addBook(book);
    std::cout<<std::endl;


    std::cout<<"Dostupné knihy:"<<std::endl;
    library.showAvailableBooks();
    std::cout<<std::endl;


    std::cout<<"Pujceni knihy:"<<std::endl;
    library.findBookAndBorrowIt("Kill");
    std::cout<<std::endl;
    library.findBookAndBorrowIt("a");
    std::cout<<std::endl;
    library.findBookAndBorrowIt("Great");
    std::cout<<std::endl;


    std::cout<<"Dostupné knihy:"<<std::endl;
    library.showAvailableBooks();
    std::cout<<std::endl;

}

Book::Book(string book)
{
    stringstream ss(book);
    string temp;
    getline(ss, temp, ';');
    id = stol(temp);
    getline(ss, nazev, ';');
    getline(ss, autor, ';');
    getline(ss, temp, ';');
    if (temp == "Available" or temp =="Available ")
    dostupnost = true;
    else
    dostupnost = false;
}

bool Book::operator <(const Book& obj) const
{
    return autor < obj.autor;
}

bool Book::operator ==(const Book& obj) const
{
    return id == obj.id;
}

void Book::setID(long id)
{
    this->id = id;
}

long Book::getID()
{
    return id;
}

bool Book::getDostupnost()
{
    return dostupnost;
}

string Book::getNazev()
{
    return nazev;
}

void Book::setDostupnost(bool dostupnost)
{
    this->dostupnost = dostupnost;
}

ostream& operator<<(ostream& out, const Book& obj)
{
    out<<obj.id<<";"<<obj.nazev<<";"<<obj.autor<<";"<<(obj.dostupnost ? "Available" : "Borrowed");
    return out;
}

Library::Library(string path_to_file)
{
    path = path_to_file;
    fstream fs;
    fs.open(path, ios::in);
    if (fs.is_open()) 
    {
        string linka;
        while (getline(fs, linka)) 
        {
            books.push_back(Book(linka));
        }
    }
    fs.close();
    books.sort();
}

void Library::addBook(Book book)
{
    if(find(books.begin(), books.end(), book) == books.end())
    {
        books.push_back(book);
        books.sort();
        cout<<"Kniha s id "<<book.getID()<<" byla pridana"<<endl;
    }
    else
    {
        cout<<"Kniha nemá unnikátní ID"<<endl;
    }
}

long Library::getUniqueId()
{
    long id = 1;
    for(auto it = books.begin(); it != books.end(); it++)
    {
        if(it->getID() > id)
        {
            id = it->getID() + 1;
        }
    }
    return id;
}

void Library::showAvailableBooks()
{
    for(auto it = books.begin(); it != books.end(); it++)
    {
        if(it->getDostupnost())
        {
            cout<<*it<<endl;
        }
    }
}

void Library::findBookAndBorrowIt(string name)
{
    int count = 0;
    for(auto it = books.begin(); it != books.end(); it++)
    {
        if(it->getNazev().find(name) != string::npos && it->getDostupnost())
        {
            cout<<*it<<endl;
            count++;
        }
    }
    if(count == 0)
    {
        cout<<"Nebyla nalezena žádní kniha s tímto jménem."<<endl;
    }
    else if(count == 1)
    {
        char odpoved;
        cout<<"Chcete si tuto knihu pujcit? (A/N)"<<endl;
        cin>>odpoved;
        if(odpoved == 'A' || odpoved == 'a')
        {
            for(auto it = books.begin(); it != books.end(); it++)
            {
                if(it->getNazev().find(name) != string::npos)
                {
                    it->setDostupnost(false);
                    cout<<"Kniha vypujcena"<<endl;
                }
            }
        }
    }
    else
    {
        cout<<"Nalezeno více knih, prosím upřesněte hedání:"<<endl;
        long id;
        cin>>id;
        for(auto it = books.begin(); it != books.end(); it++)
        {
            if(it->getID() == id)
            {
                char odpoved;
                cout<<"Chcete si tuto knihu pujcit? (a/n)"<<endl;
                cin>>odpoved;
                if(odpoved == 'a')
                {
                    for(auto it = books.begin(); it != books.end(); it++)
                    {
                        if(it->getNazev().find(name) != string::npos)
                        {
                            it->setDostupnost(false);
                            cout<<"Kniha vypujcena"<<endl;
                        }
                    }
                }
            }
        }
    }
}

ostream& operator<<(ostream& out, const Library & obj)
{
    for(auto it = obj.books.begin(); it != obj.books.end(); it++)
    {
        out<<*it<<endl;
    }
    return out;
}