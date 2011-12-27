#ifndef __zc_hashtalbe_h
#define __zc_hashtalbe_h

#include <stdlib.h>

typedef struct zc_hashtable_entry_t {
	unsigned int hash_key;
	void *key;
	void *value;
	struct zc_hashtable_entry_t *prev;
	struct zc_hashtable_entry_t *next;
} zc_hashtable_entry_t;

typedef unsigned int (*zc_hashtable_hash_fn) (void *key);
typedef int (*zc_hashtable_equal_fn) (void *key1, void *key2);
typedef void (*zc_hashtable_del_fn) (void *kv);

typedef struct {
	size_t nelem;

	zc_hashtable_entry_t **tab;
	size_t tab_size;

	zc_hashtable_hash_fn hash_fn;
	zc_hashtable_equal_fn equal_fn;
	zc_hashtable_del_fn key_del_fn;
	zc_hashtable_del_fn value_del_fn;
} zc_hashtable_t;

zc_hashtable_t *zc_hashtable_new(size_t a_size,
				 zc_hashtable_hash_fn hash_fn,
				 zc_hashtable_equal_fn equal_fn, zc_hashtable_del_fn key_del_fn, zc_hashtable_del_fn value_del_fn);

void zc_hashtable_del(zc_hashtable_t * a_table);

void zc_hashtable_clean(zc_hashtable_t * a_table);

int zc_hashtable_put(zc_hashtable_t * a_table, void *a_key, void *a_value);

zc_hashtable_entry_t *zc_hashtable_get_entry(zc_hashtable_t * a_table, void *a_key);

void *zc_hashtable_get(zc_hashtable_t * a_table, void *a_key);

void zc_hashtable_remove(zc_hashtable_t * a_table, void *a_key);

zc_hashtable_entry_t *zc_hashtable_begin(zc_hashtable_t * a_table);
zc_hashtable_entry_t *zc_hashtable_next(zc_hashtable_t * a_table, zc_hashtable_entry_t * a_entry);

#define zc_hashtable_foreach(a_table, a_entry) \
for(a_entry = zc_hashtable_begin(a_table); a_entry; a_entry = zc_hashtable_next(a_table, a_entry))

unsigned int zc_hashtable_str_hash(void *str);
int zc_hashtable_str_equal(void *key1, void *key2);

unsigned int zc_hashtable_tid_hash(void *ptid);
int zc_hashtable_tid_equal(void *ptid1, void *ptid2);

#endif
