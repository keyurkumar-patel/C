#include <stdio.h>


struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};

void dspItem(struct Item item, int linear);
void listItems(struct Item item[], int noOfItems);
int locateItem(const struct Item item[], int noOfRecs, int sku, int* index);
int menu(void);
void GrocInvSys(void);
void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);


#define LINEAR  1
#define FORM  0
#define STOCK  1
#define CHECKOUT  0
#define MAX_QTY 989
#define SKU_MAX 999
#define SKU_MIN 100
#define MAX_ITEM_NO 500
#define DATAFILE "ipc_ms5_short.txt"


void searchTest();
void updateTest();
void addTest();
void addOrUpdateTest();
void adjustQtyTest();

struct Item GI[21] = {
	{ 4.4, 275, 0, 10, 2, "Royal Gala Apples" },
	{ 5.99, 386, 0, 20, 4, "Honeydew Melon" },
	{ 3.99, 240, 0, 30, 5, "Blueberries" },
	{ 10.56, 916, 0, 20, 3, "Seedless Grapes" },
	{ 2.5, 385, 0, 5, 2, "Pomegranate" },
	{ 0.44, 495, 0, 100, 30, "Banana" },
	{ 0.5, 316, 0, 123, 10, "Kiwifruit" },
	{ 4.49, 355, 1, 20, 5, "Chicken Alfredo" },
	{ 5.49, 846, 1, 3, 5, "Veal Parmigiana" },
	{ 5.29, 359, 1, 40, 5, "Beffsteak Pie" },
	{ 4.79, 127, 1, 30, 3, "Curry Checken" },
	{ 16.99, 238, 1, 10, 2, "Tide Detergent" },
	{ 10.49, 324, 1, 40, 5, "Tide Liq. Pods" },
	{ 10.99, 491, 1, 50, 5, "Tide Powder Det." },
	{ 3.69, 538, 1, 1, 5, "Lays Chips S&V" },
	{ 3.29, 649, 1, 15, 5, "Joe Org Chips" },
	{ 1.79, 731, 1, 100, 10, "Allen's Apple Juice" },
	{ 6.69, 984, 1, 30, 3, "Coke 12 Pack" },
	{ 7.29, 350, 1, 50, 5, "Nestea 12 Pack" },
	{ 6.49, 835, 1, 20, 2, "7up 12 pack" }
};
int GNoOfRecs = 20;
const double TAX = 0.13;

void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void clrKyb(void);
void pause(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);
char yes(void);
double totalAfterTax(struct Item item);
int isLowQty(struct Item item);

struct Item itemEntry(int sku)
{
	struct Item a;



	printf("        SKU: %d", sku);
	a.sku = sku;
	printf("\n       Name: ");
	scanf(" %20[^\n]", a.name);
	clrKyb();
	printf("      Price: ");
	a.price = getDblLimited(0.01, 1000.00);
	printf("   Quantity: ");
	a.quantity = getIntLimited(1, MAX_QTY);
	printf("Minimum Qty: ");
	a.minQuantity = getIntLimited(0, 100);
	printf("   Is Taxed: ");
	a.isTaxed = yes();

	return a;
};




int main(void)
{
	welcome();
	GrocInvSys();
	return 0;
}




/*End of milestone 5 prototypes
*********************************************************************/
void saveItem(struct Item item, FILE* dataFile)
{
	//printf("%d,%d, %d, %.2lf,%d,%20s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);

	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);


}

int loadItem(struct Item* item, FILE* dataFile)
{

	int counter = 0;

	if (fscanf(dataFile, "%d,%d,%d,%lf,%d,%[^\n]%*c\n", &(*item).sku, &(*item).quantity, &(*item).minQuantity, &(*item).price, &(*item).isTaxed, (*item).name) == 6) {
		counter = 1;
	}

	return counter;

}

int saveItems(struct Item* item, char fileName[], int NoOfRecs)
{
	FILE *fp = fopen(fileName, "a+");
	int i;
	if (fp != NULL) {
		for (i = 0; i < NoOfRecs; i++) {
			saveItem(item[i], fp);
		}

	}
	else {
		printf("Failed to open file\n");
	}
	fclose(fp);
	return 1;
}

int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr)
{
	int counter = 0;
	FILE *fp = fopen(fileName, "r");
	while (loadItem(&item[counter], fp)) {
		counter++;
	}

	fclose(fp);
	*NoOfRecsPtr = counter;
	return 1;
}

void search(const struct Item item[], int NoOfRecs)
{
	int input, index, answer;


	printf("Please enter the SKU: ");
	do
	{
		scanf("%d", &input);
	} while (input > SKU_MAX || input < SKU_MIN);

	answer = locateItem(item, NoOfRecs, input, &index);

	if (answer == 1)
	{
		printf("Item not found!\n");
	}
	else if (answer == 0)
	{
		dspItem(item[index], 0);
	}
	clrKyb();
	return;
}

