#include <stdbool.h>
#include <stdlib.h>
#include "intset.h"


struct intsetType {
    int data;
    int *next;
};

intSet createSet(){
    intSet new_set = malloc(sizeof(struct intsetType)); 
    return new_set;
}
void destroySet(intSet set){
    free(set);
}
void clear(intSet set){
    while (set->next != NULL) {
        intSet temp = set->next;
        set->next = temp->next;
        free(temp);
    }
}
int card(const intSet set){

}
bool equals(const intSet set1, const intSet set2){
    
}
bool contains(const intSet set, int value){
    intSet current = set;
    while (current->next != NULL) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    if (current->data == value) {
            return true;
        }
    return false;
}
int largest(const intSet set){
    intSet current = set;
    int largest = set->data;
    while (current->next != NULL) {
        current = current->next;
        if (current->data > largest) {
            largest = current->data;
        }
    }
    return largest;
}
int smallest(const intSet set){
    intSet current = set;
    int smallest = set->data;
    while (current->next != NULL) {
        current = current->next;
        if (current->data < smallest) {
            smallest = current->data;
        }
    }
    return smallest;
}
void add(intSet set, int value){
    while (set->next != NULL) {
        set = set->next;
    }

    intSet new_element = malloc(sizeof(struct intsetType));

    new_element->data = value;
    new_element->next = NULL;

    set->next = new_element;
}
void remove_(intSet set, int value){
    while (set->next != NULL) {
        if (set->data == value) {
            intSet temp = set->next;
            set->next = temp->next;
            free(temp);
            return;
        }
        set = set->next;
    }
}
intSet union_(const intSet set1, const intSet set2){

}
intSet intersection(const intSet set1, const intSet set2){

}
intSet diff(const intSet set1, const intSet set2){

}
bool isEmpty(const intSet set){
    if (set == NULL) {
        return true;
    }
    return false;
}
int *toArray(const intSet set, int *size){
    // Implementation for converting set to array
}
char *toString(const intSet set){
    // Implementation for converting set to string
}
