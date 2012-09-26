#ifndef DICT_H
#define DICT_H 1

typedef struct _node {
	char *key; 
	void *value; 
	struct _node *next; 
} bucket_t; 

typedef struct {
	int size_pos; //size_pos in prime_array, the size of dict = prime_array[size_pos]
	int ele_num; //ele number in dict
	bucket_t **bucket; 
} dict_t; 

/* API */

int dict_init(dict_t *); 

int dict_size(dict_t *); 

int dict_add(dict_t *, char *, void *); 

int dict_lookup(dict_t *, char *, void **); 
#endif 
