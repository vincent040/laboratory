#ifndef KITTY
#define KITTY

#include <iostream>

using namespace std;

enum color{brown, white, gold, variegated/*杂色*/};


class kitty
{
public:
    kitty(float w, char g, enum color c)
        :weight(w), gender(g), furColor(c){}

    void eat();
    void sleep()const{cout << "睡觉..." << endl;}
    void actingCute()const{cout << "喵~~~" << endl;}

    void showInfo()const;

private:
    float weight;
    char gender;
    enum color furColor;
};

#endif // KITTY

