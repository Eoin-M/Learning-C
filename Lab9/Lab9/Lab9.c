#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "accounts.h"

void main()
{
	struct account accounts[10];
	setupAccounts(accounts, 10);
	printf("Balances before calculations: \n");
	printAccounts(accounts, 10);
	updateAccounts(accounts, 10);
	printf("Balances after calculations: \n");
	printAccounts(accounts, 10);
}