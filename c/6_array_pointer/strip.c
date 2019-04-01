#include <stdio.h>
#include <string.h>

#define REDUNDANT -1

void strip(char *str)
{
	if(str == NULL)
		return;

	int i, j;
	char *p = str;

	// mark all redundant letters
	for(i=1; str[i] != '\0'; i++)
	{
		for(j=0; j<i; j++)
		{
			if(p[j] == str[i])
			{
				str[i] = REDUNDANT;
				break;
			}
		}
	}

	/*
	** locate the first redundant letter and
	** the first common letter after it.
	*/
	int redun = 0, common = 0;
	for(i=1; str[i] != '\0'; i++)
	{
		if(str[i] != REDUNDANT)
			continue;

		redun = i;
		while(str[i] == REDUNDANT)
			i++;

		common = i;
		break;
	}

	// no repeat letter
	if(redun == 0)
		return;

	/*
	** move all common letters forward
	*/
	while(str[common] != '\0')
	{
		if(str[common] == REDUNDANT)
		{
			common++;
			continue;
		}
		str[redun++] = str[common];
		str[common++] = REDUNDANT;
	}
	str[redun] = '\0';
}

int main(void)
{
	char buf[64];
	fgets(buf, 64, stdin);

	strip(buf);
	printf("%s", buf);
	
	return 0;
}
