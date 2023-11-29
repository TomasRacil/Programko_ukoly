#include <iostream>

using namespace std;

int Faktorial(int cislo);
int main()
{
    int cislo;
    int faktorial=1;
    cout<<"Zadejte cislo: ";
    cin>>cislo;
    for(int i=1; i<=cislo; i++)
    {
        faktorial*=i;
    }
    cout<<"Faktorial cisla "<<cislo<<" je: "<<faktorial<<endl;

   
}
