#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

struct contact
{
	char firstName[50];
	char lastName[50];
	char companyName[50];
	char address[50];
	char city[50];
	char county[50];
	char state[50];
	char zip[50];
	char phone1[50];
	char phone2[50];
	char email[50];
	char web[50];
};

int numContacts = 0;
struct contact *contacts;
int readFile(char *fileName);
int findContact(char *string);
int findInfo(char *string, int choice);
void printContact(int pos); //changed to pass int position into function rather than struct which is global anyway.
int countLines(char *fileName);
char* formatName(char *string);

void main()
{
	char string[20];
	char fileName[] = "us-500b.txt";
	int pos = 0;
	int option;

	numContacts = countLines(fileName);

	contacts = (struct contact *)malloc(numContacts*sizeof(struct contact));


	if (!readFile(fileName))
	{
		printf("File could not be opened !!\n");
		return;
	}
	puts("Options:\n1-search by Name\n2-search by Company\n3-search by City\n4-search by County\n5-search by State\n6-search by Zip\n");
	fflush(stdin);
	scanf("%d", &option);

	puts("Enter all \(or part\) of what you are looking for: ");
	fflush(stdin);
	gets(string);

	switch (option)
	{
	case 1:
		pos = findContact(string);
		break;
	case 2:
		pos = findInfo(string, option);
		break;
	case 3:
		pos = findInfo(string, option);
		break;
	case 4:
		pos = findInfo(string, option);
		break;
	case 5:
		pos = findInfo(string, option);
		break;
	case 6:
		pos = findInfo(string, option);
		break;
	default:
		break;
	}
	if (pos == 0) puts("Not Found!\n\n");

	free(contacts); //free allocated memory
}

int findContact(char *string)
{
	int i = 0, j;
	char temp[200];

	for (j = 0; j < numContacts; j++)
	{
		strcpy(temp, contacts[j].firstName);
		strcpy(temp, formatName(temp)); //changes each letter to lowercase for case insensitive searching
		strcpy(string, formatName(string));

		if (strstr(temp, string) != NULL)
		{
			printContact(j); //prints every contact where strstr() is not NULL
			i = 1; //shows contact found
		}
		
		strcpy(temp, contacts[j].lastName);
		strcpy(temp, formatName(temp));

		if (strstr(temp, string) != NULL)
		{
			printContact(j);
			i = 1;
		}
	}

	return i;
}

int findInfo(char *string, int choice)
{
	int i = 0, j;
	char temp[200];

	for (j = 0; j < numContacts; j++)
	{
		if (choice == 2) strcpy(temp, contacts[j].companyName); //changes each letter to lowercase for case insensitive searching
		else if (choice == 3) strcpy(temp, contacts[j].city);
		else if (choice == 4) strcpy(temp, contacts[j].county);
		else if (choice == 5) strcpy(temp, contacts[j].state);
		else if (choice == 6) strcpy(temp, contacts[j].zip);
		strcpy(temp, formatName(temp));
		strcpy(string, formatName(string));

		if (strstr(temp, string) != NULL)
		{
			printContact(j);
			i = 1;
		}
	}
	return i;
}

char* formatName(char *string) //formats a name to lowercase for comparing
{
	int i;

	for (i = 0; i < strlen(string); i++)
	{
		string[i] = tolower(string[i]);
	}
	return string;
}

void printContact(int pos)
{
	printf("FIRST NAME: %s\n", contacts[pos].firstName);
	printf("LAST NAME: %s\n", contacts[pos].lastName);
	printf("COMPANY NAME: %s\n", contacts[pos].companyName);
	printf("ADDRESS: %s\n", contacts[pos].address);
	printf("CITY: %s\n", contacts[pos].city);
	printf("COUNTY: %s\n", contacts[pos].county);
	printf("STATE: %s\n", contacts[pos].state);
	printf("ZIP: %s\n", contacts[pos].zip);
	printf("PHONE #1: %s\n", contacts[pos].phone1);
	printf("PHONE #2: %s\n", contacts[pos].phone2);
	printf("EMAIL: %s\n", contacts[pos].email);
	printf("WEB: %s\n", contacts[pos].web);
}

int countLines(char *fileName)
{
	char line[200];
	FILE *fptr = fopen(fileName, "r");
	int nLines = 0;

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
		return 0;
	}

	// use fgets to skip first line
	fgets(line, 200, fptr);
	fgets(line, 200, fptr);
	while (!feof(fptr))
	{
		nLines++;
		fgets(line, 200, fptr);
	}

	fclose(fptr);

	return nLines;
}

int readFile(char *fileName)
{
	char line[200];
	FILE *fptr = fopen(fileName, "r");
	char *token;
	char delim[6] = ",";
	int n = 0, i = 0;

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
		return 0;
	}

	// use fgets to skip first line
	fgets(line, 200, fptr);

	//first data line
	fgets(line, 200, fptr);
	while (!feof(fptr))
	{
		if ((token = strtok(line, delim)) != NULL) strcpy((contacts + n)->firstName, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->lastName, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->companyName, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->address, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->city, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->county, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->state, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->zip, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->phone1, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->phone2, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->email, token);
		if ((token = strtok(NULL, delim)) != NULL) strcpy((contacts + n)->web, token);
		//printContact((contacts+n));
		n++;
		//next data line
		fgets(line, 200, fptr);

	}

	fclose(fptr);

	return 1;
}
