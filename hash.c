#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASHSIZE 97

static List hashtable[HASHSIZE];//List型の構造体hashtableを宣言

/* 変数のハッシュ値を返す */
unsigned long hash(const char *val)//int:4byte long:8byte
{
    int i;
    int hash_no = 5381;//djb2
    for (i = 0; val[i] != '\0'; i++) {
        hash_no = hash_no * 33 + val[i];
    }
    return hash_no;
}

unsigned long hash_number(const char *val)
{
	return hash(val) % HASHSIZE;
}

/* 変数がハッシュテーブルに存在する場合 */
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

/* ハッシュテーブルを初期化 */
void init_hashtable(void)
{
    int i;
    for (i = 0; i < HASHSIZE; i++) {
        hashtable[i] = NULL;
    }
}

List create_node(const char *key, double data)
{
    List new_node = malloc(sizeof(List)); 
	new_node->key = malloc(strlen(key) + 1);//+1:\0
    strcpy(new_node->key,key);//all data copy
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}


/* 登録に成功したら1、失敗したら(既に登録済みなら)0を返す */
void insert(const char *key, double data)
{
    List node;
    node = find_node(key);

    if (node == NULL) {
    	int h = hash_number(key);
        List new_node = create_node(key, data);

        if (hashtable[h] == NULL) {
            hashtable[h] = new_node;
        } else {
            List ptr;
            for (ptr = hashtable[h]; ptr->next != NULL; ptr = ptr->next);
            ptr->next = new_node;
        }
    } else {
        node->data = data;
    }
}

void print_hashtable(void)
{
    int i;
    List ptr;
    for (i = 0; i < HASHSIZE; i++) {
        if (hashtable[i] != NULL) {
            for (ptr = hashtable[i]; ptr != NULL; ptr = ptr->next) {
                printf("Hash number = %d, Value = %s, Value number =%d\n",i,ptr->key,ptr->data);
            }
        }
    }
}