#include "wrap.h"

#include <algorithm>

class comp
{
public:
    bool operator()(const string &lh, const string &rh)
    {
        return lh<rh;
    }
};

void show(map<string, string, comp> friends)
{
    cout << "===== 通讯录 =====" << endl;
    for(map<string, string>::iterator p = friends.begin();
        p != friends.end(); p++)
    {
        cout << p->first << "：" << p->second << endl;
    }
    cout << endl;
}


void contacts()
{
    map<string, string, comp> friends;

    // 插入一些朋友通信信息
    friends["张三"] = "13822558888";
    friends["李四"] = "18612345678";
    friends["张三疯"] = "18000568900";

    friends["Rose"] = "18946545763";
    friends["Jack"] = "18855554545";
    friends["Bill"] = "18913487644";
    friends.insert(pair<string, string>("王五", "18656569898"));

    // 插入一个重复的人名：
    pair< map<string, string, comp>::iterator, bool> ret;
    ret = friends.insert(pair<string, string>("张三", "18899999999"));
    if(ret.second)
        cout << "插入成功" << endl;
    else
        cout << "插入失败" << endl;

    show(friends);

    // 查询某人的电话
    cout << "你想查询谁的电话？" << endl;
    string name;
    cin >> name;

    if(friends.find(name) == friends.end())
        cout << "查无此人！" << endl;
    else
        cout << "他的电话是：" << friends[name] << endl;
}
