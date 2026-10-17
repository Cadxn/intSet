#include <stdbool.h>
#include <stdlib.h>
#include "intset.h"


struct intsetType {
    int *data;
    int capacity;
    int size;
};

intSet createSet(){
    intSet new_set = malloc(sizeof(struct intsetType)); 
    new_set->data = NULL;
    new_set->capacity = 0;
    new_set->size = 0;
    return new_set;
}
void destroySet(intSet set){
    free(set->data);
    free(set);
}
void clear(intSet set){
    set->size = 0;
}
int card(const intSet set){
    return set->size;
}
bool equals(const intSet set1, const intSet set2){
    intSet current1 = set1;
    intSet current2 = set2;
    if (current1->size != current2->size) {
        return false;
    }
    for(int i = 0; i < current1->size; i++) {
        if (current1->data[i] != current2->data[i]) {
            return false;
        }
    }

    return true;
}
bool contains(const intSet set, int value){
    intSet current = set;
    for (int i = 0; i < current->size; i++) {
        if (current->data[i] == value) {
            return true;
        }
    }
    return false;
}
int largest(const intSet set){
    intSet current = set;
    int largest = set->data[0];
    for (int i = 1; i < current->size; i++) {
        if (current->data[i] > largest) {
            largest = current->data[i];
        }
    }
    return largest;
}
int smallest(const intSet set){
    intSet current = set;
    int smallest = set->data[0];
    for (int i = 1; i < current->size; i++) {
        if (current->data[i] < smallest) {
            smallest = current->data[i];
        }
    }
    return smallest;
}
void add(intSet set, int value){

    for(int i = 0; i < set->size; i++){
            if(set->data[i] == value){
                return;
            } 
        }

    if (set->size == set->capacity) {
        int *new_data = malloc(sizeof(int) * set->capacity + 1);
        
            for (int i = 0; i < set->size; i++) {
                new_data[i] = set->data[i];
            }
            
            free(set->data);
            set->data = new_data;
            set->capacity = set->capacity + 1;
    }

    
    set->data[set->size] = value;
    set->size++;

}
void remove_(intSet set, int value){
    for(int i = 0; i < card(set); i++){
        if (set->data[i] == value) {
            for(int j = i; j < set->size - 1; j++){
                set->data[j] = set->data[j + 1];
            }
            set->size--;
            return;
        }
    }
}
intSet union_(const intSet set1, const intSet set2){
    intSet new_set = createSet();
    intSet current = set1;
    new_set->capacity = card(set1) + card(set2);
    new_set->data = malloc(sizeof(int) * new_set->capacity);

    for (int i = 0; i < card(current); i++) {
        new_set->data[i] = current->data[i];
        new_set->size++;
    }
    current = set2;
    for (int i = 0; i < card(set2); i++) {
        for(int j = 0; j < new_set->size; j++){
            if(new_set->data[j] == current->data[i]){
                break;
            } else{
                new_set->data[new_set->size] = current->data[i];
                new_set->size++;
            }
        }
    }
    return new_set;
}
intSet intersection(const intSet set1, const intSet set2){
    intSet new_set = createSet();
    intSet current = set1;
    new_set->capacity = card(set1) + card(set2);
    new_set->data = malloc(sizeof(int) * new_set->capacity);

    for (int i = 0; i < card(current); i++) {
        for(int j = 0; j < card(set2); j++){
            if(current->data[i] == set2->data[j]){
                new_set->data[new_set->size] = current->data[i];
                new_set->size++;
            }
        }
    }
    return new_set;
}
intSet diff(const intSet set1, const intSet set2){
    intSet new_set = createSet();
    intSet current = set1;
    new_set->capacity = card(set1) + card(set2);
    new_set->data = malloc(sizeof(int) * new_set->capacity);

    for (int i = 0; i < card(current); i++) {
        for(int j = 0; j < card(set2); j++){
            if(current->data[i] == set2->data[j]){
                break;
            } else {
                new_set->data[new_set->size] = current->data[i];
                new_set->size++;
            }
        }
    }
    return new_set;
}
bool isEmpty(const intSet set){
    if (set->size == 0) {
        return true;
    }
    return false;
}
int *toArray(const intSet set, int *size) {
    *size = set->size;
    int *newArray = malloc(sizeof(int) * set->size);

    for (int i = 0; i < set->size; i++) {
        newArray[i] = set->data[i];
    }

    int temp;
        for (int i = 0; i < set->size-1; i++) {
            for (int j = 0; j < set->size-i-1; j++) {
                if (newArray[j] > newArray[j+1]) {
                temp = newArray[j];
                newArray[j] = newArray[j+1];
                newArray[j+1] = temp;
            }
        }
    }

    return newArray;
}
char *toString(const intSet set){
    int total_elements = 0;
    int *sorted_data = toArray(set, &total_elements);

    char *str = malloc(sizeof(char) * (total_elements * 20 + 3));

    strcpy(str, "{");

    for (int i = 0; i < total_elements; i++) {
        char buffer[32];
        if (i == total_elements - 1) {
            snprintf(buffer, sizeof(buffer), "%d", sorted_data[i]);
        } else {
            snprintf(buffer, sizeof(buffer), "%d,", sorted_data[i]);
        }
        strcat(str, buffer);
    }

    strcat(str, "}");

    free(sorted_data);
    return str;
}
