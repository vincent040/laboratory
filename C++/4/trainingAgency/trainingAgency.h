#ifndef TRAININGAGENCY_H
#define TRAININGAGENCY_H

#include <string>

using std::string;

/******** 学校 ********/
class school
{
private:
    int classes; // 班级数
    string OAA;  // 教务处

public:
    school();

    void termBegin(); // 开学
};

/******** 公司 ********/
class company
{
private:
    float profitRate;
    string board;

public:
    company();

    void payTaxes();
};

/******** 培训机构 ********/
class trainingAgency : public school, public company
{
public:
    trainingAgency();

};

#endif // TRAININGAGENCY_H
