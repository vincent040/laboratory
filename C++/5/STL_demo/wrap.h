#ifndef WRAP
#define WRAP

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::vector;
using std::list;
using std::stack;
using std::set;
using std::map;
using std::pair;

template <typename T>
void show(T container)
{
    for(auto p = container.begin();
        p != container.end(); p++)
    {
        cout << *p << "\t";
    }
    cout << endl;
}

extern void dec2oct();		// vector
extern void rearrange();	// list
extern void arithmetic();	// stack
extern void rankingScore();	// set
extern void contacts();		// map

#endif // WRAP

