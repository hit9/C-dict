#include "dict.h"
#include <stdlib.h>
#include <string.h>

/*
 * prime array
 */
static int prime_array[] = {
	7, 
	17,             
	37,            
	79,            
	163,           
	331,           
	673,           
	1361,          
	2729,          
	5471,          
	10949,         
	21911,         
	43853,         
	87719,         
	175447,        
	350899,        
	701819,        
	1403641,       
	2807303,       
	5614657,       
	11229331,      
	22458671,      
	44917381,      
	89834777,      
	179669557,     
	359339171,     
	718678369,     
	1437356741,    
	2147483647     
};      

/* the max of size_pos is 28 */

#define SIZE_POS_MAX 28

/*
 * bkdr hash function
 */
static unsigned int BKDRHash(char *str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

/*
 * get index(position) by key
 */
static int get_index(dict_t *dict, char *key)
{
	return BKDRHash(key)%(prime_array[dict->size_pos]); 
}

/*
 * init dict's pointer
 */
int dict_init(dict_t *dict)
{
	dict->size_pos = 0; 
	dict->ele_num = 0; 
	dict->bucket = (bucket_t **)calloc(prime_array[0], sizeof(bucket_t *)); //each list's head node pointer set to 0

	if (dict->bucket == NULL) return 0; 
	return 1; 
}

/*
 * get dict's size
 */
int dict_size(dict_t *dict)
{
	return dict->ele_num; 
}

/*
 * resize the dict if ele_num == dict's size.we will reinsert all nodes again.but we don't need to check the keys
 */

static int dict_resize(dict_t *dict)
{
	if (dict->size_pos - SIZE_POS_MAX >= 0) return 0; //top the max, can't resize

	//record olds
	int old_size = prime_array[dict->size_pos]; //record old size
	bucket_t **old_bucket = dict->bucket; //record the old bucket 
	
	//resize 
	dict->size_pos += 1; 
	dict->bucket = (bucket_t **)calloc(prime_array[dict->size_pos], sizeof(bucket_t *)); //new bigger 0 space for dict->bucket
	
	/* --- begin reinsert .. --- */
	int i; //iterator for old_bucket[]

	bucket_t *t, *p, *q, *node; 
	int index; 

	for (i = 0; i < old_size; i++){
		for (t = old_bucket[i]; t; q = t, t = t->next, free(q)){ //free the old node the same time
			//new a node
			node = (bucket_t *)malloc(sizeof(bucket_t)); 
			node->key = t->key; 
			node->value = t->value; 
			
			index = get_index(dict, node->key); 
			p = (dict->bucket)[index];  //get new dict->bucket[index] first node pointer
			
			//append node to the list
			if (!p) (dict->bucket[index]) = node; 
			else{
				for (; p->next; p = p->next); 
				p->next = node; 
			}
		}
	}
	return 1; //success
}

/*
 * add a pair of 'key => value' to dict
 */
int dict_add(dict_t *dict, char *key, void *value)
{
	//if need resize
	if (prime_array[dict->size_pos] - dict->ele_num <1) dict_resize(dict); 
	//get index by hash function
	int index = get_index(dict, key); 

	//get its bucket's head node's pointer
	bucket_t *first = (dict->bucket)[index], *temp; 

	//init a new node
	bucket_t *node = (bucket_t *)malloc(sizeof(bucket_t)); 
	node->key = key; 
	node->value = value; 
	node->next = NULL; 

	/* -- append the new node to its bucket(list) if this key is a new one -- */
	
	//if first is NULL, set node the first 
	if (!first) (dict->bucket)[index] = node; 
	else{
		for (temp = first; temp->next; temp = temp->next)
			if (strcmp(temp->key, key) == 0) return 0; //key already exists, failed
		if (strcmp(temp->key, key) == 0) return 0; //cmp again with the last node temp's key
		temp->next = node; //append it after the last
	}
	
	//ele_num self plus 1
	dict->ele_num += 1; 
	
	return 1; //success
}

/*
 * lookup
 */
int dict_lookup(dict_t *dict, char *key, void **value)
{
	int index = get_index(dict, key); 
	bucket_t *first = (dict->bucket)[index]; 
	
	for (; first; first = first->next){ //first as a iterator pointer, scan the list begin from dict->bucket[index]
		if (strcmp(key, first->key) == 0){
			*value = first->value; 
			return 1; //success 
		}
	}
	return 0; //failed
}