void updateItem(struct Item* itemptr)
{
	int exit;
	struct Item a;


	a = itemEntry(itemptr[0].sku);

	printf("Overwrite old data? (Y)es/(N)o: ");
	exit = yes();

	if (exit == 1)
	{
		*itemptr = a;
		return;
	}
	if (exit == 0)
	{
		printf("--== Aborted! ==--\n");
		return;
	}

}

void addItem(struct Item item[], int *NoOfRecs, int sku)
{
	if (*NoOfRecs < MAX_ITEM_NO)
	{
		int exit, size = *NoOfRecs;
		struct Item a;

		a = itemEntry(sku);

		printf("Add Item? (Y)es/(N)o: ");
		exit = yes();

		if (exit == 1)
		{
			printf("--== Added! ==--\n");
			item[*NoOfRecs] = a;

			size++;
			*NoOfRecs = size;
			return;
		}
		if (exit == 0)
		{
			printf("--== Aborted! ==--\n");
			return;
		}

	}
	else
	{
		printf("Can not add new item; Storage Full!\n");
	}
}

void addOrUpdateItem(struct Item item[], int* NoOfRecs)
{
	struct Item a;

	int input, answer, index, exit, size = *NoOfRecs;

	printf("Please enter the SKU: ");
	scanf("%d", &input);

	answer = locateItem(item, *NoOfRecs, input, &index);
	if (answer == 1)
	{
		addItem(item, &size, input);
		*NoOfRecs = size;
	}
	else if (answer == 0)
	{
		dspItem(item[index], 0);
		printf("Item already exists, Update? (Y)es/(N)o: ");
		clrKyb();
		exit = yes();


		if (exit == 0)
		{
			printf("--== Aborted! ==--\n");

		}
		else if (exit == 1)
		{
			printf("Enter new data:\n");
			a = itemEntry(input);
			printf("Overwrite old data? (Y)es/(N)o: ");

			exit = yes();

			if (exit == 1)
			{
				printf("--== Updated! ==--\n");
				printf("Updated Item: \n");
				item[index] = a;
				dspItem(a, 0);
			}
		}
	}
}

void adjustQty(struct Item item[], int NoOfRecs, int stock)
{
	int input, answer, index;

	printf("Please enter the SKU: ");
	scanf("%d", &input);

	answer = locateItem(item, NoOfRecs, input, &index);

	if (answer == 1)
	{
		printf("SKU not found in storage!\n");
	}
	else if (answer == 0)
	{
		dspItem(item[index], 0);

		if (stock == 0)
		{
			printf("Please enter the quantity to checkout; Maximum of %d or 0 to abort: ", item[index].quantity);
		}
		else if (stock == 1)
		{
			printf("Please enter the quantity to stock; Maximum of %d or 0 to abort: ", MAX_QTY);
		}
		scanf("%d", &answer);
		if (answer == 0)
		{
			printf("--== Aborted! ==--\n");
		}
		else if (answer > 0)
		{
			if (stock == 0)
			{
				printf("--== Checked out! ==--\n");
				item[index].quantity -= answer;
			}
			else if (stock == 1)
			{
				printf("--== Stocked! ==--\n");
				item[index].quantity += answer;
			}

			if (isLowQty(item[index]) == 1)
			{
				printf("Quantity is low, please reorder ASAP!!!\n");
			}

		}
		else if (answer < 0)
		{
			printf(
				"--== Aborted! ==--\n"
				"you cannot withdraw negative ammounts\n"
			);
		}
	}
	clrKyb();
}
void welcome(void)
{
	printf("---=== Grocery Inventory System ===---\n\n");

	return;
}
void prnTitle(void)
{
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
	return;
}
void prnFooter(double gTotal)
{
	printf("--------------------------------------------------------+----------------\n");

	if (gTotal > 0)
	{
		printf("                                           Grand Total: |%12.2lf\n", gTotal);
	}
	return;
}
void clrKyb(void)
{
	char check;
	do
	{
		scanf("%c", &check);
	} while (check != '\n');
	return;
}
void pause(void)
{
	printf("Press <ENTER> to continue...");
	clrKyb();
	return;
}
int getInt(void)
{
	int valid;
	char check;
	do
	{
		scanf("%d%c", &valid, &check);

		if (check != '\n')
		{
			clrKyb();
			printf("Invalid integer, please try again: ");
			valid = 0;
		}
	} while (check != '\n');
	return (valid);
}
double getDbl(void)
{
	double valid;
	char check;
	do
	{
		scanf("%lf%c", &valid, &check);

		if (check != '\n')
		{
			clrKyb();
			printf("Invalid number, please try again: ");
			valid = 0;
		}
	} while (check != '\n');
	return (valid);
}
int getIntLimited(int lowerLimit, int upperLimit)
{
	while (1)
	{
		int value = getInt();
		if (value <= upperLimit && value >= lowerLimit)
		{
			return (value);
		}
		else if (value > upperLimit || value < lowerLimit)
		{
			printf("Invalid value, %d <= value <= %d: ", lowerLimit, upperLimit);

		}
	}
}
double getDblLimited(double lowerLimit, double upperLimit)
{
	while (1)
	{
		double value = getDbl();
		if (value < upperLimit && value > lowerLimit)
		{
			return (value);
		}
		else if (value > upperLimit || value < lowerLimit)
		{
			printf("Invalid value, %lf <= value <= %lf: ", lowerLimit, upperLimit);

		}
	}
}

