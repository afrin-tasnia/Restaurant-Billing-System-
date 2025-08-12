#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CUSTOMERS 100

char items[10][20]={
    "Burger", "Pizza", "Pasta", "Fries", "Tacos", "Coffee", "Milk Tea",
    "Ice Cream", "Brownie", "Water"
};

float price[10]={
    250.0, 700.0, 500.0, 150.0, 200.0, 100.0, 50.0, 90.0, 120.0, 20.0
};

struct Quantity {
    int qty[10];
};

struct Quantity orders[MAX_CUSTOMERS];
int customer_count=0;

void printMenu(){
    printf("\n\n-----------MENU-----------\n");
    printf("--------------------------\n");
    for(int i=0; i<10;i++){
        printf("%2d.%-10s - BDT %6.2f\n", i+1, items[i],price[i]);
    }
    printf("\n");
}

void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int safeScanInt(){
    char line[100];
    int num;
    while (1){
        if(fgets(line,sizeof(line),stdin)==NULL){
            printf("Input error! Try again: ");
            continue;
        }
        if(sscanf(line,"%d",&num)==1){
            return num;
        }
        printf("Invalid input! Please enter a number: ");
    }
}

int main(){

int choice;
    char more;

    for(int i=0;i<MAX_CUSTOMERS;i++){
        for(int j=0;j<10;j++){
            orders[i].qty[j]=0;
        }
    }

    printf("\nWelcome to The Krusty Krab!\n");
    printf("===========================");

 do{
    printf("\n---------MAIN MENU---------\n");
    printf("---------------------------\n");
    printf("1.Show Menu\n");
    printf("2.Add Order\n");
    printf("3.View Bill\n");
    printf("4.Checkout and exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    switch(choice){
        case 1:
            printMenu();
            break;

        case 2: {
                if (customer_count >= MAX_CUSTOMERS) {
                    printf("Sorry, maximum customers reached!\n");
                    break;
                }
             int cust_id = customer_count;
                printf("\nNew Customer ID: %d\n", cust_id + 1);

            more='y';
            do{
            printMenu();
            int itemsArray[10];
            int count=0;
            char line[200];

            printf("\nEnter item number to order (1-10): ");
            fgets(line, sizeof(line), stdin);

            char *token = strtok(line, " \t\n");
            while (token != NULL && count < 10) {
            int n = atoi(token);
            if (n < 1 || n > 10) {
                printf("Invalid item number: %d\n", n);
            } else {
                itemsArray[count++] = n;
            }
            token = strtok(NULL, " \t\n");
        }

            for(int i=0;i<count;i++) {
                int quantity;
                printf("Enter quantity for %s: ",items[itemsArray[i]-1]);
                scanf("%d",&quantity);
                if(quantity<=0) {
                    printf("Invalid quantity!\n",items[itemsArray[i]-1]);
                    continue;
                }
                 orders[cust_id].qty[itemsArray[i]-1] +=quantity;
            }
            printf("Item added successfully!\n");
            printf("Do you want to order more? (y/n): ");
            scanf(" %c", &more);
            }while (more == 'y' || more == 'Y');
            customer_count++;
            break;
            }

        case 3:
            {
                if (customer_count == 0) {
                    printf("No customers have ordered yet.\n");
                    break;
                }

                printf("Enter Customer ID to view bill: ");
                int id = safeScanInt();

                if (id < 1 || id > customer_count) {
                    printf("Invalid Customer ID!\n");
                    break;
                }

                int index=id-1;

                printf("\n\n---------FINAL BILL for Customer ID %d ---------\n", id);
                float total=0;
                int any_order=0;
                for (int i=0;i<10;i++){
                    int qty=orders[index].qty[i];
                    if (qty>0) {
                        float cost=qty*price[i];
                        printf("%-10s x %d=BDT %.2f\n",items[i],qty,cost);
                        total+=cost;
                        any_order=1;
                    }
                }
                if (!any_order){
                    printf("No items ordered yet.\n");
                } else {
                    printf("Total Bill=BDT %.2f\n",total);
                }
                break;
            }

        case 4:
            {
                if (customer_count==0) {
                    printf("No customers to checkout.\n");
                    break;
                }
                 printf("Enter Customer ID to checkout: ");
                int id=safeScanInt();

                if (id<1||id>customer_count) {
                    printf("Invalid Customer ID!\n");
                    break;
                }

            int index=id-1;
            printf("\n\n---------FINAL BILL for Customer ID %d---------\n",id);
            printf("----------------------------\n");

            float total=0;
            int any_order = 0;
            for(int i=0; i<10; i++){
                int qty = orders[index].qty[i];
                if (qty > 0){
                float cost = price[i]*qty;
                printf("%-10s x %d - BDT %7.2f\n", items[i],qty,cost);
                total+=cost;
                any_order = 1;
                }
            }
                 if (!any_order) {
                    printf("No items ordered yet.\n");
                   } else {
                    printf("Total Bill = BDT %.2f\n", total);
                 }
                 printf("\nThank you! Please visit us again.\n\n");
                break;
            }

            default:
                printf("Invalid choice!\n");
        }

} while(choice!=4);
   return 0;
}
