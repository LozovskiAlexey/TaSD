#include "mylib.h"
#include "structures.h"
#include "functions.h"

//сделать функцию для ввода в консоль СДЕЛАНО
//подумать как объединить функции меню в одну-две и сделать универсальными. СДЕЛАНО

//Написать функцию для вывода структур в консоли
//Считывание файла
//Распределить функции по файлам, в зависимости от назначения СДЕЛАНО

//Главная функция, вызывает все меню по очереди
//Вызывает основные функции программы
int main_menu()
{	
	int operation_result;
	int result = 1; 
	int n; 
	theater_t *theater = NULL;
	key_t *keys = NULL;
	FILE *file = NULL;
	
	while (result != 0)
	{ 
		result = choose_menu(1); //показывает меню с выбором файла
		result = choose_source_menu(result, &n, &file); //выбор файла
		
		if ((result == INV_INPUT) || (result == BAD_DATA))
			show_error(result);
		if (result == BAD_BEHAVE)
			return SUCCESS;
	}
	int element = 0;	
	if (n == BASE_SIZE)
		theater = make_base(n, &keys);
	else
	{
		theater = make_base(n + 25, &keys);
		element = n;
		for (element = 0; element < n; element++)
		{
			result = fill_struct(&theater[element], &keys[element], file);
			keys[element].source_index = element;
		}
	}
	
	while (1)
	{	
		result = show_menu();
		
		switch (result)
		{
			case ADD:
				operation_result = addition(&theater[element], &keys[element]);
				if (operation_result)
					show_error(operation_result);
				else
				{
					keys[element].source_index = element;
					element++;
				}
				break;
				
			case SHOW:
				if (element == 0)
					operation_result = EMPTY_BASE;
				else 
					operation_result = show(theater, element);
				show_error(operation_result);
				break;
				
			case DELETE:
				if (element == 0)
					operation_result = EMPTY_BASE;
				else 
				{
					operation_result = delete_el(&theater, &element);
					if (!operation_result)
						fill_keys(theater, &keys, element);
				}
				show_error(operation_result);
				break;
			
			case SHOW_TABLE:
				if (element == 0)
				{
					operation_result = EMPTY_BASE;
					show_error(operation_result);
					break;
				}
				for(int i = 0; i < element; i++)
				{
					show_title(3, i + 1);
					show_base(theater[i]);
				}
				break;
			case SHOW_KEYS:
				if (element == 0)
				{
					operation_result = EMPTY_BASE;
					show_error(operation_result);
					break;
				}
				key_qsort(keys, element);
				show_keys(keys, element);
				break;
			
			case SHOW_SORTED:
				if (element == 0)
				{
					operation_result = EMPTY_BASE;
					show_error(operation_result);
					break;
				}
				base_qsort(theater, element);
				fill_keys(theater, &keys, element);
				for(int i = 0; i < element; i++)
				{
					show_title(3, i + 1);
					show_base(theater[i]);
				}
				break;
				
			case SHOW_KEY_SORTED:
				if (element != 0)
					sort_by_key(theater, keys, element);
				else
				{
					operation_result = EMPTY_BASE;
					show_error(operation_result);
				}
				break;
				
			case SHOW_TIME:
				if (element != 0)
				{
					show_title(7, 0);
					time_cmp(theater, keys, element);
					sort_speed(keys, element);
				}
				else 
				{
					operation_result = EMPTY_BASE;
					show_error(operation_result);
				}
				break;
				
			case INV_INPUT:
				show_error(result);
				break;
			
			case EXIT:
				if (element == 0)
				{
					operation_result = EMPTY_BASE;
					show_error(result);
					break;
				}
				finish_job(theater, element);
				show_error(result);
				return 0;
		}
	}	
	return 0;
}

//В зависимости от введенного пользователем
//значения открывает файл и считывает из него 
//структуры, создает новую базу данных или выходит
//из программы.
int choose_source_menu(int result, int *n, FILE **file)
{
	switch (result)
	{
		case 1:
			show_title(4, 0);
			result = open_file(n, file);
			break;
				
		case 2:
			(*n) = BASE_SIZE;
			result = 0;
			break;
			
		case 3:
			result = BAD_BEHAVE;
			show_error(result);
			break;
		
		case -2:
			show_error(result);
			break;
	}
	return result;
}

//Проверяет корректность ответа пользователя
//Нв вход подается количество вариантов ответа
int check_answer(int n)
{
	int result, a;
	
	result = scanf("%d", &a);
	if (!result)
	{
		rewind(stdin);
		return INV_INPUT;
	}
	else if (a < 1 || a > n)
		return INV_INPUT;
	return a;
}

//создание массива структур
theater_t *make_base(int size, key_t **keys)
{
	theater_t *theater = NULL;
	
	theater = (theater_t*)realloc(theater, size * sizeof(theater_t));
	if (!theater)
		return NULL;
	(*keys) = (key_t *)realloc((*keys), size * sizeof(key_t));
	if (!(*keys))
		return NULL;
	
	return (theater);
}

//получает на вход строку из потока stdin, считывает ее и 
//посимвольно проверяет до \n, в случае если флаг 1
//проверит содержит ли строка символы кроме цифр, если да
//вернется ошибка, иначе - SUCCESS
int check_struct_data(char **str, int flag)
{
	size_t n = 0;
	size_t get_result; 
	
	fflush(stdin);
	get_result = my_getline(str, &n, stdin); //считывание строки
	if ((get_result == 0) || (get_result == INV_INPUT))
		return INV_INPUT;
	
	//проверка на содержание строки
	if (flag == 1)
		if (iSdigit(*str, n) == INV_INPUT) 
			return INV_INPUT;
		
	return SUCCESS;
}

//Считывает из потока stdin введенное пользователем значение.
//Вользователь вводит значение до символа \n.
size_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	if (!stream || !n || !lineptr)
		return INV_INPUT;
	;
	char *result = NULL;
	
	(*lineptr) = realloc(*lineptr, BUFF_SIZE);  //выделяет память под строку, которую ввел пользователь
	if (!(*lineptr))
		return INV_INPUT;

	result = fgets(*lineptr, BUFF_SIZE, stream); //считывает значения в lineptr
	char *pos = *lineptr;
	size_t size = 0; //действительный размер буфера
	int stop = 0; 
	int i = 1; //во сколько раз увеличить память

	//Посимвольно проверяет считанные данные пока не встретится \0 или \n 
	while (result)
	{
		for (int j = 0; j < BUFF_SIZE && *pos != '\0'; j++)
		{
			if ((*pos) == '\n') 
			{
				stop = 1;
				break;
			}
			pos++;
			size++;
		}
		if (stop)
			break;
	
		(*lineptr) = realloc(*lineptr, BUFF_SIZE * (++i));
		if (!(*lineptr))
			return INV_INPUT;
		result = fgets(pos, BUFF_SIZE, stream);
	}
	
	//проверка на пустую строку
	if (size == 0)
	{
		free(*lineptr);
		(*lineptr) = NULL;
		*n = size;
		size = INV_INPUT;
	}
	//перевыделяет память под действительное число считанных элементов
	else 
	{
		(*lineptr) = realloc(*lineptr, size + 1);
		(*lineptr)[size] = '\0'; 
		*n = size + 1;
	}
	return size; //Возвращает число считанных символов + \0
}

//Проверка строки, если в строке есть символы кроме цифр, вернется ERROR
//Иначе SUCCESS
int iSdigit(char *lineptr, size_t size)
{
	for (int i = 0; i < size - 1; i++)
		if (lineptr[i] < '0' || lineptr[i] > '9')
			return INV_INPUT;
	return SUCCESS;
}
