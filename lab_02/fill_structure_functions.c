#include "mylib.h"
#include "structures.h"
#include "functions.h"

/*
В этом файле находятся функции, с помощью которых заполняется 
одна структура с консоли. 
*/

//добавление структуры
//Заполнение по полям
int addition(theater_t *theater, key_t *key)
{
	theater_t theater_copy = {NULL, NULL, NULL, NULL, NULL};
	
	printf("\n Введите: \n");
	
	printf(" 1. Название театра:               ");	
	if (check_struct_data(&(theater_copy.theater), 0) == INV_INPUT)
		return INV_INPUT;
	
	printf(" 2. Название спектакля:            ");
	if (check_struct_data(&(theater_copy.spectacle), 0) == INV_INPUT)
		return INV_INPUT;
	
	printf(" 3. Фамилию режиссера:             ");
	if (check_struct_data(&(theater_copy.producer), 0) == INV_INPUT)
		return INV_INPUT;
	
	printf(" 4. Минимальную стоимость:         ");
	if (check_struct_data(&(theater_copy.min_price), 1) == INV_INPUT)
		return INV_INPUT;
	
	(*key).data = atoi(theater_copy.min_price);
	
	printf(" 5. Максимальную стоимость:        ");
	if (check_struct_data(&(theater_copy.max_price), 1) == INV_INPUT)
		return INV_INPUT;
	
	if (atoi(theater_copy.min_price) >= atoi(theater_copy.max_price))
		return INV_INPUT;
	
	if (choose_type_menu(choose_menu(2), &theater_copy) == INV_INPUT) //дописать функции children adults music
		return INV_INPUT;
		
	*theater = theater_copy;
	return SUCCESS;
}

//выбирает тип спектакля, в зависимости от флага выберет - 
//детский, мкзыкальный, взрослый и заполнит его, в случае ошибки вернет error;
int choose_type_menu(int type, theater_t *theater)
{
	int result;
	spectacle_t spectacle;
	child_t child = { NULL, 0 };
	musical_t music = { NULL, NULL, NULL, NULL };
	
	switch (type)
	{
		//Детский
		case 1: 			
			result = fill_children_struct(&child);
			
			if (result != INV_INPUT)
			{
				spectacle.child = child;
				theater->variable = 1;
			}				
			break;
		//Взрослый
		case 2: 
			result = choose_menu(4);
			if (result != INV_INPUT)
			{
				spectacle.adult.type = result;
				theater->variable = 2;
			}
			break;
		// Музыкальный	
		case 3: 
			show_title(1, 0);
			result = fill_music_struct(&music);
			if (result != INV_INPUT)
			{
				spectacle.music = music;
				theater->variable = 3;
			}

			break;
	}
	if (result != INV_INPUT)
		theater->type = spectacle;
	else 
		return INV_INPUT;
	return result;
}

//заполнения поля child целиком
int fill_children_struct(child_t *child)
{
	child_t child_copy = { NULL, 0 }; //инициализация невариантных элементов
	int result; 
	
	result = choose_menu(3);
		if (result == INV_INPUT)
			return INV_INPUT;
		
	if (choose_child_type(result, &child_copy) == INV_INPUT) //заполнение одного из полей
		return INV_INPUT;
	
	//если подполе в child не music пользователь отдельно заполняет возраст
	if (child_copy.genre != 3) 
	{
		printf(" Введите допустимый возраст:       ");
		if (check_struct_data(&(child_copy.age), 1) == INV_INPUT)
			return INV_INPUT;
		if (atoi(child_copy.age) >= 18)
			return INV_INPUT;
	}
	*child = child_copy;
	return SUCCESS;
}

//в поле child определяет какое подполе заполнить и заполняет его
//в случае ошибки ввода - вернется код ошибки, иначе 
//код успешной работы.
int choose_child_type(int flag, child_t *child)
{
	int result;
	musical_t music = { NULL, NULL, NULL, NULL };
	switch (flag)
	{
		case 1: 
			child->type.type = flag;
			child->genre = 1;
			break;
		case 2:
			child->type.type = flag;
			child->genre = 2;
			break;
		case 3:
			show_title(1, 0);
			result = fill_music_struct(&music);
			if (result == INV_INPUT)
				return INV_INPUT;
			else
			{
				child->genre = 3;
				child->type.music = music;
			}
			break;
		case INV_INPUT:
			return INV_INPUT;
	}
	return SUCCESS;		
}

//заплняет поле типа "Музыкальный спектакль"
//создает копию поля, с которой работает, после чего
//в случае корректного ввода присваивает music значение 
//заполненного поля, в противном случае вернет ошибку ввода
int fill_music_struct(musical_t *music)
{
	musical_t music_copy = { NULL, NULL, NULL, NULL };
	
	printf(" 1. Фамилию композитора:           ");
	if (check_struct_data(&(music_copy.composer), 0) == INV_INPUT)
		return INV_INPUT;
	
	printf(" 2. Страну:                        ");
	if (check_struct_data(&(music_copy.country), 0) == INV_INPUT)
		return INV_INPUT;
	
	printf(" 3. Минимально-допустимый возраст: ");
	if (check_struct_data(&(music_copy.min_age), 1) == INV_INPUT)
		return INV_INPUT;

	printf(" 4. Продолжительность(в минутах):  ");
	if (check_struct_data(&(music_copy.length), 1) == INV_INPUT)
		return INV_INPUT;
	
	*music = music_copy;
	return SUCCESS;
}