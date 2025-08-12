#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_CUSTOMERS 100
#define MAX_ITEMS 10

char items[MAX_ITEMS][20] = {
    "Burger", "Pizza", "Pasta", "Fries", "Tacos",
    "Coffee", "Milk Tea", "Ice Cream", "Brownie", "Water"
};

float prices[MAX_ITEMS] = {
    250.0, 700.0, 500.0, 150.0, 200.0,
    100.0, 50.0, 90.0, 120.0, 20.0
};

typedef struct {
    int quantities[MAX_ITEMS];
} CustomerOrder;

CustomerOrder orders[MAX_CUSTOMERS];
int total_customers = 0;

void showMenu() {
    printf("\n-----------MENU-----------\n");
    for(int i = 0; i < MAX_ITEMS; i++) {
        printf("%2d. %-10s - BDT %6.2f\n", i+1, items[i], prices[i]);
    }
}

int getNumberInput(const char* prompt) {
    char input[100];
    int number;

    while(1) {
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin);

        if(scanf(input, "%d", &number) == 1) {
            return number;
        }
        printf("Invalid input! Please enter a number.\n");
    }
}

void addOrder() {
    if(total_customers >= MAX_CUSTOMERS) {
        printf("Sorry, maximum customers reached!\n");
        return;
    }

    int current_customer = total_customers;
    printf("\nNew Customer ID: %d\n", current_customer + 1);

    char more;
    do {
        showMenu();

        printf("\nEnter item numbers separated by spaces (1-10): ");
        char input[100];
        fgets(input, sizeof(input), stdin);

        int item_numbers[MAX_ITEMS];
        int item_count = 0;
        char* token = strtok(input, " \n");

        while(token != NULL && item_count < MAX_ITEMS) {
            int num = atoi(token);
            if(num >= 1 && num <= MAX_ITEMS) {
                item_numbers[item_count++] = num - 1;
            } else {
                printf("Skipping invalid item: %d\n", num);
            }
            token = strtok(NULL, " \n");
        }

        for(int i = 0; i < item_count; i++) {
            char prompt[50];
            sprintf(prompt, "Enter quantity for %s: ", items[item_numbers[i]]);
            int qty = getNumberInput(prompt);

            if(qty > 0) {
                orders[current_customer].quantities[item_numbers[i]] += qty;
                printf("Added %d %s\n", qty, items[item_numbers[i]]);
            } else {
                printf("Quantity must be positive! Item not added.\n");
            }
        }

        printf("Add more items? (y/n): ");
        scanf(" %c", &more);
        getchar();
    } while(more == 'y' || more == 'Y');

    total_customers++;
}

void viewBill() {
    if(total_customers == 0) {
        printf("No customers have ordered yet.\n");
        return;
    }

    int customer_id = getNumberInput("Enter Customer ID: ");
    if(customer_id < 1 || customer_id > total_customers) {
        printf("Invalid Customer ID!\n");
        return;
    }

    int customer_index = customer_id - 1;
    printf("\n---------BILL for Customer ID %d---------\n", customer_id);

    float total = 0;
    int has_items = 0;

    for(int i = 0; i < MAX_ITEMS; i++) {
        int qty = orders[customer_index].quantities[i];
        if(qty > 0) {
            float cost = qty * prices[i];
            printf("%-10s x %d = BDT %7.2f\n", items[i], qty, cost);
            total += cost;
            has_items = 1;
        }
    }

    if(has_items) {
        printf("Total Bill = BDT %.2f\n", total);
    } else {
        printf("No items ordered yet.\n");
    }
}

void checkout() {
    viewBill();
    if(total_customers > 0) {
        printf("\nThank you! Please visit us again.\n\n");
    }
}

int main() {
    memset(orders, 0, sizeof(orders));

    printf("\nWelcome to The Krusty Krab!\n");
    printf("===========================\n");

    while(1) {
        printf("\n---------MAIN MENU---------\n");
        printf("1. Show Menu\n");
        printf("2. Add Order\n");
        printf("3. View Bill\n");
        printf("4. Checkout and Exit\n");

        int choice = getNumberInput("\nEnter your choice: ");

        switch(choice) {
            case 1: showMenu(); break;
            case 2: addOrder(); break;
            case 3: viewBill(); break;
            case 4: checkout(); return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}
