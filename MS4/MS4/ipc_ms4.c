#include <stdio.h>
#include<stdlib.h>
	

/***************************************************************

Tester Function prototypes and information, DO NOT MODIFY */
	

void searchTest();
void updateTest();
void addTest();
void addOrUpdateTest();
void adjustQtyTest();
	
struct Item {
   double price;
   int sku;
   int isTaxed;
   int quantity;
   int minQuantity;
   char name[21];
};
struct Item GI[21] = {
   { 4.4,275,0,10,2,"Royal Gala Apples" },
   { 5.99,386,0,20,4,"Honeydew Melon" },
   { 3.99,240,0,30,5,"Blueberries" },
   { 10.56,916,0,20,3,"Seedless Grapes" },
   { 2.5,385,0,5,2,"Pomegranate" },
   { 0.44,495,0,100,30,"Banana" },
   { 0.5,316,0,123,10,"Kiwifruit" },
   { 4.49,355,1,20,5,"Chicken Alfredo" },
   { 5.49,846,1,3,5,"Veal Parmigiana" },
   { 5.29,359,1,40,5,"Beffsteak Pie" },
   { 4.79,127,1,30,3,"Curry Checken" },
   { 16.99,238,1,10,2,"Tide Detergent" },
   { 10.49,324,1,40,5,"Tide Liq. Pods" },
   { 10.99,491,1,50,5,"Tide Powder Det." },
   { 3.69,538,1,1,5,"Lays Chips S&V" },
   { 3.29,649,1,15,5,"Joe Org Chips" },
   { 1.79,731,1,100,10,"Allen's Apple Juice" },
   { 6.69,984,1,30,3,"Coke 12 Pack" },
   { 7.29,350,1,50,5,"Nestea 12 Pack" },
   { 6.49,835,1,20,2,"7up 12 pack" }
};
int GNoOfRecs = 20;
/**************************************************************/
	

/*************************************************************
	

Student Milestone 3 definitions and prototypes go here:
	

(Do not copy struct Item since it is already implimented above*/
#define FORM 0
void clrKyb();
int getInt(void);
int getIntLimited(int lowerLimit, int upperLimit);
int locateItem(const struct Item item[], int NoOfRecs, int sku,int* index);
struct Item itemEntry(int sku);
int yes(void) ;
void dspItem(const struct Item item,int linear);
	

/*End of Student Milestone 3 definitions and prototypes
	

*************************************************************/
 
	

/*************************************************************
	

Milestone 4 defintions and prototypes:*/
// write the define statements here:
#define MAX_ITEM_NO 21
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
#define STOCK 1
#define CHECKOUT 0

// function prototypes in order of implementation:

void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);
/*End of Milestone 4 defintions and prototypes:
	

***************************************************************/
/*************************************************************
Main tester */

//int main() {
	

//   searchTest();
	

//   updateTest();
	

//   addTest();
	

//   addOrUpdateTest();
	

//   adjustQtyTest();
	

//   return 0;
	

//}

/*End of main tester
	
*****************************************************************/


/***************************************************************
Milestone 4 functions to be implemented */

