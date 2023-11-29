#include "Calendar.h"

using namespace std;
Calendar::Calendar(string name)
{
    this->name = name; //ukládám name, který zadám do konstrokturu do name který je v .h
    this->path = name + ".txt"; //jelikož path, je cesta k souboru, a řesím to pŕes texťák, tka to bude vždy .txt, takže říkám že ten soubor se bude jmenovat name.txt(to name zadám)
} 

Calendar::Calendar(string name, string path)
{
    this->name = name;//stejně jak nahoře
    this->path = path;//tentokrát path znám(z toho konstruktoru), takže to můžu přímo uložit
    string event;
	ifstream file;
	file.open(path);
	string line;
	while (getline(file, line)) {
		if (line != "") {
			event += line + '\n';
		}
		else {
			this->events.push_back(Event(event));
			event.erase();
		}
	}
	if (!event.empty()) {
		this->events.push_back(Event(event));
		event.erase();
	}
	this->events.sort();
}

void Calendar::addEvent(Event event)//funkce, která nám přídá event(ten zadáme), k eventům(máme proto nadefinovaný list)
{
    if (find (events.begin(), events.end(), event) == events.end())//find () dělá to, že dovnitř napíšeš (první prvek, poslední prvek, a prvek který chceš projíždět(event), == events.end(), by mělo potrvrzovat, že even ještě není v seznamu)
        events.push_back(event);//pokud je splněný if(even ještě neexistuje, tak ho přídám na konec seznamu)
    else
        cout<<"Event is already in calendar!!"; //pokud if není splněný(event existuje), tak vypíšu, že uź existuje
    events.sort();//Seřadí seznam podle pořádí, protože jsem si v event.cpp přetížil operátor <(menší než), tak to můžu použít
}

Calendar Calendar::findEvent(string name)
{
    Calendar foundEvents = Calendar("Events named " + name);//pomocí konstruktoru Calendar jsem si vytvořil foundEvents
    for (Event e : events)//projede se seznam events, každá položka v events se uloží do proměnné Event e
    {
        if (e.name == name)//za normalních okolností e.name fungovat nebude, jelikož je to privátní hodnota v Event.h, ale jelikoz jsme tam napsali "friend class Calendar", tak může Calendar přistupovat k private hodnotám od Eventu
            foundEvents.addEvent(e);//přidá se k found events

    }
    return foundEvents;
} 

Calendar Calendar::findEventsAfter(Time time)
{   
    stringstream time_s;
	time_s << time;
    Calendar foundEvents = Calendar("Events after: " + time_s.str());
    for (Event e : events)
    {
        if (e.start_time > time)
        foundEvents.addEvent(e);
    }
    return foundEvents;


}

Calendar Calendar::findEventsBefore(Time time)
{
    stringstream time_s;
	time_s << time;
    Calendar foundEvents = Calendar("Events before: "+ time_s.str());
    for (Event e : events)
    {
        if (e.start_time < time)
        foundEvents.addEvent(e);
    }
    return foundEvents;
}

 

ostream& operator << (ostream& out, const Calendar& obj)
{
    out<<obj.name<<endl;
    for (Event e : obj.events)
    {
        out<<e<<endl<<endl;
    }
    return out;

}
