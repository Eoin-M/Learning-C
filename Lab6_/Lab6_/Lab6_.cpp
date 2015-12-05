// Lab6_.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include "stdio.h"


void main()
{
	int custnum[2][10] = { 
			{ 1234, 2345, 3456, 4567, 5678, 6789, 7890, 8745, 9823 },
			{ 1112, 1113, 1114, 1115, 1116, 1117, 1118, 1119, 1110 },
	};
	int custcheck, pincheck;
	int i,j; //Loop counters

	printf("Enter your bank account number : ");
	scanf_s("%d", &custcheck);

	for (i = 0; i < 10; i++)
	{
		if (custcheck == custnum[0][i]) break;
	}

	if (custcheck == custnum[0][i])
	{
		for (j = 1; j <= 3; j++)
		{
			printf("Enter you pin number. Attempt #%d: ", j);
			scanf_s("%d", &pincheck);

			if (pincheck == custnum[1][i]) { printf("Congrats\n"); break; }
		}
	}

}

