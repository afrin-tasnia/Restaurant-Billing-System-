#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char items[10][20] = {
    "Burger", "Pizza", "Pasta", "Fries", "Tacos", "Coffee", "Milk Tea",
    "Ice Cream", "Brownie", "Water"
};

float price[10] = {
    250.0, 700.0, 500.0, 150.0, 200.0, 100.0, 50.0, 90.0, 120.0, 20.0
};

struct Quantity {
    int qty[10];
};

void printMenu() {
    printf("\n\n-----------MENU-----------\n");
    for (int i = 0; i < 10; i++) {
        printf("%2d. %-10s - BDT %6.2f\n", i + 1, items[i], price[i]);
    }
    printf("\n");
}

void printBill(struct Quantity order) {
    printf("\n\n---------FINAL BILL---------\n");
    float total = 0.0;
    for (int i = 0; i < 10; i++) {
        if (order.qty[i] > 0) {
            float cost = price[i] * order.qty[i];
            printf("%-10s x %d - BDT %7.2f\n", items[i], order.qty[i], cost);
            total += cost;
        }
    }
    printf("----------------------------\n");
    printf("Total Bill: BDT %7.2f\n\n", total);
}

int main() {
    int choice;
    char more;
    struct Quantity order;

    for (int i = 0; i < 10; i++) {
        order.qty[i] = 0;
    }

    printf("\nWelcome to The Krusty Krab!\n");
    printf("===========================\n");

    do {
        printf("\n---------MAIN MENU---------\n");
        printf("1. Show Menu\n");
        printf("2. Add Order\n");
        printf("3. View Bill\n");
        printf("4. Checkout and Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            printMenu();
            break;

        case 2:
            more = 'y';
            do {
                printMenu();
                int itemsArray[10];
                int count = 0;
                char line[200];

                printf("\nEnter item numbers to order (space separated, 1-10): ");
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

                for (int i = 0; i < count; i++) {
                    int quantity;
                    printf("Enter quantity for %s: ", items[itemsArray[i] - 1]);
                    scanf("%d", &quantity);
                    getchar();
                    if (quantity <= 0) {
                        printf("Invalid quantity!\n");
                        continue;
                    }
                    order.qty[itemsArray[i] - 1] += quantity;
                }

                printf("Items added successfully!\n");
                printf("Do you want to order more? (y/n): ");
                scanf(" %c", &more);
                getchar();
            } while (more == 'y' || more == 'Y');
            break;

        case 3:
            printBill(order);
            break;

        case 4:
            printBill(order);
            printf("\nThank you! Please visit us again.\n\n");
            break;

        default:
            printf("Invalid choice! Please select between 1 to 4.\n");
        }

    } while (choice != 4);

    return 0;
}

