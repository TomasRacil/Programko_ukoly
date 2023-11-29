#include <iostream>

using namespace std;

class Shape
{
    public:
        Shape();
};


class Square:public Shape
{
    private:
        int a;
    public:
        Square();
        Square(int a);
        int getA();
        double obvod();
        double obsah();
        void vypis();
};

class Rectangle:public Square
{
    private:
        int a;
        int b;
    public:
        Rectangle();
        Rectangle(int a, int b);
        int getB();
        double obvod();
        double obsah();
        void vypis();

};

class Cube:public Square
{
    private:
        int a;
    public:
        Cube();
        Cube(int a);
        double objem();
        void vypis();

};

int main()
{
    Square sq = Square(5);
    Rectangle rq = Rectangle(5, 2);
    Cube c = Cube(5);

    sq.vypis();
    rq.vypis();
    c.vypis();

    return 0;
}

Shape::Shape()
{
}

Square::Square():Shape()
{
}

Square::Square(int a)
{
    this->a = a;
}

double Square::obvod()
{
    return getA()*4;
}

double Square::obsah()
{
    return getA()*getA();
}

int Square::getA()
{
    return a;
}

void Square::vypis()
{
    cout<<"Čtverec: "<<endl;
    cout<<"Obsah: "<<obsah()<<endl;
    cout<<"Obvod: "<<obvod()<<endl;
}

Rectangle::Rectangle()
{
}
Rectangle::Rectangle(int a, int b):Square(a)
{
    this->b = b;
}
int Rectangle::getB()
{
    return b;
}

double Rectangle::obsah()
{
    return getA()*getB();
}

double Rectangle::obvod()
{
    return 2*getA()+2*getB();
}

void Rectangle::vypis()
{
    cout<<"Obdelnik:"<<endl;
    cout<<"Obsah: "<<obsah()<<endl;
    cout<<"Obvod: "<<obvod()<<endl;
}

Cube::Cube(){};
Cube::Cube(int a):Square(a)
{
    this->a = a;
}
double Cube::objem()
{
    return obsah()*getA();
}
void Cube::vypis()
{
    cout<<"Kostka:"<<endl;
    cout<<"Objem: "<<objem()<<endl;
}

