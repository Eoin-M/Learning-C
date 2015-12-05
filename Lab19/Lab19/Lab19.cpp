/* Fig. 11.16: fig11_16.c
This program reads a random access file sequentially, updates data
already written to the file, creates new data to be placed in the
file, and deletes data previously in the file. */
#include <stdio.h>

/* bookData structure definition */
struct bookData {
	char title[20];
	char author[20];
	int year;
	int ISBN;
	float wholesale_price;
	float retail_price;
};

struct bookData book;

/* prototypes */
void createFile();
int enterChoice(void);
void textFile(FILE *ptr);
void updateRecord(FILE *ptr);
void newRecord(FILE *ptr);
void deleteRecord(FILE *ptr);

int main()
{
	FILE *ptr; /* book.dat file pointer */
	int choice;  /* user's choice */

	createFile();

	ptr = fopen("book.dat", "rb+");

	/* enable user to specify action */
	while ((choice = enterChoice()) != 5) {

		switch (choice) {

			/* create text file from record file */
		case 1:
			textFile(ptr);
			break;

			/* update record */
		case 2:
			updateRecord(ptr);
			break;

			/* create record */
		case 3:
			newRecord(ptr);
			break;

			/* delete existing record */
		case 4:
			deleteRecord(ptr);
			break;

			/* display message if user does not select valid choice */
		default:
			printf("Incorrect choice\n");
			break;
		}
	}
	fclose(ptr);

	return 0; /* indicates successful termination */

}

void createFile()
{
	int i; // counter

	FILE *ptr; /* book.dat file pointer */
	book = { "", "", 0, 0, 0, 0 }; //blank struct

	/* fopen opens the file; exits if file cannot be opened */
	if ((ptr = fopen("book.dat", "rb")) == NULL)
	{
		ptr = fopen("book.dat", "wb"); //creates file if it doesn't already exits

		/* output 100 blank records to file */
		for (i = 0; i < 100; i++)
		{
			fwrite(&book, sizeof(struct bookData), 1, ptr);
		}
		fclose(ptr);
	}

	return;

}

/* create formatted text file for printing */
void textFile(FILE *ptr)
{
	FILE *writePtr; /* ISBNs.txt file pointer */

	if ((writePtr = fopen("ISBNs.txt", "w")) == NULL) {
		printf("File could not be opened.\n");
	}
	else {
		rewind(ptr); /* sets pointer to beginning of file */
		fprintf(writePtr, "%-20s%-10s%-10s%-10s%-16s%-10s\n", "Title", "Author", "Year", "ISBN", "Wholesale", "Retail");

		/* copy all records from random-access file into text file */
		while (fread(&book, sizeof(struct bookData), 1, ptr) != NULL) {

			/* write single record to text file */
			if (book.ISBN != 0) {
				fprintf(writePtr, "%-20s%-10s%-10d%-10d%-16.2f%-10.2f\n", book.title, book.author, book.year, book.ISBN, book.wholesale_price, book.retail_price);
			}

		}

		fclose(writePtr);
	}

}

/* update balance in record */
void updateRecord(FILE *ptr)
{
	int ISBN;        /* ISBN number */
	double transaction; /* transaction amount */

	/* obtain number of ISBN to update */
	printf("Enter ISBN to update ( 1 - 100 ): ");
	scanf("%d", &ISBN);

	/* move file pointer to correct record in file */
	fseek(ptr, (ISBN - 1) * sizeof(struct bookData), SEEK_SET);

	/* read record from file */
	fread(&book, sizeof(struct bookData), 1, ptr);

	/* display error if ISBN does not exist */
	if (book.ISBN == 0) {
		printf("Acount #%d has no information.\n", ISBN);
	}
	else { /* update record */
		printf("%-20s%-16s%-10d%10.2f%10.2f\n\n", book.title, book.author, book.year, book.wholesale_price, book.retail_price);

		printf("Enter new retail price: ");
		scanf("%f", &book.retail_price);

		printf("%-20s%-16s%-10d%10.2f%10.2f\n\n", book.title, book.author, book.year, book.wholesale_price, book.retail_price);

		/* move file pointer to correct record in file */
		fseek(ptr, (ISBN - 1) * sizeof(struct bookData), SEEK_SET);

		/* write updated record over old record in file */
		fwrite(&book, sizeof(struct bookData), 1, ptr);
	}

}

/* delete an existing record */
void deleteRecord(FILE *ptr)
{

	struct bookData book; /* stores record read from file */

	int ISBNNum; /* ISBN number */

	/* obtain number of ISBN to delete */
	printf("Enter ISBN number to delete ( 1 - 100 ): ");
	scanf("%d", &ISBNNum);

	/* move file pointer to correct record in file */
	fseek(ptr, (ISBNNum - 1) * sizeof(struct bookData), SEEK_SET);

	/* read record from file */
	fread(&book, sizeof(struct bookData), 1, ptr);

	/* display error if record does not exist */
	if (book.ISBN == 0) {
		printf("ISBN %d does not exist.\n", ISBNNum);
	}
	else { /* delete record */

		/* move file pointer to correct record in file */
		fseek(ptr, (ISBNNum - 1) * sizeof(struct bookData),
			SEEK_SET);

		/* replace existing record with blank record */
		book = { "", "", 0, 0, 0, 0 };

		fwrite(&book, sizeof(struct bookData), 1, ptr);
	}

}

/* create and insert record */
void newRecord(FILE *ptr)
{
	int ISBNNum; /* ISBN number */

	/* obtain number of ISBN to create */
	printf("Enter new ISBN number ( 1 - 100 ): ");
	scanf("%d", &ISBNNum);

	/* move file pointer to correct record in file */
	fseek(ptr, (ISBNNum - 1) * sizeof(struct bookData), SEEK_SET);

	/* read record from file */
	fread(&book, sizeof(struct bookData), 1, ptr);

	/* display error if ISBN already exists */
	if (book.ISBN != 0) {
		printf("ISBN #%d already contains information.\n",
			book.ISBN);
	}
	else { /* create record */

		/* user enters last name, first name and balance */
		printf("Enter title: ");
		fflush(stdin);
		gets(book.title);
		printf("Enter author: ");
		fflush(stdin);
		gets(book.author);
		printf("Enter year: ");
		fflush(stdin);
		scanf("%d", &book.year);
		printf("Enter wholesale price: ");
		fflush(stdin);
		scanf("%f", &book.wholesale_price);
		printf("Enter retail price: ");
		fflush(stdin);
		scanf("%f", &book.retail_price);

		book.ISBN = ISBNNum;

		/* move file pointer to correct record in file */
		fseek(ptr, (book.ISBN - 1) * sizeof(struct bookData), SEEK_SET);

		/* insert record in file */
		fwrite(&book, sizeof(struct bookData), 1, ptr);
	}

}

/* enable user to input menu choice */
int enterChoice(void)
{
	int menuChoice; /* variable to store user's choice */

	/* display available options */
	printf("\nEnter your choice\n"
		"1 - store a formatted text file of acounts called\n"
		"    \"ISBNs.txt\" for printing\n"
		"2 - update an ISBN\n"
		"3 - add a new ISBN\n"
		"4 - delete an ISBN\n"
		"5 - end program\n? ");

	scanf("%d", &menuChoice); /* receive choice from user */

	return menuChoice;

}