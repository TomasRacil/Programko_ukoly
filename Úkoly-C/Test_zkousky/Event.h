#pragma once//musí být v hlavičkových souborech.
#include <iostream>//tohle napiš vždycky (in, out (cin, cout))
#include <vector>//vectorový seznam
#include <fstream>//fstream, potřeba pro getline(čtení z texťáku)
#include <sstream>//string stream, slouží k rozdělení stringu
#include <string>//nevím co t odělá ale pracuju se stringem, tak to tam radśi dám

using namespace std;

struct Time //nadefinovaní struktruy, píše se pouze v hlavičkov'm souboru (ZDE)
{ 
int minute; //jednotlivé proměnné

int hour; 

int day; 

int month; 

int year; 

 

Time(); //říkám, že existuje konstrutor, dále definuju v event.cpp

Time(string time); //to stejné

bool operator < (const Time& obj) const; //říkám že budu předělávat operátor <(menší než)

bool operator > (const Time& obj)const; 

bool operator == (const Time& obj) const; 

bool operator != (const Time& obj)const; 

 

friend ostream& operator << (ostream& out, const Time& obj);//budu předělávat jak se bude vypisovat daný event(out<<)

}; 

class Event //definijuju classu
{ 

private: //private (píšu proměnné)

string name; 

Time start_time; 

Time end_time; 

string place; 

string description; 

 

public: //public, píšu jednotlivé funkce

Event(string event); //konstrukor, definuju až v Event.cpp

Event(string name, string start_time, string end_time, string place, string description); 

string getName();

Time* getStartTime();

bool operator < (const Event& obj) const; //budu přepisovat operátor <(menší než)

bool operator > (const Event& obj)const; 

bool operator == (const Event& obj)const; //rovná se

bool operator != (const Event& obj)const; //nerovná se

 

friend ostream& operator << (ostream& out, const Event& obj); //výpis
friend class Calendar;//musí to tu být abych mohl v Calendar.cpp pracovat s private hodnotama od Event.h

};

