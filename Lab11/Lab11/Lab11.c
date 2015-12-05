#include "stdafx.h"
#include <stdio.h>
#include <string.h>

void charAddresses(char *string); // 1st function to do
void commaToSpace(char *str); // 2nd function to do
void printWord(char *start); //3rd function to do
char *nextWord(char *start); // 4th function to do


void main()
{
	int i = 0;
	char location[200] = "7825,CREEK VALLEY,SACRAMENTO,95828,CA";
	char *ptr;

	// 1. call function to print out the address and content of each character in the input array
	charAddresses(location);

	// 2. call function to replace all the commas in the input string with spaces
	commaToSpace(location);

	puts("Without commas:");
	puts(location);
	puts("");

	// 3. instead of printing characters (using putchar) until a '\0', printWord prints characters until a space ' '
	puts("First Word");
	printWord(location);

	puts("Second Word");
	printWord(location + 5);

	puts("Third Word");
	printWord(location + 11);
	puts("");

	// starting from the first character in the input string, each call to "nextWord" should return the next word in the string
	// e.g. if the input string is "Hi there everyone" :
	// first call to nextWord should return the address of the letter 't' of "there"
	// second call to nextWord should return the address of the first letter 'e'of "everyone"
	// third call to nextWord should return NULL
	ptr = location;
	while (ptr)
	{
		// instead of printing characters (using putchar) until a '\0', printWord prints characters until a space ' '
		printWord(ptr);
		printf("\n");
		ptr = nextWord(ptr);
	}
}

void charAddresses(char *string)
{
	printf("Address: \tChar:\n");
	printf("-------- \t-----\n");

	while (*string != '\0')
	{
		printf("%p \t%c \n", string, *string);
		string++;
	}
	printf("\n");
}
void commaToSpace(char *str)
{
	while (*str != '\0')
	{
		if (*str == ',') *str = ' ';
		*str++;
	}
}

void printWord(char *start)
{
	while (*start != '\0')
	{
		if (*start == ' ') break;
		putchar(*start);
		*start++;
	}
	printf("\n");
}

char *nextWord(char *start)
{
	while (*(start) != '\0')
	{
		if (*(start) == ' ') return (start + 1);
		*start++;
	}
	return NULL;
}