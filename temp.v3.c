#include <stdio.h>

#define TAX_RATE 0.05

struct MenuItem {
    int id;
    char name[30];
    float price;
};

struct MenuItem menu[] = {
    {1, "Burger", 250.0},
    {2, "Pizza", 700.0},
    {3, "Pasta", 500.0},
    {4, "Fries", 150.0},
    {5, "Tacos", 200.0},
    {6, "Coffee", 100.0},
    {7, "Milk Tea", 50.0},
    {8, "Ice Cream", 90.0},
    {9, "Brownie", 120.0},
    {10, "Water", 20.0},

};

int main() {
    int choice, quantity;
    float subtotal = 0.0, tax, total;
    char more = 'y';

    printf("==== Welcome to The Krusty Krab! ====\n");

    do {
        printf("\n----------- MENU -----------\n");
        for (int i = 0; i < 10; i++) {
            printf("%2d. %-10s - BDT %6.2f\n", menu[i].id, menu[i].name, menu[i].price);
        }

        printf("\nEnter the item number you want to order: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 10) {
            printf("Invalid choice! Please select a valid item.\n");
            continue;
        }

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        float item_total = menu[choice - 1].price * quantity;
        subtotal += item_total;

        printf("Added %d x %s to your bill. Item total: BDT %.2f\n",
               quantity, menu[choice - 1].name, item_total);

        printf("Do you want to order more? (y/n): ");
        scanf(" %c", &more);

    } while (more == 'y' || more == 'Y');

    tax = subtotal * TAX_RATE;
    total = subtotal + tax;

    printf("\n====== Final Bill ======\n");
    printf("Subtotal: BDT %7.2f\n", subtotal);
    printf("Tax (5%%): BDT %7.2f\n", tax);
    printf("Total:    BDT %7.2f\n", total);
    printf("========================\n");
    printf("Thank you for dining with us!\n");

    return 0;
}

