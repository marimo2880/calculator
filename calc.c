/* �إå����ե�����򥤥󥯥롼�� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* �����Х��ѿ������ */
int ch_no = 0;//ch_no���ܤ�ʸ�����ɤ�
char ch;//�ɤ߼�ä�ʸ��
char *statement = NULL;//���Ϥ��줿ʸ������Ǽ
int tp = 0;//tp���ܤ�token���ɤ�
int token_type = 0;//�ɤ߼�ä��ȡ�����μ���
double token_const = 0;//�ɤ߼�ä��ȡ�����ο���
char *token_name = NULL;//�ɤ߼�ä��ȡ�������ѿ�
int equal_flag = 0;//��������ο�
int pair_check = 0;//��̤ο�
int total_token = 0;//�ȡ�����ο�
int error;//���顼�����뤫�ɤ���(True or False)

enum{
    True = 1, False = -1
};

enum{

    /* �ѿ�,���� */
    Name, Const,

    /* �黻��(+,-,*,/,=) */
    Plus, Minus, Times, Divide, Equal,

    /* ��� */
    Lpra, Rpra,

    /* ���,\0,EOF */

    Nontoken, Endtoken//, Endfile
};


/* �ȡ�����ξ�����Ǽ */
struct _token{
    char *name;//�ѿ�
    double number;//����
    int type;//�ȡ�����μ���
}*token;


/* ��ʸ�ڤι�¤�� */
struct tree{
    int token_node;//�黻�Ҥγ�Ǽ
    double token_number;//���ͤγ�Ǽ
    char *token_value;//�ѿ��γ�Ǽ
    int tree_depth;//�ڤο���
    struct tree *left;//������ʬ��
    struct tree *right;///������ʬ��
};

typedef struct tree *Tree;

Tree head;//Tree���ι�¤��head�����

/* �ؿ������ */
void init_token();//�ȡ�����ν����
//void init_statement(char*);
//void init_tree();//��ʸ�ڤν����
void read_char();//���Ϥ��줿ʸ������ʸ�����Ļ��Ȥ���
char* convert_to_value();//�ѿ��ΤޤȤޤ���Ѵ�����
double convert_to_number();//���ͤΤޤȤޤ���Ѵ�����
void LexicalAnalysis();//������Ϥ�Ԥ�

int read_token();//���Υȡ�������ɤ�
double read_num();//�������ɤߤ���
int SyntaxAnalysis();//��ʸ���Ϥ�Ԥ�
int assignment();//�����ν�����Ԥ�
Tree expression();//���δؿ�
Tree term();//��δؿ�
Tree primary();//�Ǥδؿ�
void print_tree(Tree, int);//�ڤ�ɽ����Ԥ�

double SemanticAnalysis(Tree);//��̣���Ϥ�Ԥ�

/* ���Ϥ��줿ʸ������ʸ�����Ļ��Ȥ��� */
void read_char()
{
    ch = statement[ch_no];
    if (ch != '\0') ch_no += 1;
}

/* �ȡ�����䥰���Х��ѿ������� */
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

/* ��ʸ�ڤ����� */
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

/* �ѻ����ѿ����Ѵ� */
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

/* ��������ͤ��Ѵ� */
double convert_to_number()
{
    double number = 0.0;
    while ('0'<=ch && ch<='9') {
        number = number*10 + ch - '0';
        read_char();
    }
    return number;
}

/* ������� */
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
	    printf("%d   ",token[i-1].number);
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

/* ���Υȡ�����Υ����ס����͡��ѿ��Υ��ڥ������ */
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