void search(const struct Item item[], int NoOfRecs) {
       int userIn;
       int index;
       printf("Please enter the SKU: ");
       userIn = getIntLimited(SKU_MIN,SKU_MAX);
       if(locateItem(item,NoOfRecs,userIn, &index) == 0)
              printf("Item not found!\n");
       else{
              char* YNans[4];
              if(item[index].isTaxed == 1){
                     *YNans = "Yes";
              }else{
                     *YNans = "No";
              }
              printf("        SKU: %d\n"
                         "       Name: %s\n"
                         "      Price: %.2lf\n"
                            "   Quantity: %d\n"
                         "Minimum Qty: %d\n"
                            "   Is Taxed: %s\n", item[index].sku, item[index].name, item[index].price, item[index].quantity, item[index].minQuantity, *YNans);
       }
}
void updateItem(struct Item* itemptr) {
       struct Item item;
       printf("Enter new data:\n");
       item = itemEntry(itemptr->sku);
       printf("Overwrite old data? (Y)es/(N)o: ");
       if(yes() == 1){
              *itemptr = item;
              printf("--== Updated! ==--\n");
       }else{
              printf("--== Aborted! ==--\n");
       }
}
void addItem(struct Item item[], int *NoOfRecs, int sku) {
       struct Item newItem;
       int spec = *NoOfRecs;
       if(spec == MAX_ITEM_NO){
              printf("Can not add new item; Storage Full!\n");
       }else{
               newItem = itemEntry(sku);
               printf("Add Item? (Y)es/(N)o: ");
               if(yes() == 1){
                      item[spec] = newItem;
                      spec++;
                      *NoOfRecs = spec;
                      printf("--== Added! ==--\n");
               }else{
                      printf("--== Aborted! ==--\n");
               }
       }
}
void addOrUpdateItem(struct Item item[], int* NoOfRecs) {
       int userIn;
       int index;
       printf("Please enter the SKU: ");
       userIn = getIntLimited(SKU_MIN,SKU_MAX);
       if(locateItem(item, *NoOfRecs, userIn, &index)==1){
              dspItem(item[index],FORM);
              printf("Item already exists, Update? (Y)es/(N)o: ");
              if(yes() == 1){
                    updateItem(&item[index]);
              }else{
                     printf("--== Aborted! ==--\n");
              }
       }else{
              addItem(item, NoOfRecs, userIn);
       }
}
void adjustQty(struct Item item[], int NoOfRecs, int stock) {
       int userQut;
       int sku;
       int flag = 0;
       int index;
       int i;
       printf("Please enter the SKU: ");
	       sku = getInt();
	       for(i = 0; i < NoOfRecs ; i++){
	                     if(sku == item[i].sku){
	                           index = i;
	                           flag = 1;
	                     }
	       }
	       if(flag == 0){
	              printf("SKU not found in storage!\n");
	       }else{
	              dspItem(item[index],FORM);
	             if(stock == 1){
	                     printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ","to stock", MAX_QTY-item[index].quantity);
	                     userQut = getIntLimited(0, MAX_QTY-item[index].quantity);
	                     if(userQut == 0){
	                           printf("--== Aborted! ==--\n");
	                     }else{
	                           item[index].quantity += userQut;
	                           printf("--== Stocked! ==--\n");
	                     }
	              }
	              else if(stock == 0){
	                     printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", "to checkout", item[index].quantity);
	                     userQut = getIntLimited(0, item[index].quantity);
	                     if(userQut == 0){
	                           printf("--== Aborted! ==--\n");
	                     }else{
	                           item[index].quantity -= userQut;
	                           printf("--== Checked out! ==--\n");
	                     }
	              }
	              if(item[index].quantity <= item[index].minQuantity){
	                     printf("Quantity is low, please reorder ASAP!!!\n");
	              }
	       }
	}
	/*End of Milestone 4 functions
	******************************************************************/
	
/*****************************************************************
	Milestone 3 function implementations:
	
   Please copy your milestone 3 functions here: */
void clrKyb(){
       while(getchar() != '\n');
}
int getInt(void) {

      int value;
       char NL = 'x';
       while (NL != '\n') {
              scanf("%d%c", &value, &NL);
              if (NL != '\n') {
                     clrKyb();
                     printf("Invalid integer, please try again: ");
              }
       }
       return value;
}
int getIntLimited(int lowerLimit, int upperLimit){
       int Value;
       do{
              Value = getInt();
              if(lowerLimit > Value || upperLimit < Value ){
                     printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
                     }
       }while(lowerLimit > Value || upperLimit < Value );
       return Value;
}
double getDbl(void){
   double value;
   char NL = 'x';
   while(NL != '\n'){
      scanf("%lf%c", &value, &NL);
      if(NL != '\n'){
         clrKyb();
         printf("Invalid number, please try again: ");
      }
   }
   return value;
}
struct Item itemEntry(int sku) {
       struct Item itemEntry;
       itemEntry.sku = sku;
       printf("        SKU: %d\n", sku);
       printf("       Name: ");
       scanf("%20[^\n]", itemEntry.name);
       clrKyb();
	    printf("      Price: ");
	    itemEntry.price = getDbl();
	       printf("   Quantity: ");
	       itemEntry.quantity = getInt();;
	       printf("Minimum Qty: ");
	       itemEntry.minQuantity = getInt();
	       printf("   Is Taxed: ");
	       itemEntry.isTaxed = yes();
	       return itemEntry;
	}
	
