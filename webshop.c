#include <stdio.h>
#include<stdlib.h>
#include"webshop.h"
#include <string.h>


///////////////////////////////////////////////////////////////////////////////////////////


int productAvailableInStore(struct Inventory* space , char*n)
{
    for(int i=0;i<space->size;i++)
    {
        if(strcmp(space->Products[i].Name,n) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int getProductFromStore(struct Inventory* space , char * n)
{
    for(int i=0;i<space->size;i++)
    {
        if(strcmp(space->Products[i].Name,n) == 0)
        {
            return i;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////


int checkPrice(struct Inventory* space , char * n)
{
    for (int i = 0; i < space->size; i++)
    {
        if(strcmp(space->Products[i].Name,n) == 0)
        {
            return space->Products[i].prize;
        }
    }
    
}

int checkDuplicate(struct Inventory* space, char * n , int *index)
{
    for(int i=0;i < space->size;i++)
    {
        if(strcmp(space->Products[i].Name,n) == 0)
        {
            *index = i;
            return 1;
        }
    }

    return 0;
}

void initializeInventory(struct Inventory* space)
{
    int capacity = 100;
    space->Products = malloc(capacity * sizeof(struct Product));
    space->CAPACITY = capacity;
    space->size = 0;
}

void addProducts(struct Inventory* space, struct Product prod)
{
    if(space->size==space->CAPACITY)
    {
        space->CAPACITY *= 2;
        space->Products = realloc(space->Products,space->CAPACITY*sizeof(struct Product));
    }
    else
    {
        int index=0;
        if(checkDuplicate(space,prod.Name,&index)==1)
        {
            space->Products[index].quantity+=prod.quantity;
        }
        else
        {
            space->Products[space->size++] = prod;
        }
    }

}

void printProduct(int p,int q,char*n)
{
    int l = strlen(n);
    for (int i = 0; i < l; i++)
    {
        printf("%c",n[i]);
    }
    printf(" %d %d \n",p,q);
}

void printInventory(struct Inventory* space)
{
    if (space->size == 0) 
    {
        printf("Error - 404 \n");
    }

    for (int i = 0; i < space->size; i++)
    {
        printProduct(space->Products[i].prize,space->Products[i].quantity,space->Products[i].Name);
    }
    
}

void insertItem(struct Inventory* store, struct Inventory* cart)
{
    struct Product pr;
    char prod_name[100];
    int quantity =0;
    int price = 0;
    printf("Enter the name of the product you want to Insert in cart: ");
    scanf("%s",prod_name);

    
    if(productAvailableInStore(store,prod_name) == 1)
    {
        printf("Please enter the quantity: ");
        scanf("%d" , &quantity);

        price = checkPrice(store,prod_name);
        strcpy(pr.Name,prod_name);
        pr.prize = price;
        pr.quantity = quantity;

        addProducts(cart,pr);

        //addProducts(cart,)
    }
    else
    {
        printf("Sorry, this product is not available.\n");
    }




}

void cartPrice(struct Inventory* cart)
{
    int price = 0;
    for (int i = 0; i < cart->size; i++)
    {
        price += (cart->Products[i].prize * cart->Products[i].quantity);

    }
    
    printf("The total price of the cart is: %d HUF\n" , price);
}

void updateFile(struct Inventory* space, FILE *file)
{
    for (int i = 0; i < space->size; i++) {
        writeProductOnFile(space->Products[i].Name, space->Products[i].prize, space->Products[i].quantity, file);
    }

    fclose(file);
}

void Buy(struct Inventory* store , struct Inventory* cart)
{
    FILE * file;
    file = fopen(store->file,"w");

    int successfullPurchase = -1;
    for (int i = 0; i < cart->size; i++)
    {
       int product = getProductFromStore(store,cart->Products[i].Name);
       if(store->Products[product].quantity >= cart->Products[i].quantity)
       {
            store->Products[product].quantity -= cart->Products[i].quantity;
            successfullPurchase = 1;
       }
       else
       {
            int storeQuantity = store->Products[product].quantity;
            int diff = cart->Products[i].quantity - storeQuantity;
            printf("Sorry! %d %s are missing!\n",diff,cart->Products[i].Name);

            store->Products[product].quantity = 0;
       }
    }
    
    cart->size =0;
    cart->Products=NULL;
    initializeInventory(cart);
    updateFile(store,file);
    fclose(file);


    if(successfullPurchase == 1)
    {
        printf("Thank you for Shopping! Take Care.\n");
    }
    
}

void readFile(struct Inventory* space)
{
    
    printf("Please enter the filename: ");
    scanf("%s", filename);
    FILE * file;
    file = fopen(filename,"r");

    strcpy(space->file,filename);
    if(file==NULL)
    {
        printf("operation not successfull");
    }

    while(!feof(file))
    {
        
        struct Product temp_product; 
        char prod_name[100];
        int prod_prize=0;
        int prod_quantity=0;

        fscanf(file,"%s %d %d",&prod_name,&prod_prize,&prod_quantity);

        strcpy(temp_product.Name,prod_name);
        temp_product.prize=prod_prize;
        temp_product.quantity=prod_quantity;
       
        addProducts(space,temp_product);

    }

    fclose(file);

    
}

void writeProductOnFile(char *n, int p, int q, FILE *fl) 
{
    fprintf(fl, "%s %d %d\n", n, p, q);
}

void writeInventoryOnFile(struct Inventory *space) 
{

    printf("Please enter the filename: ");
    scanf("%s",filename);

    FILE *file = fopen(filename, "w");
    
    for (int i = 0; i < space->size; i++) {
        writeProductOnFile(space->Products[i].Name, space->Products[i].prize, space->Products[i].quantity, file);
    }

    fclose(file);
}

void freeMemory(struct Inventory* store , struct Inventory* cart)
{   
    free(store->Products);
    free(cart->Products);

    store->Products=NULL;
    store->size=0;
    store->CAPACITY=0;

    cart->Products= NULL;
    cart->size=0;
    cart->CAPACITY=0;

}

