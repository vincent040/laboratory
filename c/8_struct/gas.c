#include <stdio.h>

struct gas
{
	float distance;
	float gals;
	float mpg; // mpg = distance * gals
};

//pass the whole structure to this function
struct gas deal_with_struct(struct gas bill)
{
	bill.mpg = bill.distance * bill.gals;
	return bill;
}

//pass the pointer to this function
void deal_with_pointer(struct gas *pbill)
{
	pbill->mpg = pbill->distance * pbill->gals;
}

int main(void)
{
	struct gas my_bill;
	my_bill.distance = 1.2;
	my_bill.gals = 3.4;

	my_bill = deal_with_struct(my_bill);
	printf("my bill's mpg: %f\n", my_bill.mpg);

	struct gas your_bill;
	your_bill.distance = 1.2;
	your_bill.gals = 3.4;

	deal_with_pointer(&your_bill);
	printf("your bill's mpg: %f\n", your_bill.mpg);

	return 0;
}
