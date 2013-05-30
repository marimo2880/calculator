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

#endif /* HASH_H_ */