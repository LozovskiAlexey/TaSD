#ifndef STRUCTURES_H
#define STRUCTURES_H

//структура тип: спектакль для взрослых
//Жанр
//1 - пьеса
//2 - драма 
//3 - комедия
typedef struct adults
{
	int type; //Выбор жанра спектаря
} adult_t;              //Новый тип

//структура тип: музыкальный спектакль 
typedef struct musical
{
	char *composer;
	char *country;
	char *min_age;
	char *length;
} musical_t;              //Новый тип

//структура выбор типа детского спектакля
//type: 1 - сказка
//      2 - пьеса
typedef union type
{
	int type;
	musical_t music;
} type_t;

//структура тип: спектакль для детей
//Возраст заполняется в случае, если 
//genre не указывает на music, внутри music возраст
//записывается отдельно
//genre - 1 - сказка 
//        2 - пьеса
//        3 - музыкальный
//с помощью genre программа определяет какое поле выводить 
//пользователю
typedef struct children
{
	char *age;
	int genre; //понадобится в заполненнии
	type_t type;
} child_t;              //Новый тип

//вариативная часть, опредяет тип спектакля
typedef union sp_type
{
	child_t child;
	adult_t adult;
	musical_t music;
} spectacle_t;              //Новый тип

//Основная структура. Заполнение невариативных полей.
//variable определяет какое из полей нужно показать пользователю
//1 - child детский спектакль
//2 - adult взрослый спектакль
//3 - music музыкальный
typedef struct repertoire 
{
	char *theater;
    char *spectacle;
    char *producer;
    char *min_price;
    char *max_price;
	int variable;
	spectacle_t type;
} theater_t;              //Новый тип

typedef struct key
{
	int source_index;
	int data;
}key_t;

#endif