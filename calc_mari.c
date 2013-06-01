/* ヘッダーファイルをインクルード */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* グローバル変数の宣言 */
int ch_no = 0;//ch_no番目の文字を読む
char ch;//読み取った文字
char *statement = NULL;//入力された文字列を格納
int tp = 0;//tp番目のtokenを読む
int token_type = 0;//読み取ったトークンの種類
double token_const = 0;//読み取ったトークンの数値
char *token_name = NULL;//読み取ったトークンの変数
int equal_flag = 0;//イコールの数
int pair_check = 0;//括弧の数
int total_token = 0;//トークンの数
int error;//エラーがあるかどうか(True or False)

#define HASHSIZE 97

enum{
    True = 1, False = -1
};

enum{

    /* 変数,数値 */
    Name, Const,

    /* 演算子(+,-,*,/,=) */
    Plus, Minus, Times, Divide, Equal,

    /* 括弧 */
    Lpra, Rpra,

    /* 誤り,\0,EOF */

    Nontoken, Endtoken//, Endfile
};


/* トークンの情報を格納 */
struct _token{
    char *name;//変数
    double number;//数値
    int type;//トークンの種類
}*token;



/* 構文木の構造体 */
struct tree{
    int token_node;//演算子の格納
    double token_number;//数値の格納
    char *token_value;//変数の格納
    int tree_depth;//木の深さ
    struct tree *left;//左の部分木
    struct tree *right;///右の部分木
};

typedef struct tree *Tree;

Tree head;//Tree型の構造体headを宣言


/* ハッシュテーブルの構造体 */
struct _list{
    char *key;//変数
    int data;//数値
    struct _list *next;//次のlistへのポインタ
};

typedef struct _list *List;

List hashtable[HASHSIZE];//List型の構造体hashtableを宣言
//List equalkey = NULL;

/* 関数の宣言 */
void init_token();//トークンの初期化
//void init_statement(char*);
//void init_tree();//構文木の初期化
void read_char();//入力された文字列を一文字ずつ参照する
char* convert_to_value();//変数のまとまりに変換する
double convert_to_number();//数値のまとまりに変換する
void LexicalAnalysis();//字句解析を行う

//void init_hashtable();//ハッシュテーブルの初期化
//int hash(char *val);//ハッシュ値を返す
//void insert(char *key,double data);
//int find_val(char *key);
//int equal_val(char *val1,char *val2);
//void print_hashtable();

int read_token();//次のトークンを読む
double read_num();//数字の読みこみ
int SyntaxAnalysis();//構文解析を行う
int assignment();//代入の処理を行う
Tree expression();//式の関数
Tree term();//項の関数
Tree primary();//素の関数
void print_tree(Tree, int);//木の表示を行う

double SemanticAnalysis(Tree);//意味解析を行う

/* 入力された文字列を一文字ずつ参照する */
void read_char()
{
    ch = statement[ch_no];
    if (ch != '\0') ch_no += 1;
}

/* トークンやグローバル変数を初期化 */
void init_token()
{
    int i;
    for (i = 0; i < 100; i++) {
	token[i].name = NULL;
	token[i].number = 0;
	token[i].type = 0;
    }
    ch = '\0';
    token_const = 0;
    total_token = 0;
    ch_no = 0;
    tp = 0;
    pair_check = 0;
    error = False;
}

/* 構文木を初期化 */
/*
void init_tree()
{
    head->token_node = 0;
    head->token_number = 0.0;
    head->token_value = NULL;
    head->tree_depth = 0;
    head->left = NULL;
    head->right = NULL;
}
*/

/* 英字を変数に変換 */
char* convert_to_value()
{
    int i = 0;
    char *value;
    value = (char*)malloc(sizeof(*value)*100);

    while (('a'<=ch && ch<='z') || ('A'<=ch && ch<= 'Z') || ('0'<=ch && ch<='9')) {
        value[i++] = ch;
        read_char();
    }
    return value;
}

/* 数字を数値に変換 */
double convert_to_number()
{
    double number = 0.0;
    while ('0'<=ch && ch<='9') {
        number = number*10 + ch - '0';
        read_char();
    }
    return number;
}

