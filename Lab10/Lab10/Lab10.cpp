#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

//AS WELL AS FIXING THE BUGS, ENHANCE THIS PROGRAM SO THAT THE SAME CARDS CANNOT BE DEALT TWICE
void main()
{
	char suits[4] = { 3, 4, 5, 6 };
	char faces[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K' };

	struct cards //database of every card dealt
	{
		int suitsA;
		int facesA;
	};

	struct cards appeared[52];

	int i, j, k, suit, face;
	int check = 0, count = 1; //check for repeat to rand again, counts the number of cards dealt
	int numHands = 0;

		printf("Enter number of Hands: ");
		scanf_s("%d", &numHands);

	for (i = 1; i <= numHands; i++)
	{
		srand(i);
		printf("\nHand # %d \n", i);
		printf("-----------------\n");

		for (j = 0; j < 5; j++)
		{
			while (check == 1)
			{
				suit = rand() % 4;
				face = rand() % 13;

				for (k = 0; k < count - 1; k++)
				{
					if (suit == appeared[k].suitsA && face == appeared[k].facesA) break;
				}

				if (k == count - 1)
				{
					check = 0;
					appeared[k].suitsA = suit;
					appeared[k].facesA = face;
				}

			}
			check = 1;
			count++;
			printf("%c of %c \n", faces[face], suits[suit]);
		}
	}
}
