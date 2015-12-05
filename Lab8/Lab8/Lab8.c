#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include "time.h"
#define SIZE 10

char custName[SIZE][30]; // array of customer names
float custBal[SIZE]; // array of customer balances

void initArrays(); // use any method you think useful to put sample data in the customer name and balance arrays
void printCustomer(int i); // prints the name and balance of customer[i]
int findHighest(); // finds the index of the customer with the highest balance
int findLowest(); // finds the index of the customer with the lowest balance
float findAverage(); // finds the average of all customer balances

void main()
{
	int i;
	float avg;
	initArrays();
	i = findHighest();
	printCustomer(i);
	i = findLowest();
	printCustomer(i);
	avg = findAverage();
	printf("\nAverage Balance = %.2f \n\n", avg);
}


void initArrays()
{
	int j; //loop counter

	for (j = 0; j < SIZE; j++)
	{
		sprintf(custName[j], "Customer:%d", j + 1);
		custBal[j] = rand() % 1000;
	}
}


void printCustomer(int i)
{
	printf("The balance of %s is %.2f \n\n", custName[i], custBal[i]);
}


int findHighest()
{
	int j; //loop counter
	float max = custBal[0];
	int pos=0;

		for (j = 1; j < SIZE; j++)
		{
			if (max < custBal[j])
			{
				max = custBal[j];
				pos = j;
			}
		}

	return pos;
}


int findLowest()
{
	int j; //loop counter
	float min = custBal[0];
	int pos=0;

	for (j = 1; j < SIZE; j++)
	{
		if (min > custBal[j])
		{
			min = custBal[j];
			pos = j;
		}
	}

	return pos;
}

float findAverage()
{
	int j; //loop counter
	float avg = 0;

	for (j = 0; j < SIZE; j++)
	{
		avg = avg + custBal[j];
	}

	avg = avg / SIZE;

	return avg;
}
