#include "hlist.h"

typedef int ht_datatype;

typedef struct node
{
	ht_datatype data;
	struct hlist_node hlist;
}htnode, *linkht;

void ht_insert(linkht *ht, ht_datatype data)
{
	linkht new = malloc(sizeof(htnode));
	new->data = data;
	(new->hlist)

	unsigned long hvalue;
	hvalue = (data*data) >> 19;

	if(ht[hvalue] != NULL)
	{
		
	}
}

int main(void)
{
	struct hlist_head *ht = (struct hlist_head *)calloc(8, 1024);
	srand(time(NULL));

	int i;
	for(i=0; i<8 * 1024; i++)
		ht_insert(ht, rand() % 10000);

	while(1)
	{
		scanf("%d", &i);
		search(ht, i);
	}
	
	return 0;
}
