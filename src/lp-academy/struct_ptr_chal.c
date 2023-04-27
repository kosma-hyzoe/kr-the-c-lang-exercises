#include <stdio.h>
#include <stdlib.h>

struct item {
        char *itemName;
        int quantity;
        float price;
        float amount;
};

void readItem(struct item *item)
{
        printf("Item name:\n");
	scanf("%s", item->itemName);

	printf("Quantity: \n");
	scanf("%i", &item->quantity);
	printf("Price:\n");
	scanf("%f", &item->price);
        item->amount = item->quantity * item->price;
        return;
}

void printItem(struct item *ip)
{
        printf("N: %s\tQ: %i\tP: %f\n", ip->itemName, ip->quantity, ip->price);
        return;
}

int main()
{
        struct item i;
        struct item *pi = &i;

        pi->itemName=malloc(30 * sizeof(char));
        readItem(pi);
        printItem(pi);
        free(pi->itemName);
        return 0;
}
