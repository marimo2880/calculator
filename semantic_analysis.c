#include "lexical_analysis.h"
#include "syntactic_analysis.h"
#include "semantic_analysis.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double semantic_analysis(Tree head)
{
    double ans = 0.0;
    if(head != NULL){

    	switch(head->token_node){
    		case Const: case Name:
    		   ans = head->token_number;
    		   return ans;
    		   break;

    		case Plus:
		//head->token_node = Const;//トークンの種類をconstに変更
		    ans = semantic_analysis(head->left) + semantic_analysis(head->right);//計算を行う
		    return ans;
		    free(head->left);
		    free(head->right);
		    break;

	        case Minus:
		    ans = semantic_analysis(head->left) - semantic_analysis(head->right);//計算を行う
		    return ans;
		    free(head->left);
		    free(head->right);
		    break;

	        case Times:
		    ans = semantic_analysis(head->left) * semantic_analysis(head->right);//計算を行う
		    return ans;
		    free(head->left);
		    free(head->right);
		    break;

	        case Divide:
		    ans = semantic_analysis(head->left) / semantic_analysis(head->right);//計算を行う
		    return ans;
		    free(head->left);
		    free(head->right);
		    break;

	        default:
		    break;
	}
    }
    return ans;
}

void print_answer(void)
{
    double ans = 0.0;
    ans = semantic_analysis(head);

    if (error == False){
    	printf("\n\n ----------------------SemanticAnalysis--------------------------\n");
    	printf(" Ans = %lf\n",ans);
    	printf(" --------------------END SemanticAnalysis------------------------\n\n\n");
    }
}
