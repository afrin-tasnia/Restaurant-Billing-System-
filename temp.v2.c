#include<stdio.h>

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

void printMenu(){
    printf("\n\n-----------MENU-----------\n");
    printf("--------------------------\n");
    for(int i=0; i<10;i++){
        printf("%2d.%-10s - BDT %6.2f\n", i+1, items[i],price[i]);
    }
    printf("\n");
}

int main(){

int q;
int choice;
int item;
struct Quantity order;

for(int i=0; i<10;i++){
    order.qty[i]=0;
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

    switch(choice){
        case 1:
            printMenu();
            break;

        case 2: {
            printMenu();
            printf("\nEnter item number to order (1-10): ");
            scanf("%d", &item);

            if (item<1 || item>10){
                printf("Invalid item number!\n");
                break;
            }

            printf("Enter quantity: ");
            scanf("%d", &q);
            order.qty[item-1] +=q;
            printf("Item added successfully!\n");
            break;
            }

        case 3:
        case 4:
            {
            printf("\n\n---------FINAL BILL---------\n");
            printf("----------------------------\n");

            float total=0.0;
            for(int i=0; i<10; i++){
                if(order.qty[i]>0){
                float cost = price[i]*order.qty[i];
                printf("%-10s x %d - BDT %7.2f\n", items[i], order.qty[i],cost);
                total+=cost;
                }
            }

            printf("----------------------------\n");
            printf("Total Bill: BDT %7.2f\n\n",total);

            if(choice==4){
                printf("\nThank you! Please visit us again.\n\n");
            }
            break;
        }

        default :
            printf("Invalid choice! Please select between 1 to 4.");
    }


}while(choice!=4);

return 0;

}

