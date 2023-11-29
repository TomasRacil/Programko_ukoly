#include "Event.h"//jelikož jsem nadefinoval knihovny v Event.h, tak už to tady nemusím řešit, jen includnu ten hlavičkový soubour
using namespace std;
Time::Time() //konstruktor který neočekává žádný vstup, proto se na každou hodnotu(jsou uložené v event.h) uloží 0
{
    this->minute = 0;
    this->hour = 0;
    this->day=0;
    this->month = 0;
    this->year = 0;
}

Time::Time(string time)//konstruktor očekává string(time), který musí rozložit na rok,měšíc,den,hodinu,minutu
{
    istringstream iss(time);
    iss>>year>>month>>day>>hour>>minute;

    /* string item;
    vector <int> items;
    stringstream time_ss(time);
    while (getline(time_ss, item, ' '))//Vezme stringstream - time_ss(do kterého jsme uložili prvnotní string time) a po mezerách rozdělí- ' '
    {
        items.push_back(stoi(item));//Každý prvek vezme a uloží do vektorového seznamu, vždy na poslední pozici;
    }

    this->minute = item[4]; //následně ukládám prvky na jednotlivých indexech do proměnných nadefinovaných v Event.h
    this->hour = item[3];
    this->day=item[2];
    this->month = item[1];
    this->year = item[0]; */

}

bool Time::operator < (const Time& obj) const//Vezmu klasický operátor <(menší než) a nadefinuju co bude porovnávat v této classe.
{
    if (year<obj.year) return true;//pokud je muj rok v levo menší než rok v pravo tak vrátí true
    else if(year>obj.year) return false;//pokud neplatí vrátí false
    else
    {
        if (month<obj.month) return true;//to stejné co nahoře jen s měsícem
        else if(month>obj.month) return false;
        else
        {
            if (day<obj.day) return true;
            else if(day>obj.day) return false;
            else
            {
                if (hour<obj.hour) return true;
                else if(hour>obj.hour) return false;
                else
                {
                    if (minute<obj.minute) return true;
                    else return false;
                }
            }
        }
    }
}

bool Time::operator > (const Time& obj)const
{
    if (year>obj.year) return true;//Dělá to stejné co operátor < jen s operátorem >(větší než)
    else if(year<obj.year) return false;
    else
    {
        if (month>obj.month) return true;
        else if(month<obj.month) return false;
        else
        {
            if (day>obj.day) return true;
            else if(day<obj.day) return false;
            else
            {
                if (hour>obj.hour) return true;
                else if(hour<obj.hour) return false;
                else
                {
                    if (minute>obj.minute) return true;
                    else return false;
                }
            }
        }
    }
}

bool Time::operator == (const Time& obj) const//Pokud se každá hodnota rovná, vrátí true, jinak vrátí false
{
    if (year == obj.year && month==obj.month && day == obj.day && hour == obj.hour && minute == obj.minute ) return true;
    return false;
} 

bool Time::operator != (const Time& obj)const//Pokud se všechny hodnoty rovnají, vráti false, jinak vrátí true, jelikož aby platilo !=, tak stačí aby se jedna nerovala.
{
    if (year == obj.year && month==obj.month && day == obj.day && hour == obj.hour && minute == obj.minute ) return false;
    return true;
}

 

ostream& operator << (ostream& out, const Time& obj)//představ si že přepíšeš cout<<"hello world", ale díky tomu, že přepíšeš to out<<, tak můžeš napsat cout<<Time a vypíše se to tak jak to je dole nadefinované
{
    out<<obj.year<<" "<<obj.month<<" "<<obj.day<<" "<<obj.hour<<" "<<obj.minute;
    return out;
}


 

Event::Event(string event)//konstruktor očekávajíci string event, což v texťáku, který zadal je 5 řádků
{
    stringstream event_ss(event);
    string item;
    vector<string>items;
    while(getline(event_ss, item, '\n'))//čte po řádcích a rozděluje je o "\n"(což je jako kdybys zmáčkla tab, neboli skočila na další řádek)
    {
        items.push_back(item);//uloží řádek na konec seznamu items (píšu tam item, jelikož jsem si udělal string item a tím pádem můj řádek se jmenuje item)
    }

    this->name = items[0];//uložím ze seznamu na prvím indexu(což je jméno eventu), do proměnné name.
    this->start_time = Time(items[1]);//jelikož start time je ve stringu a my víme, že potřebuje rozdělit na rok, měsíc, den, hodinu a minutu, tak můžu použít konstruktor pro strukturu, který jsem si již nadefinoval nahoře, aby se to převedlo.
    this->end_time = Time(items[2]);
    this->place = items[3];
    this->description = items[4];


} 

Event::Event(string name, string start_time, string end_time, string place, string description)//konstrukor, který očekává již všechny důležité věci rovnou dané, tím pádem nemusím procházer žádny texťák
{
    this->name = name;//tady jen ukládám name který jsem dostal nahoře(normálně napíšeš třeba "Zkouška"(musí být v " ", protože je to string), do proměnné která je uložená v event.h, proto pořád používám this->, jelikož se odkazuju na ten hlavičkový soubor(.h))
    this->start_time = Time(start_time);
    this->end_time = Time(end_time);
    this->place = place;
    this->description = description;
}

string Event::getName()
{
    return name;
}

Time* Event::getStartTime()
{
	return &start_time;
}

bool Event::operator < (const Event& obj) const
{
    if (start_time<obj.start_time) return true;//pokud je start_time menší než end_time tak to vrátí true;
    else if(start_time == obj.start_time && end_time<obj.end_time) return true;//pokud je start_time stejný, ale end_time je pořád menší, tak to taky vrátí true;
    return false;//pokud neplatí ani jedna z podmínek co jsou nahoře nepsané, tak to vrátí false.
}


bool Event::operator > (const Event& obj)const
{
    if (start_time>obj.start_time) return true;//to stejné co nahoře jen řešíme >(větší než)
    else if(start_time == obj.start_time && end_time>obj.end_time) return true;
    return false;
}

bool Event::operator == (const Event& obj)const
{
    if(start_time == obj.start_time && place==obj.place && name==obj.name) return true;//pokud jsou oba časy stejné, vrátí nám to true;
    return false;//pokud nejsou stejné vrátí nám to false
}

bool Event::operator != (const Event& obj)const
{
    if(start_time == obj.start_time && place==obj.place && name==obj.name) return false;//jelikož potřebujeme, aby se alespoň jeden čas lišil při použití "!=", tak můžeme říct, že pokud oba časy jsou stejné, tak to vrátí false.
    return true;//pokud není splněná podmínka u if, vrátí true.
}

 

ostream& operator << (ostream& out, const Event& obj)//zase přepisuju out<<, takže při použíti cout<<event, se vypíše vše, co jsem dole nadefinoval.
{
    out<<obj.name<<"\n";
    out<<obj.start_time<<"\n";
    out<<obj.end_time<<"\n";
    out<<obj.place<<"\n";
    out<<obj.description<<"\n";
    return out;
}

