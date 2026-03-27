#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

struct Node{
        int data;
        struct Node* next;
};

struct Node* hashTable[SIZE];

int hashFunc(int key){
        return key%SIZE;
}

void insert(int key){
        int index=hashFunc(key);

        struct Node* newNode=(struct Node*)malloc(sizeof ( struct Node));

        newNode->data=key;
        newNode->next=NULL;

         if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
        } else {
            newNode->next = hashTable[index];
            hashTable[index] = newNode;
        }
      printf("Inserted %d at index %d\n", key, index);

      
}
