#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "accounts.h"
#include "time.h"

// sets up the array of accounts with random balances and account numbers
void setupAccounts(struct account accounts[], int num) //num = 10
{
	int i, j, check = 0; //loop counters and repeated number check
	srand(time(NULL));

	for (i = 0; i < num; i++)
	{
		accounts[i].num = (rand() % 100) + 1;
		if (i > 0)
		{
			for (check = 0; check == 0;)
			{
				for (j = 0; j < i; j++)
				{
					if (accounts[i].num == accounts[j].num)	{ accounts[i].num = rand() % 100; check = 0; }
					else check = 1;
				}
			}
		}

		accounts[i].balance = rand() % 10000;
		accounts[i].interest = 0;
		accounts[i].tax = 0;
	}
}

// uses calcInterest and calcTax to calculate the interest and tax, and update the account balances
void updateAccounts(struct account accounts[], int num)
{
	int i; //loop variable

	for (i = 0; i < num; i++)
	{
		accounts[i].interest = calcInterest(accounts[i].balance);
		accounts[i].tax = calcTax(accounts[i].interest);
		accounts[i].balance = accounts[i].balance + (accounts[i].interest - accounts[i].tax);
	}
}

// calculates the interest on the balance, using the interest rate defined in accounts.h
double calcInterest(double balance)
{
	return(balance * interestRate);
}

// calculates the tax on the interest, using the tax rate defined in accounts.h
double calcTax(double interest)
{
	return(interest * taxRate);
}

// uses printAccount to print out an array of accounts
void printAccounts(struct account accounts[], int num)
{
	int i; //loop counter
	printf("\nAccount: \tBalance: \tIntrest: \tTax: \n");
	printf("-------- \t-------- \t-------- \t-------- \n");

	for (i = 0; i < num; i++)
	{
		printAccount(accounts[i]);
	}
	printf("----------------------------------------------------------\n\n");
}

// prints an individual account
void printAccount(struct account anAccount)
{
	printf("%8d \t%8.2lf \t%8.2lf \t%8.2lf \n", anAccount.num, anAccount.balance, anAccount.interest, anAccount.tax);
}