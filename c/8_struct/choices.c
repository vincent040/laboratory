#include <stdio.h>

enum choices
{
	no = 0,
	yes = 1,
	maybe = 2
};

int main(void)
{
	int my_choices;

	printf("pls input 0, 1 or 2 stand for no, yes and maybe: ");
	scanf("%d", &my_choices);

	switch(my_choices)
	{
	case no:
		printf("no\n");
		break;
	case yes:
		printf("yes\n");
		break;
	case maybe:
		printf("maybe\n");
		break;
	default:
		printf("invalid arguments.\n");
	}

	return 0;
}
