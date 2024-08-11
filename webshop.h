#ifndef WEBSHOP_H
#define WEBSHOP_H

#include <stdio.h>

char filename[100];



struct Product
{
    char Name[50];
    int prize;
    int quantity;

};

struct Inventory
{
    char file[100];
    struct Product* Products;
    int size;
    int CAPACITY; 

};


int productAvailableInStore(struct Inventory* space , char*n);
int getProductFromStore(struct Inventory* space , char * n);
int checkPrice(struct Inventory* space , char * n);
int checkDuplicate(struct Inventory* space, char * n , int *index);
void initializeInventory(struct Inventory* space);
void addProducts(struct Inventory* space, struct Product prod);
void printProduct(int p,int q,char*n);
void printInventory(struct Inventory* space);
void insertItem(struct Inventory* store, struct Inventory* cart);
void cartPrice(struct Inventory* cart);
void Buy(struct Inventory* store , struct Inventory* cart);
void readFile(struct Inventory* space);
void writeProductOnFile(char *n, int p, int q, FILE *fl);
void writeInventoryOnFile(struct Inventory *space);
void freeMemory(struct Inventory* store , struct Inventory* cart);
void updateFile(struct Inventory* store, FILE *fl);




#endif