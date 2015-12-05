// Lab6.cpp : Uses student ID to find and print their mark

#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"


void main()
{
	int ID[10] = { 101, 102, 103, 104, 105, 106, 107, 108, 109, 110 }; //Student ID Array
	int mark[10] = { 45, 67, 23, 91, 56, 42, 98, 12, 45, 86 }; //Student Mark Array
	char name[10][20] = { "Smith", "Jones", "Murphy", "Martin", "Maguire", "Byrne", "Reilly", "Coughlan", "Zenkevich", "Orlowska" };
	int check1; //Used to check user ID against database
	char check2[20] =""; //Used to check user surname against database
	char choice; //Initial Choice
	int j ; //loop counter and position in array
	char loop = 'y'; //loops the entire program

	while (loop == 'y')
	{
		printf("i/I - Search by ID\n");
		printf("s/S - Search by Surname\n");
		printf("q/Q - Quit\n");
		printf("Enter your choice: ");
		fflush(stdin);
		choice = getchar();
		choice = tolower(choice);

		if (choice == 'i')
		{
			printf("\nPlease enter your Student ID: ");
			scanf_s("%d", &check1);

			for (j = 0; j < 10; j++)
			{
				if (check1 == ID[j])
				{
					printf("\nID: %d\n", ID[j]);
					printf("Surname: %s\n", name[j]);
					printf("Mark: %d\n", mark[j]);
					printf("----------------------------------------------------------------------------\n");
					j--;
					break;
				}
			}

			if (j == 10)
			{
				printf("Your Student ID cannot be found. Please try again!\n");
				printf("----------------------------------------------------------------------------\n");
			}
		}

		else if (choice == 's')
		{
			printf("\nPlease enter your Surname: ");
			fflush(stdin);
			scanf_s("%s", check2, 20);

			for (j = 0; j < 10; j++)
			{
				if (!strcmp(check2, name[j]))
				{
					printf("\nID: %d\n", ID[j]);
					printf("Surname: %s\n", name[j]);
					printf("Mark: %d\n", mark[j]);
					printf("----------------------------------------------------------------------------\n");
					j--;
					break;
				}
			}

			if (j == 10)
			{
				printf("Your Surname cannot be found. Please try again!\n");
				printf("----------------------------------------------------------------------------\n");
			}
		}
		printf("Would you like to check another mark? (y/n): ");
		fflush(stdin);
		loop = getchar();
		printf("----------------------------------------------------------------------------\n\n");
	}


}

