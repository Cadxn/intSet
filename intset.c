#include <stdbool.h>

#ifndef INTSET_H
#define INTSET_H

typedef struct intsetType *intSet;

intSet createSet(){

}
void destroySet(intSet set){

}
void clear(intSet set){

}
int card(const intSet set){

}
bool equals(const intSet set1, const intSet set2){

}
bool contains(const intSet set, int value){

}
int largest(const intSet set){

}
int smallest(const intSet set){

}
void add(intSet set, int value){

}
void remove_(intSet set, int value){

}
intSet union_(const intSet set1, const intSet set2){

}
intSet intersection(const intSet set1, const intSet set2){

}
intSet diff(const intSet set1, const intSet set2){

}
bool isEmpty(const intSet set){

}
int *toArray(const intSet set, int *size){

}
char *toString(const intSet set){

}

#endif