char yes(void)
{
	char check;
	do
	{
		scanf("%c", &check);
		clrKyb();
		if (check != 'y' && check != 'n' && check != 'Y' && check != 'N')
		{
			printf("Only (Y)es or (N)o are acceptable: ");
		}

	} while (check != 'y' && check != 'n' && check != 'Y' && check != 'N');

	if (check == 'y' || check == 'Y')
	{
		return 1;
	}
	else if (check == 'n' || check == 'N')
	{
		return 0;
	}
	return 1;
}

double totalAfterTax(struct Item item)
{
	double total;

	if (item.isTaxed != 0)
	{
		total = (item.price * item.quantity * (1 + TAX));
	}
	if (item.isTaxed == 0)
	{
		total = (item.price * item.quantity);
	}
	return total;
}

int isLowQty(struct Item item)
{
	if (item.quantity <= item.minQuantity)
	{
		return 1;
	}
	else if (item.quantity > item.minQuantity)
	{
		return 0;
	}
	return 1;
}

void dspItem(struct Item item, int linear)
{

	if (linear == 1)
	{
		printf("   |%d|", item.sku);
		printf("%-20s", item.name);
		printf("|%8.2lf", item.price);
		if (item.isTaxed == 1)
		{
			printf("|  Yes");
		}
		else if (item.isTaxed == 0)
		{
			printf("|   No");
		}
		printf("|%4d ", item.quantity);
		printf("|%4d ", item.minQuantity);
		printf("|%12.2lf|", totalAfterTax(item));
		if (isLowQty(item) == 1)
		{
			printf("***");
		}
		printf("\n");
	}
	else if (linear == 0)
	{
		printf("        SKU: %d\n", item.sku);
		printf("       Name: ");
		printf("%s", item.name);
		printf("\n      Price: %0.2lf\n", item.price);

		printf("   Quantity: %d\n", item.quantity);
		printf("Minimum Qty: %d\n", item.minQuantity);
		if (item.isTaxed == 1)
		{
			printf("   Is Taxed: Yes\n");
		}
		else if (item.isTaxed == 0)
		{
			printf("   Is Taxed: No\n");
		}
		if (isLowQty(item) == 1)
		{
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}
	}
	return;
}

void listItems(struct Item item[], int noOfItems)
{
	int count;
	double gTotal = 0;

	prnTitle();
	for (count = 0; count < noOfItems; count++)
	{
		printf("%d", (count + 1));
		dspItem(item[count], LINEAR);
		gTotal += totalAfterTax(item[count]);
	}
	prnFooter(gTotal);
	return;
}

int locateItem(const struct Item item[], int noOfRecs, int sku, int* index)
{
	int count, x = 1;


	for (count = 0; count < noOfRecs && x == 1; count++)
	{
		if (item[count].sku == sku)
		{
			x = 0;
			*index = count;
		}
	}
	return x;
}

int menu(void)
{
	int choice;
	printf(
		"1- List all items\n"
		"2- Search by SKU\n"
		"3- Checkout an item\n"
		"4- Stock an item\n"
		"5- Add new item or update item\n"
		"0- Exit program\n"
		"> "
	);
	choice = getIntLimited(0, 7);
	return choice;
}

