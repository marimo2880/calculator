#include "hash.h"
#include "lexical_analysis.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASHSIZE 97

static List hashtable[HASHSIZE];//List型の構造体hashtableを宣言

/* ハッシュテーブルの初期化 */
void init_hashtable(void)
{
    int i;
    for (i = 0; i < HASHSIZE; i++) {
        hashtable[i] = NULL;
    }
}

/* ハッシュテーブルを表示する */
void print_hashtable(void)
{
    int i;
    List ptr;
    for (i = 0; i < HASHSIZE; i++) {
        if (hashtable[i] != NULL) {
            for (ptr = hashtable[i]; ptr != NULL; ptr = ptr->next) {
                printf("Hash number = %d, Value = %s, Data =%f\n",i,ptr->key,ptr->data);
            }
        }
    }
}

/* 渡された変数からある規則で得られた数値を返す */
unsigned long hash(const char *val)//int:4byte long:8byte
{
    int i;
    int hash_no = 5381;//djb2
    for (i = 0; val[i] != '\0'; i++) {
        hash_no = hash_no * 33 + val[i];
    }
    return hash_no;
}

/* ハッシュ値を返す */
unsigned long hash_number(const char *val)
{
	return hash(val) % HASHSIZE;
}

/* 既に変数がハッシュテーブルに登録されているか調べる */
List find_node(const char *key)
{
    int h;
    List ptr;
    h = hash_number(key);

    for (ptr = hashtable[h]; ptr != NULL; ptr = ptr->next) {
        if (strcmp(ptr->key,key) == 0) {
            return ptr;
        }
    }
    return NULL;
}

/* 新規登録する */
List create_node(const char *key, double data)
{
    List new_node = malloc(sizeof(List)); 
	new_node->key = malloc(strlen(key) + 1);//+1は最後の'\0'分
    strcpy(new_node->key,key);//keyを指す先頭のアドレスではなくkeyの文字列自体を入れる
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/* 新規登録もしくは更新 */
void insert(const char *key, double data)
{
    List node;
    node = find_node(key);

    if (node == NULL) {//まだ登録されていなかったら
    	int h = hash_number(key);
        List new_node = create_node(key, data);//新規登録する

        if (hashtable[h] == NULL) {
            hashtable[h] = new_node;
        } else {
            List ptr;
            for (ptr = hashtable[h]; ptr->next != NULL; ptr = ptr->next);
            ptr->next = new_node;
        }
    } else {//既に変数が登録されていたら
        node->data = data;//変数のデータを上書きする
    }
    print_hashtable();
}

double search(char *key)
{
    int h = 0;
    List ptr;
    h = hash_number(key);

    for (ptr = hashtable[h]; ptr != NULL; ptr = ptr->next) {
        if (strcmp(ptr->key,key) == 0) {
            return ptr->data;
        }
    }
    printf("%s : Not exist!\n", key);
    error = True;
}

