/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA1
* Lex.c
* Lex.c tests methods from List.c and uses them to alphabetize lines of a file
*********************************************************************************/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#define MAX_LEN 160

int main(int argc, char * argv[]){
        int count = 0;
        FILE *in, *out;
        char line[MAX_LEN];
        if( argc != 3 ){
                printf("Usage: %s <input file> <output file>\n", argv[0]);
                exit(1);
        }

        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");
        if( in==NULL ){
                printf("Unable to open file %s for reading\n", argv[1]);
                exit(1);
        }
        if( out==NULL ){
                printf("Unable to open file %s for writing\n", argv[2]);
                exit(1);
        }
        //read file
        while (fgets(line, MAX_LEN, in ) != NULL){
                count++;
        }
        rewind(in);

        char** array = malloc((count) * sizeof(char*));

        for(int i = 0; i < count; i++){
                array[i] = malloc((MAX_LEN) * sizeof(char));
        }
	int cnt = 0;
        while(cnt < count) {
                fgets(array[cnt], MAX_LEN, in);
                cnt++;
        }
        //alphabetize char** array
        List Sort = newList();
        append(Sort, 0);
        for(int j = 1; j < count; j++) {
                moveBack(Sort);
                int tempj = j-1;
                while(tempj >= 0 && strcmp(array[j], array[get(Sort)]) <= 0)
                {
                        movePrev(Sort);
                        tempj--;
                }
	if(index(Sort) >= 0)
                        insertAfter(Sort, j);
                else
                        prepend(Sort, j);
        }
        //print to output file
        moveFront(Sort);
        while(index(Sort) > -1) {
            fprintf(out, "%s", array[get(Sort)]);
            moveNext(Sort);
        }
        //free memory
        fclose(in);
        fclose(out);
        for(int k = 0; k < count; k++){
                free(array[k]);
        }
        free(array);
        freeList(&Sort);
        return(0);
}

