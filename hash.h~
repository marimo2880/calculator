#ifndef HASH_H_
#define HASH_H_

/* ハッシュテーブルの構造体 */
struct _list{
    char *key;//変数
    int data;//数値
    struct _list *next;//次のlistへのポインタ
};

typedef struct _list *List;

unsigned long hash(const char *val);
unsigned long hash_number(const char *val);
List find_node(const char *key);
void init_hashtable(void);
List create_node(const char *key, double data);
void insert(const char *key, double data);
void print_hashtable(void);



#endif /* HASH_H_ */