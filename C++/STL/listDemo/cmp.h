#ifndef CMP_H
#define CMP_H

#include "student.h"

template <typename T>
class cmp
{
public:
    enum order{ASC/*升序*/, DES/*降序*/} _ord;
    cmp(enum order o=ASC);

    bool operator()(const T& rh1, const T& rh2);
};

// 类模板中的类方法定义必须放在头文件中，否则无法编译
// 因此CPP文件在编译成.o文件之时，模板尚未实例化
template <typename T>
cmp<T>::cmp(order o)
    :_ord(o)
{}

template <typename T>
bool cmp<T>::operator ()(const T& rh1, const T& rh2)
{
    if(_ord == ASC)
        return rh1 < rh2;
    else
        return rh1 > rh2;
}

template <>
bool cmp<student<string, int> >::operator ()(const student<string, int>& rh1, const student<string, int>& rh2)
{
    if(_ord == ASC)
        return rh1.age() < rh2.age();
    else
        return rh1.age() > rh2.age();
}

#endif // CMP_H
