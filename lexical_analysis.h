#ifndef LEXICAL_H_
#define LEXICAL_H_

extern int ch_no;//ch_no番目の文字を読む
extern char ch;//読み取った文字
extern char *statement;//入力された文字列
extern int equal_flag;//イコールの数
extern int pair_check;//括弧の数
extern int total_token;//トークンの数
extern int error;//エラーがあるかどうか(True or False)

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

    /* 誤り,\0 */
    Nontoken, Endtoken
};

/* トークンの情報を格納 */
struct _token{
    char *name;//変数
    double number;//数値
    int type;//トークンの種類
};

typedef struct _token *Token;

Token token;

/* 関数の宣言 */
void init_lexical(void);//トークンの初期化
void read_char(void);//入力された文字列を一文字ずつ参照する
char* convert_to_value(void);//変数のまとまりに変換する
double convert_to_number(void);//数値のまとまりに変換する
void lexical_analysis(void);//字句解析を行う

#endif /* LEXICAL_H_ */

