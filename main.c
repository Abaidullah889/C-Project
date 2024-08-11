#include <stdio.h>
#include<stdlib.h>
#include"webshop.h"
#include <string.h>



int main() 
{
    


    int exit =1;
    int choice = -1;


//////////////////////////////////////////////////////////////////////////////////////////////

    struct Inventory store;
    struct Inventory cart;      
    initializeInventory(&cart);
    initializeInventory(&store);

//////////////////////////////////////////////////////////////////////////////////////////


    printf("Select (1) if you want to open the store: \n");
    printf("Select (2) if you want to get the data from the store on the file: \n");
    printf("Select (3) if you want to insert an item into the cart: \n");
    printf("Select (4) if you want to see the price of the cart: \n");
    printf("Select (5) if you want to buy the cart \n");
    printf("Select (6) if you want to see items in the store\n");
    printf("Select (7) if you want to see items in the cart\n\n");

    printf("Choose -1 for exit \n");

    while(exit == 1)
    {
        

        printf("Your Choice ");
        scanf("%d",&choice);

        if(choice == 1)
        {
            readFile(&store);
        }
        if(choice == 2)
        {
            writeInventoryOnFile(&store);
        }
        if(choice == 3)
        {
            insertItem(&store,&cart);
        }
        if(choice == 4)
        {
            cartPrice(&cart);
        }
        if(choice == 5)
        {
            Buy(&store,&cart);
        }
        if(choice == 6)
        {
            printInventory(&store);
        }
        if(choice == 7)
        {
            printInventory(&cart);
        }
        if(choice == -1)
        {
            freeMemory(&store,&cart);
            return 0;
        }

    }



    return 0;
}

