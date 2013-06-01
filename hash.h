#ifndef HASH_H_
#define HASH_H_

/* ハッシュテーブルの構造体 */
struct _list{
    char *key;//変数
    double data;//数値
    struct _list *next;
};

typedef struct _list *List;

void init_hashtable(void);
unsigned long hash(const char *val);
unsigned long hash_number(const char *val);
List find_node(const char *key);
List create_node(const char *key, double data);
void insert(const char *key, double data);
void print_hashtable(void);
double search(char *key);

#endif /* HASH_H_ */