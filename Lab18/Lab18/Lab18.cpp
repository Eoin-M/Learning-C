// Lab18.cpp : 

#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

void enterReading(FILE *ptr);
void dayWeather(FILE *ptr); //finds weather od day by date
void listAll(FILE *ptr);
void printData(struct data weather); //other functions pass data here to print data

struct data{
	int day;
	int month;
	int year;
	float minTemp;
	float maxTemp;
	float rainfall;
	char descreiption[200];
};

struct data weather;

void main()
{
	FILE *ptr; //pointer to weather.bin
	int choice;

	ptr = fopen("weather.bin", "ab+"); //open file once in apend read mode

	while (1) //infinte loop until default is triggered
	{
		puts("1. Enter reading\n2. Find a day's weather\n3. List all\n0. Quit");
		scanf("%d", &choice);

		switch (choice){
		default: { fclose(ptr);  return; } //close file and end program
		case 1: { enterReading(ptr); break; }
		case 2: { dayWeather(ptr); break; }
		case 3: { listAll(ptr); break; }
		}
	}
}

void enterReading(FILE *ptr)
{
	fseek(ptr, 0, SEEK_SET); //move cursor to end of file in case not there already

	puts("Please enter the following information:\n");
	puts("Date (dd/mm/yyyy): "); //date seperated by '/'
	fflush(stdin);
	scanf("%d/%d/%d", &weather.day, &weather.month, &weather.year);
	puts("Minimum temperature: ");
	fflush(stdin);
	scanf("%f", &weather.minTemp);
	puts("Maximum temperature: ");
	fflush(stdin);
	scanf("%f", &weather.maxTemp);
	puts("Rainfall: ");
	fflush(stdin);
	scanf("%f", &weather.rainfall);
	puts("Enter a description:");
	fflush(stdin);
	gets(weather.descreiption);
	puts("\n");

	fwrite(&weather, sizeof(data), 1, ptr);
}

void dayWeather(FILE *ptr)
{
	int tempDay, tempMonth, tempYear;

	fseek(ptr, 0, SEEK_SET); //move cursor to beginning of file
	puts("Enter date (dd/mm/yyyy): ");
	scanf("%d/%d/%d", &tempDay, &tempMonth, &tempYear);

	while (fread(&weather, sizeof(data), 1, ptr) == 1)
	{
		if (tempDay == weather.day && tempMonth == weather.month && tempYear == weather.year)
		{
			printData(weather); //simple function to print all data in struct
			return;
		}
	}
	puts("No date found!\n");
}

void listAll(FILE *ptr)
{
	int i = 0; //counter

	fseek(ptr, 0, SEEK_SET); //move cursor to beginning of file

	while (fread(&weather, sizeof(data), 1, ptr) == 1)
	{
		printData(weather); //simple function to print all data in struct
		i++;
	}
	if (i == 0)	puts("No dates found in file!\n");
	else printf("%d day(s) found.\n\n", i);
}

void printData(struct data weather)
{
	printf("\nDate: %02d/%02d/%d\n", weather.day, weather.month, weather.year);
	printf("Minimum temperature: %.2f\n", weather.minTemp);
	printf("Maximum temperature: %.2f\n", weather.maxTemp);
	printf("Rainfall: %.2f\n", weather.rainfall);
	printf("Description:\n%s\n", weather.descreiption);
	puts("--------------------------------------\n");
}