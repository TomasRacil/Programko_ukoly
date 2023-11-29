#include <iostream>  //cout, cin
#include <string>   //string (text)
#include <fstream>
#include <vector>

using namespace std;

int main()
{
   fstream myFile;
   vector<int> cisla;
    myFile.open("2000.txt", ios::in);
    if (myFile.is_open()){
        string radek;
        while (getline(myFile,radek))
        {
            cisla.push_back(stoi(radek));                                         
        }
        myFile.close();
    }
    for (int i = 0; i < cisla.size(); i++) {
        for (int j = 0; j < cisla.size(); j++) {
            for(int k=0; k<cisla.size(); k++){

            
            if (cisla[i] + cisla[j] + cisla[k] == 2020) {
                // Vynásob čísla mezi sebou
                int soucin = cisla[i] * cisla[j] * cisla[k];
                cout << cisla[i] << " + " << cisla[j] <<" "<<cisla[k]<<" = 2020"<< endl;
                cout << "Jejich součin je: " << soucin << endl;
                return 0;
            }
            }
        }
    }
    getchar(); getchar();
    return 0;
}