/* 字句解析 */
void LexicalAnalysis()
{
    printf(" ----------------------LexicalAnalysis--------------------------\n\n");
    int i = 0;
    read_char();

    while (ch != '\0') {
        switch(ch) {
        case ' ':
            read_char();
            break;
//        case EOF:
//            token[i++].type = Endfile;
//            break;
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i':
        case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
        case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I':
        case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
        case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
            token[i].type = Name;
            token[i++].name = convert_to_value();
	    printf("%s   ",token[i-1].name);
	    total_token++;
            break;
        case '0':
            token[i].type = Const;
            token[i++].number = 0;
	    printf("%f   ",token[i-1].number);
	    total_token++;
            read_char();
            break;
        case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            token[i].type = Const;
            token[i++].number = convert_to_number();
	    printf("%lf   ",token[i-1].number);
	    total_token++;
            break;
        case '+':
            token[i++].type = Plus;
	    printf("+   ");
	    total_token++;            
	    read_char();
            break;
        case '-':
            token[i++].type = Minus;
	    printf("-   ");
	    total_token++;
            read_char();
            break;
        case '*':
            token[i++].type = Times;
	    printf("*   ");
	    total_token++;
            read_char();
            break;
        case '/':
            token[i++].type = Divide;
	    printf("/   ");
	    total_token++;
            read_char();
            break;
        case '=':
            token[i++].type = Equal;
	    printf("=   ");
            equal_flag += 1;
	    total_token++;
            read_char();
            break;
        case '(':
            token[i++].type = Lpra;
	    printf("(   ");
	    pair_check++;
	    total_token++;
            read_char();
            break;
        case ')':
            token[i++].type = Rpra;
	    printf(")   ");
	    pair_check--;
	    total_token++;
            read_char();
            break;
        case '\0':
            token[i++].type = Endtoken;
	    total_token++;
            break;
        default:
	    error = True;
	    token[i].type = Nontoken;
	    printf("%c   ",ch);
	    read_char();
	    break;
        }
    }

    printf("\n\n Total token = %d",total_token);
    if(error == True) printf("\nError!!\n");
    if (error == False) printf("\n\n -------------------END LexcialAnalysis-------------------------\n");
}

/* 次のトークンのタイプ・数値・変数のスペルを得る */
int read_token()
{
    token_type = token[tp].type;
    token_name = token[tp].name;
    if (token_type != Endtoken) {
	tp++;
    } 
    return token_type;
}

double read_num(){
    token_const = token[tp - 1].number;
    return token_const;

}

/* 構文解析 */
int SyntaxAnalysis()
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

    if (equal_flag == 1){//代入文だったら代入の関数を呼び出す 
	assignment();
    } else {
	head = expression();//そうでなかったら式の関数を呼び出す
    }
   
    if (error == False) printf(" Tree:\n");
    print_tree(head, 0);

    
    if (error == False) printf(" --------------------END SyntaxAnalysis--------------------------\n");
}

/* 代入文の関数 */
int assignment()
{
    insert(token[0].name,token[2].number);
    printf("assignment\n");
    return 0;
}

/* 式の関数 */
Tree expression()
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
Tree term()
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
Tree primary()
{
    Tree head, cons, name;

    switch(token_type){
    case Const:
	/*木を作る*/
	cons = malloc(sizeof(*cons)); cons->token_number = read_num();
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
	    }
//	printf("%d\n",head->token_node);
	    print_tree(head->left, h + 1);
	}
    }
    
}

double SemanticAnalysis(Tree head){

    if(head != NULL){


	    switch(head->token_node){
	    case Const: case Name:
		return head->token_number;
		break;

	    case Plus:
		//	head->token_node = Const;//トークンの種類をconstに変更
		return SemanticAnalysis(head->left) + SemanticAnalysis(head->right);//計算を行う
		free(head->left);
		free(head->right);
		break;

	    case Minus:
		return SemanticAnalysis(head->left) - SemanticAnalysis(head->right);//計算を行う
		free(head->left);
		free(head->right);
		break;

	    case Times:
	        return SemanticAnalysis(head->left) * SemanticAnalysis(head->right);//計算を行う
		free(head->left);
		free(head->right);
		break;

	    case Divide:
	        return SemanticAnalysis(head->left) / SemanticAnalysis(head->right);//計算を行う
		free(head->left);
		free(head->right);
		break;



	    default:
		break;
	    }

	
      }
    //  return num;
}

/* main関数 */
int main()
{  
	
    for(;;) {
	int i = 0;
	double num = 0;

	statement = (char*)malloc(sizeof(*statement)*100);	
	token = malloc(sizeof(*token)*100);//トークン領域の確保   
	//	init_statement(statement);
	init_token();
      
        /* 入力を受け付ける */
	printf("\n > ");
	while ((statement[i++] = getchar()) != '\n') ;
	statement[i-1] = '\0';
	
	if(strcmp(statement, "end") == 0) return 0;
 

	//init_tree();
	/* 字句解析 */
	LexicalAnalysis();


        /* 構文解析 */
        SyntaxAnalysis();
	if (error == False){
	/*意味解析*/
	    printf("\n\n ----------------------SemanticAnalysis--------------------------\n");
	    num = SemanticAnalysis(head);
	    printf(" Ans = %lf\n",num);
	    printf(" --------------------END SemanticAnalysis------------------------\n\n\n");
	}
	free(statement);
	free(token);


    }
    return 0;
}
