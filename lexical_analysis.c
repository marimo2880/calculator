#include "lexical_analysis.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char ch = '\0';
int total_token = 0;
int ch_no = 0;
int pair_check = 0;
int error = False;
int equal_flag = 0;

/* トークンとグローバル変数を初期化 */
void init_lexical(void)
{
    
    int i;
    for (i = 0; i < 100; i++) {
        token[i].name = NULL;
        token[i].number = 0;
        token[i].type = 0;
    }
    
    
    
    ch = '\0';
    total_token = 0;
    ch_no = 0;
    pair_check = 0;
    error = False;
    equal_flag = 0;
}

/* 入力された文字列を一文字ずつ参照する */
void read_char(void)
{
    ch = statement[ch_no];
    if (ch != '\0') ch_no += 1;
}

/* 英字を変数に変換 */
char* convert_to_value(void)
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
double convert_to_number(void)
{
    double number = 0.0;
    while ('0'<=ch && ch<='9') {
        number = number*10 + ch - '0';
        read_char();
    }
    return number;
}

/* 字句解析 */
void lexical_analysis(void)
{
    printf(" ----------------------LexicalAnalysis--------------------------\n\n");
    int i = 0;
    //init_lexical();
    read_char();

    while (ch != '\0') {
        switch(ch) {
        case ' ':
            read_char();
            break;
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
            equal_flag++;
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

    printf("\n\nTotal token = %d",total_token);
    if(error == True) printf("\nLexical Error!!\n");
    if (error == False) printf("\n\n -------------------END LexcialAnalysis-------------------------\n");
}

