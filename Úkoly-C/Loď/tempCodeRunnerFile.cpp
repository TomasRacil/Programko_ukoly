#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Lodicka
{
    private:
    int north,east,deg;
    

    public:
    void turn(char smer, int stupne)
    {
        switch (smer)
        {
        case 'R': stupne-=90; break;
        case 'L': stupne+=90; break;
        default: stupne;
        }

        if (stupne<0)
        {
            stupne+=360;
        }
        else if (stupne>360)
        {
            stupne-=360;
        }
    }

    void move(char smer, int vzdalenost)
    {
        switch (smer)
        {
        case 'N': north+=vzdalenost; break;
        case 'S': north-=vzdalenost; break;
        case 'E': east+=vzdalenost; break;
        case 'W': east-=vzdalenost; break;
        case 'F':
        if (deg == 0) 
            east += vzdalenost;
        else if (deg == 90) 
            north += vzdalenost;
        else if (deg == 180) 
            east -= vzdalenost;
        else if (deg == 270) 
            north -= vzdalenost;break;  
        default: vzdalenost;
        }
    }

    void print_pos()
    {
        cout<<"North: "<<north<<endl;
        cout<<"East: "<<east<<endl;
        cout<<"Deg: "<<deg<<endl;
    }


};


int main()
{
    fstream myFile;
    vector<char> souradnice;
    vector<int> pohyb;
    string radek;
    Lodicka lod;
    char smer;
    int pohyb1;
    myFile.open("data.txt", ios::in);
    if (myFile.is_open())
    {
        
        while (getline(myFile,radek))
        {
            stringstream ss(radek);
            ss >> smer >> pohyb1;
            pohyb.push_back(pohyb1);
            souradnice.push_back(smer);
                                                     
        }
        myFile.close();
    }

    for (int i = 0; i < souradnice.size(); i++)
    {
        lod.turn(souradnice[i],pohyb[i]);
        lod.move(souradnice[i],pohyb[i]);
        
    }
    lod.print_pos();


    return 0;
}