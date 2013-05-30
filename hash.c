#include "hash.h"
#include <stdlib.h>
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
List find_val(const char *key)
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

