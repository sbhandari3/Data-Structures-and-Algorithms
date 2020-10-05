/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA5
* DictionaryTest.c
* DictionaryTest.c tests methods from Dictionary.c 
*********************************************************************************/
//-----------------------------------------------------------------------------
// DictionaryClient.c
// Test client for Dictionary ADT
//-----------------------------------------------------------------------------:


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"

int main(){
    Dictionary A = newDictionary(1);
    Dictionary B = newDictionary(0);
    int i;
    char *Dict[] = {
        "An", "Ban","Can"};
     

    // NonEmpty_makeEmpty Test
    insert(A, "c", 3);
    insert(A, "b", 2);
    insert(A, "a", 1);
    beginForward(A);
    makeEmpty(A);
    if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF || size(A) != 0)
        printf("Test NonEmpty_makeEmpty: FAILED: test 1\n");

    // Delete_value Test
    insert(A, "e", 25);
    insert(A, "g", 30);
    delete (A, "a");
    if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF)
        printf("Test Delete_value: FAILED: test 1\n");
    beginReverse(A);
    delete (A, "d");
    
    makeEmpty(A);
      // print Dictionary B after deletions
   printf("Dictionary B (%sunique keys):\n", (getUnique(B)?"":"non-"));
   printf("after deletions:\n");
   printDictionary(stdout, B);
   printf("\n");


   // insert duplicates into A ----------------------------
   for(i=1; i<n; i+=2){
      insert(A, word[i], i);
   }

   // print Dictionary A after insertions
   printf("Dictionary A (%sunique keys):\n", (getUnique(A)?"":"non-"));
   printf("after insertions:\n");
   printDictionary(stdout, A);
   printf("\n");

   // uncomment line below to get error message
   // insert(B, word[10], 10);
   // Dictionary Error: 
   // calling insert() on existing key: e

    // NonUnique_beginForward Test
    insert(B, "d", 2);
    //insert(B, "d", 5);
   // insert(B, "d", 1);
    if (beginForward(B) != 2)
        printf("Test NonUnique_beginForward: FAILED: test 1\n");
    next(B);
    if (currentVal(B) != 5)
        printf("Test NonUnique_beginForward: FAILED: test 2\n");

    for (i = 0; i < 42; i++)
        insert(A, wordList[i], i);
    printDictionary(stdout, A);
    printf("forward A:\n");
    for (i = beginForward(A); currentVal(A) != VAL_UNDEF; i = next(A)){
        printf("key: " KEY_FORMAT " value: " VAL_FORMAT "\n", currentKey(A), i);
    }
    makeEmpty(A);
    printDictionary(stdout, A);
    freeDictionary(&A);
    freeDictionary(&B);
