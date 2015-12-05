#include "stdafx.h"
#include <stdio.h>
#include "string.h"


int countCharOccurence(char *string, char c);
int countOccurence(char *string, char c);
int getOption();
int checkSpelling();
int findWord();

long int nwords = 0;
char dictionary[80000][20];

void main(void)
{
	FILE *fptr;
	char fileName[] = "webster.txt";
	int option = 0;

	fptr = fopen(fileName, "r");

	if (fptr == NULL)
	{
		printf("File could not be opened !!\n");
		return;
	}
	else
	{
		while (!feof(fptr))
		{

			fscanf(fptr, "%s\n", dictionary[nwords]);
			nwords++;
		}
		fclose(fptr);
	}

	printf("%ld words read from file \n\n", nwords);

	option = getOption();
	while (option != 0)
	{
		if (option == 1) checkSpelling();
		if (option == 2) findWord();
		if (option == 0) return;
		option = getOption();
	}
}

int getOption()
{
	int option = 0;

	puts("Options: 1=check spelling, 2=find words, 0=quit\n");
	fflush(stdin);
	scanf("%d", &option);
	return option;
}

int checkSpelling()
{
	long int i;
	char temp[20];

	puts("Enter word to check");
	fflush(stdin);
	gets(temp);

	// PUT YOUR CODE HERE
	for (i = 0; i < nwords; i++)
	{
		if (!strcmp(temp, dictionary[i]))
		{
			puts("Spelling Correct!\n");
			return 0;
		}
	}

	puts("Word not found");
	return 0;
}

int findWord()
{
	char bestFit[20];
	int numMatches;
	int highestMatch = 0;
	int i, j, k, len;
	char temp[20];
	int tempCount = 0, wordCount = 0;

	puts("Enter letters you have");

	scanf("%s", temp);
	len = strlen(temp);

	// ENTER YOUR CODE HERE
	for (i = 0; i < nwords; i++)
	{
		numMatches = 0;

		for (j = 0; j < len; j++)
		{
			if (len >= strlen(dictionary[i]))
			{
				tempCount = countCharOccurence(temp, temp[j]);
				if (tempCount < countCharOccurence(dictionary[i], temp[j])) break;

				numMatches += countOccurence(dictionary[i], temp[j]);

				for (k = 0; k < strlen(dictionary[i]); k++)
				{
					if (countCharOccurence(temp, dictionary[i][k]) == 0) {
						numMatches = 0; break;
					}
				}
			}
		}
		if (numMatches > highestMatch)
		{
			highestMatch = numMatches; wordCount = i;
		}
	}
	strcpy(bestFit, dictionary[wordCount]);

	if (highestMatch == 0 && numMatches == 0)
	{
		printf("There is no Best Fit for \"%s\"\n", temp);
	}

	else printf("Best Fit for \"%s\" is \"%s\"  [%d]\n", temp, bestFit, highestMatch);
	return numMatches;
}

int countCharOccurence(char *string, char c)
{
	int i, count = 0, len;
	len = strlen(string);

	for (i = 0; i<len; i++)
	{
		if (string[i] == c) count++;
	}
	return count;
}

int countOccurence(char *string, char c)
{
	int i, len;
	len = strlen(string);

	for (i = 0; i<len; i++)
	{
		if (string[i] == c) return 1;
	}
	return 0;
}