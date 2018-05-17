#include "kitty.h"

void kitty::eat()
{
    cout << "吃猫粮..." << endl;
    weight += 0.1;

    if(weight >= 3.0)
        cout << "警告！你家猫太肥了！当前体重："
             << weight << "kg" << endl;
}

void kitty::showInfo()const
{
    cout << "体重：" << weight << "kg" << endl;
    cout << "性别：" << (gender=='m' ? "公" : "母") << endl;

    cout << "毛色：";

    switch(furColor)
    {
    case brown:
        cout << "棕色";
        break;
    case white:
        cout << "白色";
        break;
    case gold:
        cout << "金色";
        break;
    case variegated:
        cout << "杂色";
        break;
    }
    cout << endl;
}
