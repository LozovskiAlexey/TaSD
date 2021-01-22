#include "mylib.h"
#include "structures.h"
#include "functions.h"

/*
ЗАДАНИЕ: Вывести список всех музыкальных спектаклей для детей указанного
возраста с продолжительностью меньше указанной. 

В этом файле расположены функции, которые показывают введенную пользователем
и считанную из файла базу данных. 
База данных может быть выведена: 
1 - По заданию.
2 - Вся база.
3 - Упорядоченая.
*/

int show(theater_t *theater, int n)
{
	int flag = 0; //определит, если хоть одна структура будет выведена на экран. 
	//иначе сообщение об ошибке
	char *age = NULL;
	char *length = NULL;
	
	printf(" 1. Возраст:           ");
	if (check_struct_data(&age, 1) == INV_INPUT)
		return INV_INPUT;
	
	printf(" 2. Продолжительность: ");
	if (check_struct_data(&length, 1) == INV_INPUT)
		return INV_INPUT;
	
	show_title(2, 0);
	show_text(1);
	
	int given_age = atoi(age);
	int given_length = atoi(length);
	int number = 1; //индексы выводимых на экран театров

	for (int i = 0; i < n; i++)
	{
		if (find_base(theater[i], given_age, given_length) == SUCCESS)
		{
			show_title(3, number);
			show_base(theater[i]);
			number++;
			flag = 1;
		}
	}
	int result = flag == 0 ? NO_MATCHES : SUCCESS;
	return result;
}

int find_base(theater_t theater, int given_age, int given_length)
{
	if (theater.variable == 1)
		if (theater.type.child.genre == 3)
			if (atoi(theater.type.child.type.music.min_age) == given_age) //исправить 
				if (atoi(theater.type.child.type.music.length) < given_length) //исправить
					return SUCCESS;
	return ERROR;
}

void show_base(theater_t theater)
{
	printf("\n 1. Название театра:           %s"
		   "\n 2. Название спектакля:        %s"
		   "\n 3. Фамилия режиссера:         %s"
		   "\n 4. Стоимость:                 %s...%s"
		   "\n ────────────────────────────────────────────────────────",
		   theater.theater, theater.spectacle, theater.producer,
		   theater.min_price, theater.max_price);
		   
	int flag_type = theater.variable;
	switch (flag_type)
	{
		case 1:
			printf("\n 5. Тип спектакля:             Детский");
			show_childtype(theater.type.child);
			break;
		case 2:
			printf("\n 5. Тип спектакля:             Взрослый");
			show_adulttype(theater.type.adult.type);
			break;
		case 3:
			printf("\n 5. Тип спектакля:             Музыкальный");
			show_musictype(theater.type.music);
			break;
	}
}

void show_childtype(child_t child)
{
	int flag = child.genre;
	char *genre;
	
	printf("\n ────────────────────────────────────────────────────────");
	switch (flag)
	{
		case 1:
			genre = "Сказка";
			break;
		case 2:
			genre = "Пьеса";
			break;
		case 3:
			genre = "Музыкальный";
			break;
	}
	printf("\n 1. Жанр:                      %s\n", genre);
	
	if (flag == 3)
		show_musictype(child.type.music);
	else 
		printf("\n 2. Допустимый возраст:        %s\n", child.age);
}

void show_adulttype(int type)
{
	char *genre;
	
	printf("\n ────────────────────────────────────────────────────────");
	switch (type)
	{
		case 1:
			genre = "Пьеса";
			break;
		case 2:
			genre = "Драма";
			break;
		case 3:
			genre = "Комедия";
			break;
	}
	printf("\n 1. Жанр:                      %s\n", genre);
}

void show_musictype(musical_t music)
{
	printf("\n ────────────────────────────────────────────────────────");
	printf("\n 1. Композитор:                %s"
		   "\n 2. Страна:                    %s"
		   "\n 3. Допустимый возраст:        %s"
		   "\n 4. Продолжительность:         %s\n",
		   music.composer, music.country,
		   music.min_age, music.length);
}
