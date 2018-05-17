#include "product.h"

float product::_totalAmount = 0;
float apple::_totalWeight = 0;
float shampoo::_totalCount= 0;


apple::apple(float cost, float price)
{
    _cost = cost;
    _price= price;
}

void apple::sold(int quantity, float discount)
{
    _totalAmount += quantity * this->price() * discount;
    _totalWeight += quantity;
}

shampoo::shampoo(float cost, float price)
{
    _cost = cost;
    _price= price;
}

void shampoo::sold(int quantity, float discount)
{
    _totalAmount += quantity * this->price() * discount;
    _totalCount  += quantity;
}
