#include <iostream>

using namespace std;

int main()
{
    int VyskaKoruny, VyskaKmene;
    cout<<"Zadejte výšku koruny: ";
    cin>>VyskaKoruny;
    cout<<"Zadejte výšku kmene: ";
    cin>>VyskaKmene;

    for(int i=0; i<VyskaKoruny; i++)
    {
        for(int j=0; j<VyskaKoruny-i; j++)
        {
            cout<<" ";
        }
        for(int j=0; j<2*i+1;j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
    for(int i=0; i<VyskaKmene;i++)
    {
        for(int j=0; j<VyskaKoruny-1; j++)
        {
            cout<<" ";
        }
        for(int j=0; j<3;j++)
        {
            cout<<"|";
        }
        cout<<endl;;
    }
}