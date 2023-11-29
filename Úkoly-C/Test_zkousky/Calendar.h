#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Event.h"//tady musim includnovou event.h, protože budu tvořit kalendár, z těch jednotlivých eventů, takže k tomu potřebuju přístup od tud

using namespace std;

class Calendar 
{ 

private: 

string name; 

string path; 

list<Event> events; //list očekávajíci Event

 

public: 

Calendar(string name); //konstruktor, zase říkám, jen že existuje, definuje se v calendar.cpp

Calendar(string name, string path); 

void addEvent(Event event); //funkce, která bude přidávat event do kalendáře

Calendar findEvent(string name); //hledá daný event, podle jména

Calendar findEventsAfter(Time time); //hledá eventy po tom čas, který zadám

Calendar findEventsBefore(Time time); //hledá eventy před tím časem, který zadámto je 

 

friend std::ostream& operator << (ostream& out, const Calendar& obj); 
};

