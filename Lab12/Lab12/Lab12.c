// Lab12.cpp :


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int year;
	char county[3];
	int number;
} registration;

typedef struct
{
	char make[40];
	char model[40];
	int year;
	double price;
	registration reg;
	int sold;  // 0 = for sale; 1 = sold
} car;

// this function is already written
int printMenu();

// complete the code in these functions
int addCar(car stock[], int num, car newCar);
void displayCarsForSale(car stock[], int num);
void displayAllCars(car stock[], int num);
void displayCar(car car1);
void sellCar(car stock[], int num, registration reg);


void main()
{
	car stock[200];
	int numCars = 0;
	int option;
	car newCar;
	registration reg1;

	printf("Welcome to the Universal Car Sales \n");
	printf("------------------------------------\n");

	option = printMenu();
	while (option != 0)
	{
		switch (option)
		{
		case 1:
			displayCarsForSale(stock, numCars);
			break;

		case 2:
			printf("Enter make: ");
			scanf("%s", &newCar.make);
			fflush(stdin);
			printf("Enter model: ");
			scanf("%s", &newCar.model);
			fflush(stdin);
			printf("Enter year: ");
			scanf_s("%d", &newCar.year);
			fflush(stdin);
			printf("Enter price: ");
			scanf_s("%lf", &newCar.price);
			fflush(stdin);
			printf("Enter reg (e.g. 04 CE 1234): ");
			scanf("%d %s %d", &newCar.reg.year, &newCar.reg.county, &newCar.reg.number);
			printf("\n");
			newCar.sold = 0;

			numCars = addCar(stock, numCars, newCar);
			// get the user to enter the new car data & reg
			// use newCar to hold the data
			// call addCar (stock, numCars, newCar)
			// addCar returns the new number of cars (numCars+1)
			break;

		case 3:
			printf("Enter the reg of the car that you wuld like to buy: ");
			scanf("%d %s %d", &reg1.year, &reg1.county, &reg1.number);
			printf("\n");

			sellCar(stock, numCars, reg1);
			// get the user to enter the reg that is sold
			// call sellCar(stock, numCars, reg1);
			// it sets  'sold' to 1 for this car
			break;

		case 4:
			displayAllCars(stock, numCars);
			// call displayAllCars if there are any in stock
			break;

		default:
			puts("Illegal Option!\n");
		}
		option = printMenu();
	}

}

int printMenu()
{
	int option = 0;
	printf("1 - Display Stock for Sale\n");
	printf("2 - Add Car \n");
	printf("3 - Sell Car \n");
	printf("4 - Display All Stock \n");
	printf("0 - Exit\n");
	printf("------------------------------------\n");
	printf("Choose your option:\n");
	scanf_s("%d", &option);
	printf("------------------------------------\n");
	return option;

}

int addCar(car stock[], int num, car newCar)
{
	*(stock + num) = newCar;
	return num + 1;
}


void displayCar(car car1)
{
	printf("Make: \t%s\n", car1.make);
	printf("Model: \t%s\n", car1.model);
	printf("Year: \t%d\n", car1.year);
	printf("Price: \t%.2lf\n", car1.price);
	printf("Reg: \t%02d %s %d\n", car1.reg.year, car1.reg.county, car1.reg.number);
	if (car1.sold == 0) printf("For Sale\n\n");
	else if (car1.sold == 1) printf("Sold\n\n");
	// print out the details for a car, including the reg
}


void displayCarsForSale(car stock[], int num)
{
	int i;
	int temp = 0; //check if any cars are for sale

	for (i = 0; i < num; i++)
	{
		if (stock[i].sold == 0) { displayCar(stock[i]); temp = 1; }
	}

	if (temp == 0) printf("There are no cars for sale!\n\n");

	// call displayCar for cars with 'sold' = 0
	printf("------------------------------------\n");

}


void displayAllCars(car stock[], int num)
{
	int i;

	for (i = 0; i < num; i++)
	{
		displayCar(stock[i]);
	}
	if (i == 0) printf("There is no stock!\n\n");
	// call displayCar for all cars
}


void sellCar(car stock[], int num, registration reg)
{
	int i;

	for (i = 0; i < num; i++)
	{
		if (reg.year == stock[i].reg.year && !strcmp(reg.county, stock[i].reg.county) && reg.number == stock[i].reg.number)
		{
			printf("Car is now sold!\n\n");
			stock[i].sold = 1;
			break;
		}
	}

	if (i == num) printf("Car not found!\n\n");
	// set sold=0 for the car with this reg
	// print "Car Not Found\n" if it is not in stock
}