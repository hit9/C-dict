####API
```c
int dict_init(dict_t *); 

int dict_size(dict_t *); 

void dict_set(dict_t *, char *, void *); 

int dict_get(dict_t *, char *, void **); 

int dict_del(dict_t *, char *); 

void dict_keys(dict_t *, char **); 

```
