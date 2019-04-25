// includes go here
#include <stdio.h>

void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void clrKyb(void);
void pause(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);


/* 1- comment out the main when submitting milestone one
2- Your final milestone one should run perfectly with the following tester program.
To comment out the main() delete the next two characters after the arrow ->

int main(void) {
   int iVal;
   double dVal;
   welcome();

   // testing prnTitle()
   printf("listing header and footer with grand total:\n");
   prnTitle();



   // Testing prnFooter()
   prnFooter(1234.5678);
   printf("listing header and footer without grand total:\n");
   prnTitle();
   prnFooter(-1);


   // Testing Pause() and clrKyb()
   pause();


   // Testing getInt()
   printf("Enter an integer: ");
   iVal = getInt();
   printf("You entered: %d\n", iVal);


   // Testing Get Int Limited
   printf("Enter an integer between 10 an 20: ");
   iVal = getIntLimited(10, 20);
   printf("Your entered %d\n", iVal);


   // Testing Get Double
   printf("Enter a floating point number: ");
   dVal = getDbl();
   printf("You entered: %0.2lf\n", dVal);


   // Tesing Get Double Limited
   printf("Enter a floating point number between 10.00 an 20.00: ");
   dVal = getDblLimited(10.0, 20.0);
   printf("You entered: %0.2lf\n", dVal);



   printf("End of tester program for milestone one!\n");
   return 0;
}
*/
//Funcions Body
void clrKyb() {
   char ch;
   do {
      scanf("%c", &ch);
   } while (ch != '\n');
}

void welcome(void) {
   printf("---=== Grocery Inventory System ===---\n\n");
}

void prnTitle() {
   printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
   printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void prnFooter(double gTotal) {
   printf("--------------------------------------------------------+----------------\n");
   if (gTotal > 0) {
      printf("                                           Grand Total: |%12.2lf\n", gTotal);
   }
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
    if (ch != '\n' && chk !=2 ) {
	 clrKyb();
	 printf("Invalid integer, please try again: ");  
      }
   } while (ch != '\n');
  
   return val;
//get proper int else print error
  
   //return any integer_value;
}

int getIntLimited(int lowerLimit, int upperLimit) {

   int val;
   
   char ch;
   //printf("Enter a floating point number between %d and %d:", lowerLimit, upperLimit);
   do {
      scanf("%d%c", &val, &ch);
      if (val < lowerLimit || val > upperLimit) {
       //  clrKyb();
	 printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
	
      }
   } while (val < lowerLimit || val > upperLimit);
 // clrKyb();
   return val;
}

double getDbl(void) {
   double val;
   int chk;
   char ch;
  
   do {
     chk=scanf("%lf%c", &val, &ch);
      if (ch != '\n' && chk!=2) {
	 clrKyb();
	 printf("Invalid number, please try again: ");
     
      }
   } while (ch != '\n');
 //  clrKyb();
   return val;
}

double getDblLimited(double lowerLimit, double upperLimit) {
   //get double between this limit.
   double val;
 //  int chk;
   char ch;
   //printf("Enter a floating point number between %.2lf and %.2lf:", lowerLimit, upperLimit);
   do {
      scanf("%lf%c", &val, &ch);
      if (val < lowerLimit || val > upperLimit) {
	 printf("Invalid value, %.6lf< value < %.6lf: ", lowerLimit, upperLimit);
    //  clrKyb();
      }
   } while (val < lowerLimit || val > upperLimit);
  // clrKyb();
   return val;
}
