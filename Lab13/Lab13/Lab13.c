// Lab13.c
//

#include "stdafx.h"
#include "stdio.h"
#include "string.h"


void main()
{
	FILE *fp;
	char line[200];
	char vehicle[81];
	char type[81];
	char month[12][1];
	char monthName[12][81] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	int i; //loop counter

	fp = fopen("MaintenanceSchedule.txt", "r");

	if (fp == NULL) printf("Error. No such file found!\n");

	else
	{
		fgets(line, 200, fp); //scan first 2 useless lines
		fgets(line, 200, fp);

		while (!feof(fp))
		{
			fscanf(fp, "%s\t%s\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c", vehicle, type, &month[0], &month[1], &month[2], &month[3], &month[4], &month[5], &month[6], &month[7], &month[8], &month[9], &month[10], &month[11]);
			
			if (!strcmp(vehicle, "END")) break; //break loop once end of useful file data is reached

			for (i = 0; i < 12; i++)
			{
				if (month[i][0] == 'S')
				{
					printf("%s with regestration: %s, in %s has Service Due\n", vehicle, type, monthName[i]);
				}
				else if (month[i][0] == 'I')
				{
					printf("%s with regestration: %s, in %s has Inspection Service Due\n", vehicle, type, monthName[i]);
				}
				else if (month[i][0] == 'T')
				{
					printf("%s with regestration: %s, in %s has Two-year Tacho Check Due\n", vehicle, type, monthName[i]);
				}
				else if (month[i][0] == 'C')
				{
					printf("%s with regestration: %s, in %s has Commercial Vehicle Test Due\n", vehicle, type, monthName[i]);
				}
			}
		}
	}

}

