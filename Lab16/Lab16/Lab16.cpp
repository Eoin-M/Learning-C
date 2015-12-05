// Lab16.cpp  I've edited the text file to remove the unneccessary quotation marks and spaces

#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

struct data {
	char orderDate[81];
	int year;
	char region[81];
	char rep[81];
	char item[81];
	int units;
	float unitCost;
	float total;
};

struct data line[50];

void region(struct data line[50], int end);
void rep(struct data line[50], int end);
void item(struct data line[50], int end);
void year(struct data line[50], int end);

int main()
{
	FILE *fp;
	char waste[81]; //initial unimportant line
	char temp[81];
	char del[2] = "/"; //delimiter
	char *tok; //token 
	int i; //array position counter
	int choice;

	fp = fopen("SampleData.txt", "r");

	if (fp == NULL) {
		puts("Can't open file!\n");  return 0;
	}

	fgets(waste, 200, fp);

	for (i = 0; !feof(fp); i++) //loop fils array with file data
	{
		fscanf(fp, "%s\t%s\t%s\t%[^\t]\t%d\t%f\t%s\n", line[i].orderDate, line[i].region, line[i].rep, line[i].item, &line[i].units, &line[i].unitCost, temp);
		line[i].total = atof(temp); //total can contain a comma
		tok = strtok(line[i].orderDate, del);
		
		while (tok != NULL)
		{
			line[i].year = atoi(tok); //only need to save year
			tok = strtok(NULL, del);
		}
	}

	fclose(fp);

	while (1)
	{
		puts("Calculate total sales by:\n");
		puts("1. Region \n2. Rep \n3. Item \n4. Year \n0. End program");
		scanf("%d", &choice);

		switch (choice){
		default: return 0;
		case 1: { region(line, i); break; }
		case 2: { rep(line, i); break; }
		case 3: { item(line, i); break; }
		case 4: { year(line, i); break; }
		}
	}

}

void region(struct data line[50], int end)
{
	char region[81]; //compare against array
	float total = 0; //sum of totals in array
	int i; //loop counter

	puts("\nEnter the Region to search by: ");
	fflush(stdin);
	gets(region);
	region[0] = toupper(region[0]); //format user entered string
	for (i = 1; i < strlen(region); i++)
	{
		region[i] = tolower(region[i]);
	}

	for (i = 0; i < end; i++)
	{
		if (!strcmp(region, line[i].region)) total += line[i].total;
	}
	if (total != 0) printf("Total sales for region %s: %.2f\n\n", region, total);
	else puts("Region does not exist!\n\n");
}

void rep(struct data line[50], int end)
{
	char rep[81]; //compare against array
	float total = 0; //sum of totals in array
	int i; //loop counter

	puts("\nEnter the Rep to search by: ");
	fflush(stdin);
	gets(rep);
	rep[0] = toupper(rep[0]); //format user entered string
	for (i = 1; i < strlen(rep); i++)
	{
		rep[i] = tolower(rep[i]);
	}

	for (i = 0; i < end; i++)
	{
		if (!strcmp(rep, line[i].rep)) total += line[i].total;
	}
	if (total != 0) printf("Total sales for Rep '%s': %.2f\n\n", rep, total);
	else printf("Rep '%s' does not exist!\n\n", rep);
}

void item(struct data line[50], int end)
{
	char item[81]; //compare against array
	float total = 0; //sum of totals in array
	int i; //loop counter

	puts("\nEnter the item to search by: ");
	fflush(stdin);
	gets(item);
	item[0] = toupper(item[0]); //format user entered string
	for (i = 1; i < strlen(item); i++)
	{
		item[i] = tolower(item[i]);
	}
	if (!strcmp("Pen set", item)) strcpy(item, "Pen Set"); //lazy solution to strcmp

	for (i = 0; i < end; i++)
	{
		if (!strcmp(item, line[i].item)) total += line[i].total;
	}
	if (total != 0) printf("Total sales for item '%s': %.2f\n\n", item, total);
	else printf("Item '%s' does not exist!\n\n", item);
}

void year(struct data line[50], int end)
{
	int year = 0; //compare against array
	float total = 0; //sum of totals in array
	int i; //loop counter

	puts("\nEnter the year to search by: ");
	scanf("%d", &year);
	year = year % 2000; //mod year to double figures

	for (i = 0; i < end; i++)
	{
		if (year == line[i].year) total += line[i].total;
	}
	if (total != 0) printf("Total sales for 20%d: %f\n\n", year, total);
	else puts("Year not found!\n\n");
}

