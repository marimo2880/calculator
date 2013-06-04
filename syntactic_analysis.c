#include "lexical_analysis.h"
#include "syntactic_analysis.h"
#include "semantic_analysis.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int tp = 0;//tp番目のtokenを読む
int token_type = 0;//読み取ったトークンの種類
double token_const = 0.0;//読み取ったトークンの数値
char *token_name;

/* グローバル変数を初期化 */
void init_syntactic(void)
{
	tp = 0;
	token_type = 0;
	token_const = 0.0;
}

/* 次のトークンのタイプ・数値・変数のスペルを得る */
int read_token(void)
{
    token_type = token[tp].type;
    token_name = token[tp].name;
    if (token_type != Endtoken) {
	tp++;
    }
    return token_type;
}

/* 数値を得る */
double read_num(void)
{
    token_const = token[tp - 1].number;
    return token_const;
}

/* 構文解析 */
void syntactic_analysis(void)
{
    if (error == False) printf("\n ----------------------SyntaxAnalysis---------------------------\n");

    if(pair_check != 0){//括弧の個数が合わなかったらエラー
	 if (error == False) printf(" Syntax Error!!\n");
	 error = True;
    }

    switch(token[total_token - 1].type){
    case Plus: case Minus: case Times: case Divide: case Lpra:
	if (error == False)  printf(" Syntax Error!!\n");
	error = True;
	break;
    default:
	break;
    }

    read_token();//トークン0番目を読む

    if (error == False) printf(" Tree:\n");
    if (equal_flag == 0) {
	head = expression();
	print_tree(head, 0);
	if (error == False) printf(" --------------------END SyntaxAnalysis--------------------------\n");
    }

    if (equal_flag == 1){//代入文だったら代入の関数を呼び出す
	assignment();
    }
}

/* 代入文の関数 */
void assignment(void)
{
    Tree equal, hensu;
    double val_info = 0.0;

    printf("assignment\n");

    hensu = malloc(sizeof(*hensu));
    hensu->token_node = Name; hensu->token_value = token_name;
    hensu->right = NULL; hensu->left = NULL;

    read_token();
    read_token();

    equal = malloc(sizeof(*equal));
    equal->token_node = Equal; equal->right = expression(); equal->left = hensu;

    print_tree(equal, 0);//=を根とした木の表示
    if (error == False) printf(" --------------------END SyntaxAnalysis--------------------------\n");
    val_info = semantic_analysis(equal->right);
    insert(token[0].name,val_info);
}

/* 式の関数 */
Tree expression(void)
{
    int count =0;
    Tree head, hidari, plus, minus, zero;

    if (token_type == Minus){//式のはじめが-だったら
	read_token();
	zero = malloc(sizeof(*zero));
	zero->token_node = Const; zero->token_number = 0; //数値0のノードを作成
	minus = malloc(sizeof(*minus)); minus->token_node = Minus;
	hidari = minus; minus->right = term(); minus->left = zero;
    }else{
	/*式のはじめをterから受け取る場合*/
	hidari = term();
    }

    while(token_type == Plus || token_type == Minus){
	switch(token_type){
	case Plus:
	    read_token();
	    /*木を作る*/
	    plus = malloc(sizeof(*plus)); plus->token_node = Plus;
	    head = plus; plus->right = term(); plus->left = hidari;
	    hidari = plus;
	    count++;
	    break;

	case Minus:
	    read_token();
	    /*木を作る*/
	    minus = malloc(sizeof(*minus)); minus->token_node = Minus;
	    head = minus; minus->right = term(); minus->left = hidari;
	    hidari = minus;
	    count++;
	    break;
	}

    }
    // printf("head node ---  %d\n",head->token_node);//＋ノードの出力

    if(count == 0){
	head = hidari;
    }
    // printf("expression\n");
      return head;
}

/* 項の関数 */
Tree term(void)
{
    int count = 0;
    Tree head, hidari, times, divide;

    hidari =  primary();

    while(token_type == Times || token_type == Divide){
	switch(token_type){
	case Times:
	    read_token();
	    /*木をつくる*/
	    times = malloc(sizeof(*times)); times->token_node = Times;
	    head = times; times->right = primary(); times->left = hidari;
	    hidari = times;
	    //    printf("* node  %d\n",head->right);
	    count++;
	    break;

	case Divide:
	    read_token();
	    /*木をつくる*/
	    divide = malloc(sizeof(*divide)); divide->token_node = Divide;
	    head = divide; divide->right = primary(); divide->left = hidari;
	    hidari = divide;
	    count++;
	    break;
	}
    }

    if(count == 0){
	head = hidari;
    }

//  printf("term\n");
      return head;

}

/* 素の関数 */
Tree primary(void)
{
    Tree head, cons, name;

    switch(token_type){
    case Const:
	/*木を作る*/
	cons = malloc(sizeof(*cons));
  cons->token_number = read_num();
	cons->token_node = Const;
//	printf("token_const %lf",token_const);
	head = cons; cons->left = NULL; cons->right = NULL; //数値の木を作る

	read_token();//読み進める。初回なら1+2*3だったら+をみる
	break;

    case Name:
	/*木を作る*/
	name = malloc(sizeof(*name)); name->token_value = token_name;
	head = name; name->left = NULL; name->right = NULL;//変数名の木を作る
	name->token_node = Name;
	name->token_number = search(token_name);
	read_token();
	break;

    case Lpra://headにexpression()から返ってきたものを入れる。
	read_token();//括弧の中を一つ読む
	head = expression();//ここは結構怪しい。式として括弧内を処理。閉じ括弧のトークン見ているときに抜けてくるはず
	if(token_type == Rpra){//ここもtoken_type使うと上のswitchとの兼ね合い大丈夫なのかな
	read_token();
	}else{
		if (error == False) printf(" Syntax Error!!\n");
		error = True;
	}
	break;

    default:
	 if (error == False) printf(" Syntax Error!!\n");//エラーの関数もあとで追加する
	 error = True;
	 break;

    }

//    printf("primary\n");
    return head;
}

/* 構文木のプリント */
void print_tree(Tree head, int h){
    if (error == False){
	int i;

	if(head != NULL){
	    print_tree(head->right, h + 1);
	    for(i = 0; i < h; i++){
		printf("\t");
	    }
	    /*token_nodeの種類によってprintするものをわける*/
	    switch(head->token_node){
	    case Name:
		head->tree_depth = h;
		printf("%s (%d)\n\n",head->token_value,h);
		break;
	    case Const:
		head->tree_depth = h;
		printf("%d (%d)\n\n",(int)(head->token_number),h);
		break;
	    case Plus:
		head->tree_depth = h;
		printf("+ (%d)\n\n",h);
		break;
	    case Minus:
		head->tree_depth = h;
		printf("- (%d)\n\n",h);
		break;
	    case Times:
		head->tree_depth = h;
		printf("* (%d)\n\n",h);
		break;
	    case Divide:
		head->tree_depth = h;
		printf("/ (%d)\n\n",h);
		break;
            case Equal:
                head->tree_depth = h;
                printf("= (%d)\n\n",h);
	    }
//	printf("%d\n",head->token_node);
	    print_tree(head->left, h + 1);
	}
	}
}

