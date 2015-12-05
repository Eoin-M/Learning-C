struct account
{
	int num;
	double balance;
	double interest;
	double tax;
};

void printAccounts(struct account accounts[], int num);
double calcInterest(double balance);
double calcTax(double interest);
void printAccount(struct account anAccount);
void setupAccounts(struct account accounts[], int num);
void updateAccounts(struct account accounts[], int num);

#define interestRate 0.025
#define taxRate 0.25