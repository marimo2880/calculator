#include "lexical_analysis.h"
#include "syntactic_analysis.h"
#include "semantic_analysis.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *statement;

int main(void)
{  	
    init_hashtable();
    for(;;) {
    	int i = 0;
    	statement = (char*)malloc(sizeof(statement)*100);
    	token = malloc(sizeof(token)*100);

	init_lexical();
	init_syntactic();
      
	/* 入力 */
	printf("\nPlease input statement > ");
	while ((statement[i++] = getchar()) != '\n');
	statement[i-1] = '\0';

	if(strcmp(statement,"end") == 0) return 0;
	    
	lexical_analysis();//字句解析
	syntactic_analysis();//構文解析
	if (equal_flag == 0) {
	    print_answer();//意味解析
	}

	free(statement);
	free(token);
    }
    return 0;
}

