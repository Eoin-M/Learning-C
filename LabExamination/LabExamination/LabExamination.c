// LabExamination.cpp

#include "stdafx.h"
#include "stdio.h"
#include "string.h"

typedef struct
{
	int year;
	double price[12];
	double average;
} electricity;
electricity records[30];

double maxAvg = 0; //holds the maximum average for highest year
int maxAvgYear; //holds the year of the max average

double max = 0; //holds the highest price of all the months
int monthNum; //holds the numerical value of the month of the highest price
int year; //holds the year of the highest price

int openFile();
void highestPrice(); //finds the name of the month of the highest price based on monthNum and prints the information

void main()
{
	int choice;

	if (openFile()) return; //returns 1 and exits the program if the file cannot be opened

	while (1) //infinite loop until the user enters '0'
	{
		puts("1. Find the month with the highest price\n2. Find the year with the highest average price\n0. Exit");
		fflush(stdin);
		scanf("%d", &choice);
		if (choice < 0 || choice > 2) { puts("Invalid Selection!\n"); continue; }
		switch (choice)
		{
		case 0: return;
		case 1: highestPrice(); break;
		case 2:{
			printf("Highest Annual Average Price was %lf in %d\n\n", maxAvg, maxAvgYear);
			break;
		}
		}
	}
}

int openFile()
{
	FILE *ptr;
	char waste[200];
	int i, j;
	double total = 0;

	if ((ptr = fopen("electricity.txt", "r")) == NULL)
	{
		puts("File cannot be opened!");
		return 1;
	}
	fgets(waste, 200, ptr); //reads in the 4 waste string lines at the start of the file
	fgets(waste, 200, ptr);
	fgets(waste, 200, ptr);
	fgets(waste, 200, ptr);

	for (i = 0;; i++)
	{
		fscanf(ptr, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", &records[i].year, &records[i].price[0],
			&records[i].price[1], &records[i].price[2], &records[i].price[3], &records[i].price[4],
			&records[i].price[5], &records[i].price[6], &records[i].price[7], &records[i].price[8],
			&records[i].price[9], &records[i].price[10], &records[i].price[11]);
		if (records[i].year == 0) break; //once the program reads the 0 at the end of the file, it breaks out of the reading loop

		for (j = 0; j < 12; j++)
		{
			total += records[i].price[j];
			if (records[i].price[j] > max) { //checks if the price this year is greater than the current max
				max = records[i].price[j]; monthNum = j; year = records[i].year; //recors the new max price and the month and year in which it is in
			}
		}

		records[i].average = total / (double)12; //average is total price divided by the 12 months of the year
		total = 0; //reset total varibale

		if (records[i].average > maxAvg) maxAvg = records[i].average; maxAvgYear = records[i].year; //maxAvg holds the highest average price, maxAvgYear holds the year of the max average price
	}
	fclose(ptr);
	return 0;
}

void highestPrice()
{
	printf("Highest Price Month was %lf in ", max);
	switch (monthNum) //uses the numerical value of the months to select the correct string name to print to user
	{
	case 0: printf("January"); break;
	case 1: printf("February"); break;
	case 2: printf("March"); break;
	case 3: printf("April"); break;
	case 4: printf("May"); break;
	case 5: printf("June"); break;
	case 6: printf("July"); break;
	case 7: printf("August"); break;
	case 8: printf("September"); break;
	case 9: printf("October"); break;
	case 10: printf("November"); break;
	case 11: printf("December"); break;
	}
	printf(" of %d\n\n", year);
}