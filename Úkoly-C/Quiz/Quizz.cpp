#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Question {
    string question;
    string a;
    string b;
    string c;
    char correctAnswer;
};


int main()
{
    fstream myFile;
    string radek;
    Question question;
    int score = 0;
    vector <Question>Otazky;

    myFile.open("questions.txt", ios::in);
    if(myFile.is_open())
    {
        while(getline(myFile, radek))
        {
            stringstream ss(radek);
            getline(ss, question.question, ';' );
            getline(ss, question.a, ';' );
            getline(ss, question.b, ';' );
            getline(ss, question.c, ';' );
            ss>>question.correctAnswer;
            Otazky.push_back(question);
            
        }
        myFile.close();

        for(int i=0; i<3;i++)
        {
        cout<<Otazky[i].question<<endl;
        cout<<"a)"<<Otazky[i].a<<endl;
        cout<<"b)"<<Otazky[i].b<<endl;
        cout<<"c)"<<Otazky[i].c<<endl;
        cout<<"Zadejte odpověď: ";
        char odpoved;
        cin>>odpoved;
        if(odpoved==Otazky[i].correctAnswer)
        {
            cout<<"Správně"<<endl<<endl;
            score++;
        }
        else
            cout<<"Špatně"<<endl<<endl;
        }
    } 
    cout<<"Vaše skóre je: "<<score<<endl;
    getchar(); getchar();
    return 0;
}  
