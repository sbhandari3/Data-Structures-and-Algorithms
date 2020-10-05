/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA5
* Lex.c
* Lex.c tests methods from Dictionary.c and uses them and prints the file in key order.
*********************************************************************************/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"
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
        
	Dictionary D = newDictionary(0);
        int j = 0;
	for(j = 0; j < count; j++){
		insert(D,array[j],j);
	}
        //print to output file
        int a;
    	for (a = beginForward(D); currentVal(D) != VAL_UNDEF; a = next(D)){
        	fprintf(out, "%s", array[currentVal(D)]);
    	}

        //free memory
        fclose(in);
        fclose(out);
        for(int k = 0; k < count; k++){
                free(array[k]);
        }
        free(array);
        freeDictionary(&D);
        return(0);
}


