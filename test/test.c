/*
 * tests for dict.h  = & dict.c
 * cases:
 *  * dict_init
 *  * dict_set
 *  * dict_size
 *  * dict_get
 *  * dict_del
 *  * dict_keys
 *  * dict_resize
 *  * dict_reset
 *  * dict_destory
 *  * dict_iter
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mcheck.h>
#include "dict.h"

#define TEST(CASE) printf(" >> TEST CASE : " CASE )
#define PASS() printf("\t\t[PASSED]\n")

int main(int argc, const char *argv[])
{
	mtrace(); 
	dict_t *d = (dict_t *)malloc(sizeof(dict_t)); 
	
	TEST("dict_init()"); 
	assert(1 == dict_init(d)); 
	assert(0 == d->ele_num); 
	assert(0 == d->size_pos); 
	PASS(); 
	
	TEST("dict_set()"); 
	dict_set(d, "key", "var"); 
	assert(1 == dict_size(d)); 
	dict_set(d, "key", "var_n"); 
	assert(1 == dict_size(d)); 
	dict_set(d, "0", "0var"); 
	assert(2 == dict_size(d)); 
	dict_set(d, "7", "7var"); 
	assert(3 == dict_size(d)); 
	PASS(); 
	
	TEST("dict_size()"); 
	assert(3 == dict_size(d)); 
	PASS(); 
	
	TEST("dict_get()"); 
	char *var; 
	assert(1 == dict_get(d, "key", (void **)&var)); 
	assert(strcmp(var, "var_n") == 0); 
	assert(0 == dict_get(d, "keys", (void **)&var)); 
	PASS(); 
	
	TEST("dict_del()"); 
	assert(1 == dict_del(d, "key")); 
	assert(0 == dict_get(d, "key", (void **)&var)); 
	assert(2 == dict_size(d)); 
	PASS(); 
	
	TEST("dict_keys()"); 
	char **s = (char **)calloc(10, sizeof(char *)); 
	dict_keys(d, s); 
	assert(s[2] == NULL); 
	assert(strcmp(s[1], "0") == 0 || strcmp(s[1], "7") == 0); 
	assert(strcmp(s[0], "0") == 0 || strcmp(s[1], "0") == 0); 
	assert(strcmp(s[1], s[0]) != 0); 
	PASS(); 
	free(s); 
	
	TEST("dict_reset()"); 
	dict_reset(d); 
	assert(0 == d->ele_num); 
	assert(0 == d->size_pos); 
	assert(NULL == (d->bucket)[0]); 
	assert(NULL == (d->bucket)[1]); 
	assert(NULL == (d->bucket)[2]); 
	assert(NULL == (d->bucket)[3]); 
	assert(NULL == (d->bucket)[4]); 
	assert(NULL == (d->bucket)[5]); 
	assert(NULL == (d->bucket)[6]); 
	PASS(); 
	
	TEST("dict_resize()"); 
	/* 7 times set */
	dict_set(d, "1", "hello1"); 
	dict_set(d, "2", "hello2"); 
	dict_set(d, "3", "hello3"); 
	dict_set(d, "4", "hello4"); 
	dict_set(d, "5", "hello5"); 
	dict_set(d, "6", "hello6"); 
	dict_set(d, "7", "hello7"); 
	assert(1 == d->size_pos); 
	/* 17 times */
	dict_set(d, "8", "hello8"); 
	dict_set(d, "9", "hello9"); 
	dict_set(d, "10", "hello10"); 
	dict_set(d, "11", "hello11"); 
	dict_set(d, "12", "hello12"); 
	dict_set(d, "13", "hello13"); 
	dict_set(d, "14", "hello14"); 
	dict_set(d, "15", "hello15"); 
	dict_set(d, "16", "hello16"); 
	dict_set(d, "17", "hello17"); 
	assert(2 == d->size_pos); 
	PASS(); 

	TEST("dict_iter()"); 
	char *k = NULL, *v = NULL; 
	int i = 0; 
	printf("\n\tprint all k =>v pairs:\n");
	while(dict_iter(d, &k, (void **)&v)){
		printf("\t'%s'\t=>\t'%s'\n", k, v);
		i++; 
	}
	printf("print over, total %d pair", i);
	assert(i == dict_size(d)); 
	PASS(); 
	
	TEST("dict_destory()"); 
	dict_destory(d); 
	assert(0 == dict_size(d)); 
	assert(0 == d->size_pos); 
	assert(NULL == d->bucket); 
	PASS(); 
	
	free(d); 
	return 0;
}
