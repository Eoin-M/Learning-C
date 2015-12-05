#include "stdafx.h"
#include <stdio.h>
#include "string.h"

int readResults(char *inPath);
int writeRange(char *start, char *end, int toFile, char *outPath);
int writeSingle(char *firstName, char *lastName, int toFile, char *outPath);

typedef struct
{
	int ID;
	char firstName[25];
	char lastName[25];
	char english, french, maths, philosophy;
} student;

student students[100];
int ns;

void main(int argc, char *argv[])
{
	char *firstName, *lastName;
	char *start, *end;
	char *inPath, *outPath = NULL;
	int toFile = 0;
	ns = 0;
	int ret;

	/*
	insert your code here to read in the command line arguments
	and call the correct functions
	*/

	inPath = argv[1];
	if (readResults(inPath) == 0) return;

	if (argc == 7)
	{
		toFile = 1;
		outPath = argv[6];
		if (outPath == NULL)
		{
			puts("Output needs a value!\n");
			return;
		}
	}

	if (!strcmp(argv[2], "/s"))
	{
		firstName = argv[3];
		lastName = argv[4];
		writeSingle(firstName, lastName, toFile, outPath);
	}
	else if (!strcmp(argv[2], "/r"))
	{
		start = argv[3];
		end = argv[4];
		writeRange(start, end, toFile, outPath);
	}
}

/* this function reads the data file and populates the array of student data structures */
int readResults(char *inPath)
{
	char temp[200];
	FILE *fptr;
	fptr = fopen(inPath, "r");

	if (fptr == NULL)
	{
		printf("Error in readResults opening data file: %s \n", inPath);
		return 0;
	}

	fgets(temp, 200, fptr);
	fscanf(fptr, "%d %s %s %c %c %c %c", &students[ns].ID, students[ns].firstName, students[ns].lastName, &students[ns].english,
		&students[ns].maths, &students[ns].french, &students[ns].philosophy);

	while (!feof(fptr))
	{
		ns++;
		fscanf(fptr, "%d %s %s %c %c %c %c", &students[ns].ID, students[ns].firstName, students[ns].lastName, &students[ns].english,
			&students[ns].maths, &students[ns].french, &students[ns].philosophy);
	}
	fclose(fptr);
	return 1;

}
/*
this function prints out the results for students in the range start-end
if toFile is false then the results are written to the stdout
if tofile is true then the results are written to the file specified by outPath
*/
int writeRange(char *start, char *end, int toFile, char *outPath)
{
	int i; //loop counter
	int position[2]; //position in array that the names are found
	FILE *ptr = NULL; //pointer to the output file

	if (toFile == 0)
	{
		for (i = 0; i < ns; i++)
		{
			if (!strcmp(start, students[i].lastName)) { position[0] = i; break; }
		}
		for (; i < ns; i++)
		{
			if (!strcmp(end, students[i].lastName)) { position[1] = i; break; }
		}

		if (i < ns)
		{
			printf("ID\tFirstname\tLastname\tEnglish\tMaths\tFrench\tPhilosophy\n");

			for (i = position[0]; i <= position[1]; i++)
			{
				printf("%d\t%-16s%-16s%c\t%c\t%c\t%c\n", students[i].ID, students[i].firstName, students[i].lastName,
					students[i].english, students[i].maths, students[i].french, students[i].philosophy);
			}
		}
		else if (i == ns) printf("No Results Found in Range!\n");
	}
	else
	{
		for (i = 0; i < ns; i++)
		{
			if (!strcmp(start, students[i].lastName)) { position[0] = i; break; }
		}
		for (; i < ns; i++)
		{
			if (!strcmp(end, students[i].lastName)) { position[1] = i; break; }
		}

		if (i < ns)
		{
			ptr = fopen(outPath, "w"); //create file

			printf("ID\tFirstname\tLastname\tEnglish\tMaths\tFrench\tPhilosophy\n");
			fprintf(ptr, "ID\tFirstname\tLastname\tEnglish\tMaths\tFrench\tPhilosophy\n");

			for (i = position[0]; i <= position[1]; i++)
			{
				printf("%d\t%-16s%-16s%c\t%c\t%c\t%c\n", students[i].ID, students[i].firstName, students[i].lastName,
					students[i].english, students[i].maths, students[i].french, students[i].philosophy);
				
				fprintf(ptr, "%d\t%s\t%s\t%c\t%c\t%c\t%c\n", students[i].ID, students[i].firstName, students[i].lastName,
					students[i].english, students[i].maths, students[i].french, students[i].philosophy);
			}
			fclose(ptr);
		}
		else if (i == ns) printf("No Result Found in Range!\n");
	}
	return 1;
}

/*
this function prints out the results for a students with
the given firstName and lastName
if toFile is false then the results are written to the stdout
if tofile is true then the results are written to the file specified by outPath
*/
int writeSingle(char *firstName, char *lastName, int toFile, char *outPath)
{
	int i; //loop counter
	FILE *ptr = NULL; //pointer to the output file

	if (toFile == 0)
	{
		for (i = 0; i < ns; i++)
		{
			if (!strcmp(firstName, students[i].firstName) && !strcmp(lastName, students[i].lastName)) break;
		}

		if (i < ns)
		{
			printf("ID\tFirstname\tLastname\tEnglish\tMaths\tFrench\tPhilosophy\n");
			printf("%d\t%s\t\t%s\t\t%c\t%c\t%c\t%c\n", students[i].ID, students[i].firstName, students[i].lastName,
				students[i].english, students[i].maths, students[i].french, students[i].philosophy);
		}
		else if (i == ns) printf("No Result Found!\n");
	}
	else
	{
		{
			for (i = 0; i < ns; i++)
			{
				if (!strcmp(firstName, students[i].firstName) && !strcmp(lastName, students[i].lastName)) break;
			}
			if (i < ns)
			{
				printf("ID\tFirstname\tLastname\tEnglish\tMaths\tFrench\tPhilosophy\n");
				printf("%d\t%s\t%s\t%c\t%c\t%c\t%c\n\n", students[i].ID, students[i].firstName, students[i].lastName,
					students[i].english, students[i].maths, students[i].french, students[i].philosophy);
				
				printf("Information of the student has been written to file: %s\n", outPath);

				ptr = fopen(outPath, "w"); //create file

				fprintf(ptr, "ID\tFirstname\tLastname\tEnglish\tMaths\tFrench\tPhilosophy\n");
				fprintf(ptr, "%d\t%s\t%s\t%c\t%c\t%c\t%c\n", students[i].ID, students[i].firstName, students[i].lastName,
					students[i].english, students[i].maths, students[i].french, students[i].philosophy);

				fclose(ptr);
			}
			else if (i == ns) printf("No Result Found!\n");
		}
	}
	return 1;
}