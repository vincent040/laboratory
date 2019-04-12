#ifndef PRODUCT_H
#define PRODUCT_H

// 商品
class product
{
public:
    product(float cost=0, float price=0)
        :_cost(cost), _price(price){}

    virtual void sold(int quantity, float discount)=0;

    static float totalAmount(){return _totalAmount;}
    float price()const{return _price;}
    float cost() const{return _cost;}

protected:
    static float _totalAmount; // 总销售额

    float _cost; // 成本
    float _price;// 售价
};


// 苹果
class apple : public product
{
public:
    apple(float cost=0, float price=0);
    void sold(int quantity, float discount);
    static float totalWeight(){return _totalWeight;} // 总共卖了多少斤

private:
    static float _totalWeight;
};

// 洗发水
class shampoo : public product
{
public:
    shampoo(float cost=0, float price=0);
    void sold(int quantity, float discount);
    static float totalCount(){return _totalCount;} // 总共卖了多少瓶

private:
    static float _totalCount;
};

#endif // PRODUCT_H
