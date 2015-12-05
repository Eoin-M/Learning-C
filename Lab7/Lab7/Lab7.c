// Lab7.c

#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"

float squareMetres(float width, float length);
float squareFeet(float lengthFeet, float widthFeet, float lengthInches, float widthInches);
float feetAndInchesToMetres(float feet, float inches);

float totalfeet, totalinches;

void main()
{
	int op = 0;
	float int1, int2, int3, int4; //integer for multiplication
	char c1, c2, c3, c4, c5; //symbols
	float sum;
	char str[81];

	printf("1. Metric Area Calculator \n2. Imperial Area Calculator\n");
	printf("Choose your option: ");
	scanf_s("%d", &op);

	printf("\nEnter the dimensions of the room: \n");

	if (op == 1)
	{
		printf("Example 30x40\n");
		fflush(stdin);
		gets(str);
		sscanf(str, "%f%c%f", &int1, &c2, &int2);

		sum = squareMetres(int1, int2);

		printf("Size of the room: %.2f square meters\n", sum);
	}

	else if (op == 2)
	{
		printf("Example: 30'8\"x40'3\"\n");
		fflush(stdin);
		gets(str);
		sscanf(str, "%f%c%f%c%c%f%c%f%c", &int1, &c1, &int2, &c2, &c3, &int3, &c4, &int4, &c5);

		squareFeet(int1, int2, int3, int4);

		printf("Size of the room: %.2f'%.2f\"\n", totalfeet, totalinches);
		
		sum = feetAndInchesToMetres(totalfeet, totalinches);

		printf("Size of the room: %.2f\n", sum);
	}

	else printf("That is an invalid entry!\n");
}

float squareMetres(float width, float length)
{
	return width * length;
}

float squareFeet(float int1, float int2, float int3, float int4)
{
	float tempsum = 0;

	int1 = int1 * 12;
	int3 = int3 * 12;
	int2 = int2 + int1;
	int4 = int4 + int3;

	tempsum = int2 * int4;
	
	totalfeet = 0;

	while (tempsum >= 144)
	{
		totalfeet++;
		tempsum = tempsum - 144;
	}
	totalinches = sqrt(tempsum);
}

float feetAndInchesToMetres(float feet, float inches)
{
	feet = feet * 0.3048;
	inches = inches * 0.0254;

	return feet + inches;
}