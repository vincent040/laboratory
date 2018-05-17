#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define SIZE 20

typedef int datatype;

struct node
{
	datatype data;
	struct node *next;
};

typedef struct
{
	unsigned long table_size;
	struct node **table_entry;

}hash_table;

void show(hash_table *ht, unsigned long pos, datatype data);

hash_table *init_ht(unsigned long size)
{
	hash_table *ht = malloc(sizeof(hash_table));
	ht->table_size = size;
	ht->table_entry = calloc(size, sizeof(struct node *));

	return ht;
}

void hash_add(datatype data, hash_table *ht)
{
	// 使用保留除数法，获得哈希地址（即数组的下标值）
	unsigned long hash_addr = data % (SIZE-1);

	struct node *new = malloc(sizeof(struct node));
	new->data = data;
	new->next = NULL;

	show(ht, hash_addr, data);
	printf("=================================\n");

	// 1：该哈希地址可用，直接将新节点放进去
	if(ht->table_entry[hash_addr] == NULL)
	{
		ht->table_entry[hash_addr] = new;
	}
	// 2：该哈希地址不可用，将新节点链到冲突链表的末尾
	else
	{
		struct node *p = ht->table_entry[hash_addr];
		while(p->next != NULL)
		{
			p = p->next;
		}
		p->next = new;
	}
}

void show(hash_table *ht, unsigned long pos, datatype data)
{
	struct node *p;

	int i;
	for(i=0; i<ht->table_size; i++)
	{
		p = ht->table_entry[i];

		printf("table_entry[%d]: ", i);

		if(p != NULL)
		{
			struct node *q = p;
			while(q != NULL)
			{
				printf("%d\t", q->data);
				q = q->next;
			}
		}
	
		if(pos == i)
		{
			printf("\t <-- %d\n", data);
		}
		else
		{
			printf("\n");
		}
	}
}

int main(void)
{
	hash_table *ht = init_ht(SIZE);

	srand(time(NULL));
	int i;
	for(i=0; i<10; i++)
	{
		hash_add(rand()%1000, ht);
		sleep(1);
	}
	show(ht, -1, -1);

	// 利用已经设计好的哈希函数和解决冲突的办法，查表

	/* add your code here */

	return 0;
}