int yes(void) {  // ms2
	       char CH;
	       int RET = 0;
	       do {
	         scanf("%c", &CH);// to discard all whitespace.
	              clrKyb();
	              if (CH != 'Y' && CH != 'y' && CH != 'N' && CH != 'n') {
	                     printf("Only (Y)es or (N)o are acceptable: ");
	              }
	       }while (CH != 'Y' && CH != 'y' && CH != 'N' && CH != 'n');
	       if (CH == 'Y' || CH == 'y') {
	              RET = 1;
	       }
	       return RET;
	}
	void dspItem(struct Item item,int linear){
	       char* YNans[4];
	       if(item.isTaxed == 1){
	              *YNans = "Yes";
	       }else{
	              *YNans = "No";
	              }
	       if(linear == 1){
	              printf("|%3d|%-20s|%8.2lf|  %3s| %3d | %3d |", item.sku, item.name, item.price, *YNans,item.quantity, item.minQuantity);
	              if(item.quantity < item.minQuantity){
	                     printf("***\n");
	              }else{
	                     printf("\n");
	              }
	       }else{
	              printf("        SKU: %d\n"
	                           "       Name: %s\n"
	                           "      Price: %.2lf\n"
	                           "   Quantity: %d\n"
	                           "Minimum Qty: %d\n"
	                          "   Is Taxed: %s\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, *YNans);
	              if(item.quantity <= item.minQuantity){
	                     printf("WARNING: Quantity low, please order ASAP!!!\n");
	              }
	       }
	}
	int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index){
	       int i;
	       int flag = 0;
	       for(i = 0; i < NoOfRecs ; i++){
	              if(sku == item[i].sku){
	                     *index = i;
	                     flag = 1;
	              }
	       }
	       return flag;
	}
	/*End of Milestone 3 functions.
	

******************************************************************/
	/***************************************************************
	Tester Functions DO NOT MODIFY */
	void searchTest() {
	   printf("================Search Test:\n");
	   printf("Enter 731: \n");
	   search(GI, GNoOfRecs);
	   printf("Enter 222: \n");
	   search(GI, GNoOfRecs);
	}
	void updateTest() {
	   struct Item I = { 11.11,111,1,11,1,"Ones!" };
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
	   updateItem(&I);
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
	   addItem(GI, &GNoOfRecs, 222); //n
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
	
   addItem(GI, &GNoOfRecs, 222); //y
	   printf("New item is added, No of itemsinstorage: %d\n", GNoOfRecs);
	   dspItem(GI[GNoOfRecs - 1], FORM);
	   printf("Adding 333: \n");
	   addItem(GI, &GNoOfRecs, 333);
	}
	void addOrUpdateTest() {
	   GNoOfRecs = MAX_ITEM_NO;
	   printf("================AddOrUpdate Test:\n");
	   printf("Enter 731 and then \'n\':\n");
	   addOrUpdateItem(GI, &GNoOfRecs); // n
	   printf("Enter 731, \'y\' and then:\n"
	      "       Name: Apple\n"
	      "      Price: 1.80\n"
	      "   Quantity: 101\n"
	      "Minimum Qty: 11\n"
	      "   Is Taxed: n\n"
	      "Overwrite old data? (Y)es/(N)o: y\n");
	   addOrUpdateItem(GI, &GNoOfRecs); // yes new data Yes
	   printf("Updated Item: \n");
	   dspItem(GI[16], FORM);
	   printf("Enter 444: \n");
	   addOrUpdateItem(GI, &GNoOfRecs); //n
	
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
	

 
	/* End test functions
*********************************************************************/
	

 