/* ��ʸ���� */
int SyntaxAnalysis()
{
    if (error == False) printf("\n ----------------------SyntaxAnalysis---------------------------\n");

    if(pair_check != 0){//��̤θĿ������ʤ��ä��饨�顼
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

    read_token();//�ȡ�����0���ܤ��ɤ�

    if (equal_flag == 1){//����ʸ���ä��������δؿ���ƤӽФ� 
	assignment();
    } else {
	head = expression();//�����Ǥʤ��ä��鼰�δؿ���ƤӽФ�
    }
   
    if (error == False) printf(" Tree:\n");
    print_tree(head, 0);

    
    if (error == False) printf(" --------------------END SyntaxAnalysis--------------------------\n");
}

/* ����ʸ�δؿ� */
int assignment()
{
    printf("assignment\n");
    return 0;
}

/* ���δؿ� */
Tree expression()
{
    int count =0;
    Tree head, hidari, plus, minus, zero;


    if (token_type == Minus){//���ΤϤ��᤬-���ä���
	read_token();
	zero = malloc(sizeof(*zero));
	zero->token_node = Const; zero->token_number = 0; //����0�ΥΡ��ɤ����
	minus = malloc(sizeof(*minus)); minus->token_node = Minus;
	hidari = minus; minus->right = term(); minus->left = zero;
    }else{
	/*���ΤϤ����ter������������*/
	hidari = term();
    }

    while(token_type == Plus || token_type == Minus){
	switch(token_type){
	case Plus:
	    read_token();
	    /*�ڤ���*/
	    plus = malloc(sizeof(*plus)); plus->token_node = Plus;
	    head = plus; plus->right = term(); plus->left = hidari;
	    hidari = plus;
	    count++;
	    break;
	
	case Minus:
	    read_token();
	    /*�ڤ���*/
	    minus = malloc(sizeof(*minus)); minus->token_node = Minus;
	    head = minus; minus->right = term(); minus->left = hidari;
	    hidari = minus;
	    count++;
	    break;
	}
    
    }
    // printf("head node ---  %d\n",head->token_node);//�ܥΡ��ɤν���

    if(count == 0){
	head = hidari;
    }


    // printf("expression\n");
      return head;

}

/* ��δؿ� */
Tree term()
{
    int count = 0;
    Tree head, hidari, times, divide;

    hidari =  primary();

    while(token_type == Times || token_type == Divide){
	switch(token_type){
	case Times:
	    read_token();
	    /*�ڤ�Ĥ���*/
	    times = malloc(sizeof(*times)); times->token_node = Times;
	    head = times; times->right = primary(); times->left = hidari;
	    hidari = times;
	    //    printf("* node  %d\n",head->right);
	    count++;
	    break;

	case Divide:
	    read_token();
	    /*�ڤ�Ĥ���*/
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

/* �Ǥδؿ� */
Tree primary()
{
    Tree head, cons, name;

    switch(token_type){
    case Const:
	/*�ڤ���*/
	cons = malloc(sizeof(*cons)); cons->token_number = read_num();
	cons->token_node = Const;
//	printf("token_const %lf",token_const);
	head = cons; cons->left = NULL; cons->right = NULL; //���ͤ��ڤ���

	read_token();//�ɤ߿ʤ�롣���ʤ�1+2*3���ä���+��ߤ�
	break;

    case Name:
	/*�ڤ���*/
	name = malloc(sizeof(*name)); name->token_value = token_name;
	head = name; name->left = NULL; name->right = NULL;//�ѿ�̾���ڤ���
	name->token_node = Name;
	read_token();
	break;

    case Lpra://head��expression()�����֤äƤ�����Τ�����롣
	read_token();//��̤�������ɤ�
	head = expression();//�����Ϸ빽�����������Ȥ��Ƴ�����������Ĥ���̤Υȡ����󸫤Ƥ���Ȥ���ȴ���Ƥ���Ϥ�
	if(token_type == Rpra){//������token_type�Ȥ��Ⱦ��switch�Ȥη�͹礤����פʤΤ���
	read_token();
	}else{
	     if (error == False) printf(" Syntax Error!!\n");
	    error = True;
	}
	break;
		
    default:
	 if (error == False) printf(" Syntax Error!!\n");//���顼�δؿ��⤢�Ȥ��ɲä���
	error = True;
	break;
       
    }
   
//    printf("primary\n");
    return head;

}

/* ��ʸ�ڤΥץ��� */
void print_tree(Tree head, int h){
    if (error == False){
	int i;
	
	if(head != NULL){
	    print_tree(head->right, h + 1);
	    for(i = 0; i < h; i++){
		printf("\t");
	    }
	    /*token_node�μ���ˤ�ä�print�����Τ�櫓��*/
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
		//	head->token_node = Const;//�ȡ�����μ����const���ѹ�
		return SemanticAnalysis(head->left) + SemanticAnalysis(head->right);//�׻���Ԥ�
		free(head->left);
		free(head->right);
		break;

	    case Minus:
		return SemanticAnalysis(head->left) - SemanticAnalysis(head->right);//�׻���Ԥ�
		free(head->left);
		free(head->right);
		break;

	    case Times:
	        return SemanticAnalysis(head->left) * SemanticAnalysis(head->right);//�׻���Ԥ�
		free(head->left);
		free(head->right);
		break;

	    case Divide:
	        return SemanticAnalysis(head->left) / SemanticAnalysis(head->right);//�׻���Ԥ�
		free(head->left);
		free(head->right);
		break;



	    default:
		break;
	    }

	
      }
    //  return num;
}

/* main�ؿ� */
int main()
{  
	
    for(;;) {
	int i = 0;
	double num = 0;

	statement = (char*)malloc(sizeof(*statement)*100);	
	token = malloc(sizeof(*token)*100);//�ȡ������ΰ�γ���   
	//	init_statement(statement);
	init_token();
      
        /* ���Ϥ�����դ��� */
	printf("\n > ");
	while ((statement[i++] = getchar()) != '\n') ;
	statement[i-1] = '\0';
	
	if(strcmp(statement, "end") == 0) return 0;
 

	//init_tree();
	/* ������� */
	LexicalAnalysis();


        /* ��ʸ���� */
        SyntaxAnalysis();
	if (error == False){
	/*��̣����*/
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
