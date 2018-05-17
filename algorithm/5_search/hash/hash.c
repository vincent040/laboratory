#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct
{
	int data;
}hash_node;

typedef struct
{
	unsigned size;
	hash_node *table;
}hash_table;

hash_table *init_ht(unsigned size)
{
	hash_table *ht = malloc(sizeof(hash_table));
	
	ht->size = size;
	ht->table = calloc(size, sizeof(hash_node));

	return ht;
}

void show(int data, hash_table *ht, unsigned hash_addr)
{
	printf("=====================================\n");
	int i;
	for(i=0; i<ht->size; i++)
	{
		printf("table[%d]:", i);

		i==hash_addr && ht->table[i].data==0 ?
		printf("\t<==%d\n", data) :
		(
			i==hash_addr ?
			printf(" %d\t<==%d\n", ht->table[i].data, data) :
			(
				ht->table[i].data==0 ?
				printf("\n") :
				printf(" %d\n", ht->table[i].data)
			)
		);
	}
	printf("=====================================\n");
}

unsigned hash(int data, hash_table *ht)
{
	unsigned hash_addr = data % ht->size;
	show(data, ht, hash_addr);
	sleep(1);

	return hash_addr;
}

unsigned add_hnode(hash_node *newnode, hash_table *ht)
{
	unsigned hash_addr = hash(newnode->data, ht);

	while(ht->table[hash_addr].data != 0)
	{
		hash_addr = (hash_addr+1) % ht->size;
		show(newnode->data, ht, hash_addr);
		sleep(1);
	}

	ht->table[hash_addr] = *newnode;
	return hash_addr;
}

int search(hash_table *ht, int data)
{
	unsigned hash_addr = hash(data, ht);

label:
	ht->table[hash_addr].data==0 ?
	return -1 :
	(
		ht->table[hash_addr].data==data ?
		return hash_addr:
		hash_addr = (hash_addr+1) % ht->size, goto label;
	);
}

int main(void)
{
	hash_table *ht;
	ht = init_ht(5);

	srand(time(NULL));
	int i;
	unsigned hash_addr;
	hash_node *newnode;
	for(i=0; i<5; i++)
	{
		newnode = malloc(sizeof(hash_node));
		newnode->data = rand() % 1000;

		hash_addr = add_hnode(newnode, ht);
	}
	show(newnode->data, ht, -1);

	printf("input a number:");
	scanf("%d", &i);

	int index = search(ht, i);

	index == -1 ?
	printf("Not Found!\n") :
	printf("index: %d\n", index);

	return 0;
}
