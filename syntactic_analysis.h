#ifndef SYNTACTIC_H_
#define SYNTACTIC_H_

extern int tp;//tp番目のtokenを読む
extern int token_type;//読み取ったトークンの種類
extern double token_const;//読み取ったトークンの数値
extern char *token_name;//読み取ったトークンの変数

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

Tree head;//Tree型の構造体headを宣言。式の時に使用

void init_syntactic(void);
int read_token(void);//次のトークンを読む
double read_num(void);//数字の読みこみ
void syntactic_analysis(void);//構文解析を行う
void assignment(void);//代入の関数
Tree expression(void);//式の関数
Tree term(void);//項の関数
Tree primary(void);//素の関数
void print_tree(Tree head, int h);//木の表示を行う

#endif /* SYNTACTIC_H_ */