void GrocInvSys(void)
{
	struct Item foo[MAX_ITEM_NO];
	int hold;
	int choice;
	char exit;
	int i = 0;
	int j = 0;
	j = loadItems(foo, DATAFILE, &hold);
	if (j == 0)
	{
		printf("Could not read from %s.\n", DATAFILE);
	}

	else
	{
		while (1)
		{
			choice = menu();
			switch (choice)
			{
			case 1:
				listItems(foo, hold);
				pause();
				break;
			case 2:
				search(foo, hold);
				pause();
				break;
			case 3:
				adjustQty(foo, hold, CHECKOUT);
				i = saveItems(foo, DATAFILE, hold);
				if (i != 1)
				{
					printf("could not update data file %s\n", DATAFILE);
				}
				pause();
				break;
			case 4:
				adjustQty(foo, hold, STOCK);
				i = saveItems(foo, DATAFILE, hold);
				if (i != 1)
				{
					printf("could not update data file %s\n", DATAFILE);
				}
				pause();
				break;
			case 5:
				addOrUpdateItem(foo, &hold);
				saveItems(foo, DATAFILE, hold);
				if (i != 1)
				{
					printf("could not update data file %s\n", DATAFILE);
				}
				pause();

				break;
				//case 6:
				printf("Delete Item!\n");
				pause();
				break;
				//case 7:
				printf("Search by name!\n");
				pause();
				break;
			case 0:
				printf("Exit the program? (Y)es/(N)o): ");
				exit = yes();
				if (exit == 1)
				{
					return;
				}
				break;
			default:

				printf("Invalid input, try again: \n");
				break;
			}
		}
	}
}
void searchTest() {
	printf("================Search Test:\n");
	printf("Enter 731: \n");
	search(GI, GNoOfRecs);
	printf("Enter 222: \n");
	search(GI, GNoOfRecs);
}
void updateTest() {
	struct Item I = { 11.11, 111, 1, 11, 1, "Ones!" };
	printf("================Update Test:\n");
	printf("Enter the follwoing: \n");
	printf(
		"         SKU: 111\n"
		"        Name: Grape\n"
		"      Price : 22.22\n"
		"   Quantity : 22\n"
		"Minimum Qty : 2\n"
		"   Is Taxed : y\n"
		"Overwrite old data? (Y)es/(N)o: n\n");
	printf("Enter new data:\n");
	updateItem(&I);
	printf("Unchanged Item Data:\n");
	dspItem(I, FORM);
	printf("Enter the follwoing: \n");
	printf(
		"         SKU: 111\n"
		"        Name: Grape\n"
		"      Price : 22.22\n"
		"   Quantity : 22\n"
		"Minimum Qty : 2\n"
		"   Is Taxed : y\n"
		"Overwrite old data? (Y)es/(N)o: y\n");
	printf("Enter new data:\n");
	updateItem(&I);
	printf("--== Updated! ==--\n");
	printf("Updated Item: \n");
	dspItem(I, FORM);
}
void addTest() {
	printf("================Add Test:\n");
	printf("Total items in Storage: %d, Max no: %d\n", GNoOfRecs, MAX_ITEM_NO);
	printf("Enter the follwoing: \n");
	printf(
		"         SKU: 222\n"
		"        Name: Grape\n"
		"      Price : 22.22\n"
		"   Quantity : 22\n"
		"Minimum Qty : 2\n"
		"   Is Taxed : y\n"
		"Add Item? (Y)es/(N)o: n\n");

	addItem(GI, &GNoOfRecs, 222);
	printf("Garbage here! Nothing is added, No of items in storage: %d\n", GNoOfRecs);
	dspItem(GI[GNoOfRecs], FORM);
	printf("Enter the follwoing: \n");
	printf(
		"         SKU: 222\n"
		"        Name: Grape\n"
		"      Price : 22.22\n"
		"   Quantity : 22\n"
		"Minimum Qty : 2\n"
		"   Is Taxed : y\n"
		"Add Item? (Y)es/(N)o: y\n");
	addItem(GI, &GNoOfRecs, 222);
	printf("New item is added, No of itemsinstorage: %d\n", GNoOfRecs);
	dspItem(GI[GNoOfRecs - 1], FORM);
	printf("Adding 333: \n");
	addItem(GI, &GNoOfRecs, 333);
}
void addOrUpdateTest() {
	GNoOfRecs = MAX_ITEM_NO;
	printf("================AddOrUpdate Test:\n");
	printf("Enter 731 and then \'n\':\n");
	addOrUpdateItem(GI, &GNoOfRecs);
	printf("Enter 731, \'y\' and then:\n"
		"       Name: Apple\n"
		"      Price: 1.80\n"
		"   Quantity: 101\n"
		"Minimum Qty: 11\n"
		"   Is Taxed: n\n"
		"Overwrite old data? (Y)es/(N)o: y\n");

	addOrUpdateItem(GI, &GNoOfRecs);

	printf("Enter 444: \n");
	addOrUpdateItem(GI, &GNoOfRecs);
}

void adjustQtyTest() {
	printf("================AdjustQty Test:\n");
	printf("Invalid SKU Test; Enter 444:\n");
	adjustQty(GI, GNoOfRecs, STOCK);
	printf("Aborting Entry test; Enter 731 and then 0:\n");
	adjustQty(GI, GNoOfRecs, CHECKOUT);
	printf("Checking out with low quantity warning; Enter 731 and then 90:\n");
	adjustQty(GI, GNoOfRecs, CHECKOUT);
	printf("Stocking; Enter 731 and then 50:\n");
	adjustQty(GI, GNoOfRecs, STOCK);
	dspItem(GI[16], FORM);
}

