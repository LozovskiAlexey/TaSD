#include "mylib.h"
#include "structures.h"
#include "functions.h"

/*
В этом файле расположены функции для чтения файла в базу данных
*/

int open_file(int *n, FILE **file)
{
	char *file_name = NULL;     //пользователь вводит название файла
	if (check_struct_data(&file_name, 0) == INV_INPUT)
		return BAD_DATA;
	
	(*file) = fopen(file_name, "r"); //Файл открывается
	if (!(*file))
		return BAD_DATA;
	
	if (fscanf(*file, "%d\n", n) == 0) //считывается число элементов
		return BAD_DATA;
	
	if ((*n) == 0)
		return BAD_DATA;
	
	printf(" Чудесно! Вы прекрасно справились с заданием.\n");
	return SUCCESS;
}

int fill_struct(theater_t *theater, key_t *key, FILE *file)
{
	theater_t theater_copy = {NULL, NULL, NULL, NULL, NULL};
	
	if (check_file_data(&(theater_copy.theater), 0, file) == BAD_DATA)
		return BAD_DATA;

	if (check_file_data(&(theater_copy.spectacle), 0, file) == BAD_DATA)
		return BAD_DATA;	

	if (check_file_data(&(theater_copy.producer), 0, file) == BAD_DATA)
		return BAD_DATA;

	if (check_file_data(&(theater_copy.min_price), 1, file) == BAD_DATA)
		return BAD_DATA;
	
	(*key).data = atoi(theater_copy.min_price);
	
	if (check_file_data(&(theater_copy.max_price), 1, file) == BAD_DATA)
		return BAD_DATA;

	if (fscanf(file, "%d\n", &theater_copy.variable) != 1)
		return BAD_DATA;
	
	if (read_struct_type(&theater_copy, file) == BAD_DATA)
		return BAD_DATA;

	*theater = theater_copy;
	
	return SUCCESS;
}

int read_struct_type(theater_t *theater, FILE *file)
{
	int result;
	spectacle_t spectacle;
	child_t child = { NULL, 0 };
	adult_t adult = { 0 };
	musical_t music = { NULL, NULL, NULL, NULL };
	
	switch ((*theater).variable)
	{
		case 1:
			result = fill_child(&child, file);
			if (result != BAD_DATA)
				spectacle.child = child;
			break;
		case 2:
			result = fill_adult(&adult, file);
			if (result != BAD_DATA)
				spectacle.adult = adult;
			break;
		case 3:
			result = fill_music(&music, file);
			if (result != BAD_DATA)
				spectacle.music = music;
			break;
	}
	if (result !=  BAD_DATA)
		theater->type = spectacle;
	else 
		return BAD_DATA;
	return result;
}

int fill_music(musical_t *music, FILE *file)
{
	musical_t music_copy = { NULL, NULL, NULL, NULL };

	if (check_file_data(&(music_copy.composer), 0, file) == BAD_DATA)
		return BAD_DATA;

	if (check_file_data(&(music_copy.country), 0, file) == BAD_DATA)
		return BAD_DATA;

	if (check_file_data(&(music_copy.min_age), 1, file) == BAD_DATA)
		return BAD_DATA;

	if (check_file_data(&(music_copy.length), 1, file) == BAD_DATA)
		return BAD_DATA;
	
	*music = music_copy;
	return SUCCESS;
}

int fill_adult(adult_t *adult, FILE *file)
{
	if (fscanf(file, "%d\n", &(adult->type)) != 1)
		return BAD_DATA;
	return SUCCESS;
}

int fill_child(child_t *child, FILE *file)
{
	child_t child_copy = { NULL, 0 }; //инициализация невариантных элементов
	if (fscanf(file, "%d\n", &child_copy.genre) != 1)
		return BAD_DATA;
	
	if (read_child_type(&child_copy, file) == BAD_DATA)
		return BAD_DATA;
	
	if (child_copy.genre != 3)
	{
		if (check_file_data(&(child_copy.age), 1, file) == BAD_DATA)
			return BAD_DATA;
	}
	*child = child_copy;
	
	return SUCCESS;
}

int read_child_type(child_t *child, FILE *file)
{
	int result;
	musical_t music = { NULL, NULL, NULL, NULL };
	
	switch ((*child).genre)
	{
		case 1:
			child->type.type = 1;
			break;
		case 2:
			child->type.type = 2;
			break;
		case 3:
			result = fill_music(&music, file);
			if (result == BAD_DATA)
				return BAD_DATA;
			else 
			{
				child->type.type = 3;
				child->type.music = music;
			}
			break;
	}
	return SUCCESS;
}

int check_file_data(char **str, int flag, FILE *file)
{	
	size_t n = 0;
	size_t get_result; 
	
	get_result = my_getline(str, &n, file); //считывание строки

	if ((get_result == 0) || (get_result == BAD_DATA))
		return BAD_DATA;
	
	//проверка на содержание строки
	if (flag == 1)
		if (iSdigit(*str, n) == INV_INPUT) 
			return BAD_DATA;
		
	return SUCCESS;
}