#include "mylib.h"
#include "structures.h"
#include "functions.h"

int delete_el(theater_t **theater, int *size)
{
	show_title(5, 0);
	
	int result; 
	int del_flag = 0;
	char *sp_name = NULL;
	
	result = check_struct_data(&(sp_name), 0);
	while (result != SUCCESS)
	{
		printf(" Некорректный ввод. Попытайтесь еще!\n"
			   " Введите название спектакля: ");
		result = check_struct_data(&(sp_name), 0);
	}
	
	for (int i  = 0; i < (*size); i++)
	{
		if (!strcmp((*theater)[i].spectacle, sp_name))
		{
			for (int j = i; j < (*size) - 1; j++)
				(*theater)[j] = (*theater)[j + 1];

			del_flag = 1;
			
//			(*theater) = realloc((*theater), (*size) - 1);
					
			(*size)--;
			break;
		}
	}
	if (del_flag)
		return SUCCESS;
	else 
		return NO_MATCHES;
}

void show_keys(key_t *keys, int size)
{
	show_title(6, 0);
	for (int i = 0; i < size; i++)
		printf("        %-15d   %-15d     %-15d\n",
		       i+1, keys[i].source_index, keys[i].data);
}

void fill_keys(theater_t *theater, key_t **key, int size)
{
	for (int i = 0; i < size; i++)
	{
		(*key)[i].source_index = i;
		(*key)[i].data = atoi(theater[i].min_price);
	}
//	(*key) = realloc((*key), size);
}

int compare_key(const void *key1, const void *key2)  
{
  return (((const key_t*)key1)->data) - (((const key_t*)key2)->data);  
}

int compare_base(const void *price1, const void *price2)
{
	int int_pr1 = atoi(((theater_t*)price1)->min_price);
	int int_pr2= atoi(((theater_t*)price2)->min_price);
	
	return int_pr1 - int_pr2;
}

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void*, const void*))
{
	unsigned i, j;           
	int border = number - 1; 
	int sort_border = border; 
	int compare_result = 0;

	
	char *array = (char*)first;
	
	for (i = 0; i < number; i++)
	{
		for (j = 0; j < border; j++)
		{
			compare_result = comparator((void*)(array + j * size), (void*)(array + (j + 1) * size));
			if (compare_result > 0)
			{	
				swap((void*)(array + j * size), (void*)(array + (j + 1) * size), size);
				sort_border = j;
			}
		}
		if (sort_border != border) 
			border = sort_border;
	}
}

void key_mysort(key_t *keys, int size)
{
	mysort(keys, size, sizeof(key_t), compare_key);
}

void key_qsort(key_t *keys, int size)
{
	qsort(keys, size, sizeof(key_t), compare_key);
}

void base_qsort(theater_t *theater, int size)
{
	qsort(theater, size, sizeof(theater_t), compare_base);
}

void base_mysort(theater_t *theater, int size)
{
	mysort(theater, size, sizeof(theater_t), compare_base);
}

void sort_by_key(theater_t* theater, key_t *key, int size)
{
	key_qsort(key, size);
	for (int i = 0; i < size; i++)
	{
		show_title(3, i + 1);
		show_base(theater[key[i].source_index]);
	}
}

void swap(void *a, void *b, size_t size)
{
	char tmp = 0;
	
	for (int i = 0; i < size; i++)
	{
		tmp = *((char*)a + i);
		*((char*)a + i) = *((char*)b + i);
		*((char*)b + i) = tmp;
	}
}

void time_cmp(theater_t *theater, key_t *keys, int size)
{
	theater_t *theater_copy1 = NULL; 
	key_t *key_copy1 = NULL;
	
	unsigned long long tb, te, tk, ts;
	
	theater_copy1 = (theater_t *)malloc(size * sizeof(theater_t));
	memcpy(theater_copy1, theater, size * sizeof(theater_t));
	
	key_copy1 = (key_t *)malloc(size * sizeof(key_t));
	memcpy(key_copy1, keys, size * sizeof(key_t));
	
	tb = tick();
	key_qsort(key_copy1, size);
	te = tick();
	tk = te - tb;
	int mem_used = (sizeof(theater_t) + sizeof(key_t)) * size;
	
	printf(" Сортировка по ключам:              %d\n", (int)(tk));
	printf(" Использовано памяти:               %d\n\n", mem_used);
	
	tb = tick();
	base_qsort(theater_copy1, size);
	te = tick();
	ts = te - tb;
	mem_used = sizeof(theater_t) * size;	

	printf(" Сортировка исходной таблицы:       %d\n", (int)(ts));
	printf(" Использовано памяти:               %d\n\n", mem_used);
	
	double res = (double)tk / (double)ts;
	printf(" Процентное соотношение:            %.3f\n\n", res);
	
	free(theater_copy1);
	free(key_copy1);
}

void sort_speed(key_t *keys, int size)
{
	key_t *key_copy1 = NULL;
	key_t *key_copy2 = NULL;
	
	key_copy1 = (key_t *)malloc(size * sizeof(key_t));
	memcpy(key_copy1, keys, size * sizeof(key_t));
	
	key_copy2 = (key_t *)malloc(size * sizeof(key_t));
	memcpy(key_copy2, keys, size * sizeof(key_t));
	
	unsigned long long tb, te, tk, ts;
	
	tb = tick();
	key_qsort(key_copy1, size);
	te = tick();
	ts = te - tb;
	
	printf(" Сортирова ключей qsort:            %d\n", (int)ts);
	
	tb = tick();
	key_mysort(key_copy2, size);
	te = tick();
	tk = te - tb;
	
	printf(" Сортирова ключей buble_sort:       %d\n", (int)tk);
	free(key_copy1);
	free(key_copy2);
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}