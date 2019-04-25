#include <stdio.h>
#include <stdlib.h>
void clrKyb(void);
void pause(void);
int getInt(void);
int yes(void);  // ms2
int getIntLimited(int lowerLimit, int upperLimit);
void welcome(void);
void GrocInvSys(void);  // ms2
int menu(void);  // ms2

/*int main(void) {
	GrocInvSys();
	return 0;
}*/

// implmement MS2 fucntions here

void GrocInvSys(void) {
	int choice;
   int ctch; //this will use for chacking the yes function values
	int i;
	welcome();
//	choice=menu();
   for (i = 0; i < 25; i++) {
      choice = menu();
      switch (choice) {
      case 1:
         printf("List Items!\n");
         pause();
         break;
      case 2:
         printf("Search Items!\n");
         pause();
         break;
      case 3:
         printf("Checkout Item!\n");
         pause();
         break;
      case 4:
         printf("Stock Item!\n");
         pause();
         break;
      case 5:
         printf("Add/Update Item!\n");
         pause();
         break;
      case 6:
         printf("Delete Item!\n");
         pause();
         break;
      case 7:
         printf("Search by name!\n");
         pause();
         break;
      case 0:
         printf("Exit the program? (Y)es/(N)o : ");
         ctch=yes();
         if (ctch == 1) {
            exit(0);
         }
         else if(ctch==0){
            break;
         }
         break;
      default:
         printf("\n");
         break;

      }
   }
}

int yes(void) {
	char ch;
	scanf("%c", &ch);
	clrKyb();
	while (ch != 'Y' && ch != 'N' && ch != 'y' && ch != 'n') {
		printf("Only (Y)es or (N)o are acceptable: ");
		scanf("%c", &ch);
		clrKyb();

	}
	if (ch == 'Y' || ch == 'y') {
		return 1;
	}
	else if (ch == 'N' || ch == 'n') {
		return 0;
	}
   return 0;

}
int menu(void) {

	int choice;
	printf("1- List all items\n");
	printf("2- Search by SKU\n");
	printf("3- Checkout an item\n");
	printf("4- Stock an item\n");
	printf("5- Add new item or update item\n");
	printf("6- delete item\n");
	printf("7- Search by name\n");
	printf("0- Exit program\n> ");

	choice = getIntLimited(0, 7);
	return choice;
}



// copy MS1 functions here
void clrKyb() {
	char ch;
	do {
		scanf("%c", &ch);
	} while (ch != '\n');
}

void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
}




void pause() {


	printf("Press <ENTER> to continue...");
	clrKyb();

}

int getInt() {
	int val;
	char ch;
	int chk;
	do {
		chk = scanf("%d%c", &val, &ch);
		if (ch != '\n' && chk != 2) {
			clrKyb();
			printf("Invalid integer, please try again: ");
		}
	} while (ch != '\n');

	return val;
	
	//return any integer_value;
}

int getIntLimited(int lowerLimit, int upperLimit) {

	int val;

	char ch;
	
	do {
		scanf("%d%c", &val, &ch);
		if (val < lowerLimit || val > upperLimit) {
			
			printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);

		}
	} while (val < lowerLimit || val > upperLimit);
	
	return val;
}

