C-dict
------

[![Build Status](https://travis-ci.org/hit9/C-dict.png?branch=master)](https://travis-ci.org/hit9/C-dict)

####API
```c
int dict_init(dict_t *); 

int dict_size(dict_t *); 

void dict_set(dict_t *, char *, void *); 

int dict_get(dict_t *, char *, void **); 

int dict_del(dict_t *, char *); 

void dict_keys(dict_t *, char **); 

void dict_reset(dict_t *); 

void dict_destory(dict_t *); 

int dict_iter(dict_t *, char **, void **); 
```

####Test
```shell
cd test
make test
```

####Data Type
```
dict_t;
```

####Example
```c
	dict_t *d = (dict_t *)malloc(sizeof(dict_t));
	char *var; 
	
	dict_init(d); 
	
	dict_set(d, "key1", "var1"); 
	dict_set(d, "key2", "var2"); 
	dict_set(d, "key3", "var3"); 
	
	dict_get(d, "key1", (void **)&var); 
	printf("key1=>%s\n", var);
	
	printf("dict size:%d\n", dict_size(d));
	
	if (1 == dict_del(d, "key3"))
		printf("del key3 done\n");
	
	char **ks = (char **)malloc(dict_size(d)*sizeof(char*)); 
	int i; 
	dict_keys(d, ks); 
	for(i = 0; i < dict_size(d); i++)
		printf("%s ",*(ks+i) );
	printf("\n");
	
	char *k, *v; 
	while(dict_iter(d, &k, (void **)&v))
		printf("%s = >%s\n", k, v);
	
	dict_reset(d); 
	
	dict_destory(d); 
	free(d); 
```

#### TODO

```
dict_merge()

```
