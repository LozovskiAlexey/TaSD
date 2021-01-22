#include "mylib.h"
#include "structures.h"
#include "functions.h"

//Основное меню, работает в цикле
//возвращает введенное пользователем значение
//если ошибка, вернет ERROR
int show_menu()
{
	printf(" ----================================================----\n"
		   "                     --== МЕНЮ ==-- \n"
		   " ----================================================----\n"
		   " 1. Добавить спектакль.\n"
		   " 2. Показать список театров.\n"
		   " 3. Удалить спектакль.\n"
		   " 4. Показать всю таблицу.\n"
		   " 5. Показать ключи.\n"
		   " 6. Отсортировать таблицу.\n"
		   " 7. Отсортировать таблицу ключами.\n"
		   " 8. Показать время работы сортировок.\n"
		   " 9. Отключите меня.\n"
		   " ----================================================----\n"
		   " Чем я могу вам помочь?\n"
		   " Введите номер:                    ");
		   
	int result; 
	result = check_answer(9);
	return result;
}

//В зависимости от флага выводит меню из 3 вариантов
// ответа и проверяет введенные пользователем данные.
//если ошибка - INV_INPUT иначе данные пользователя.
int choose_menu(int flag)
{
	switch (flag)
	{
		case 1:
			printf(" ----================================================----\n"
				   "                --== НАЧАЛО РАБОТЫ ==-- \n"
				   " ----================================================----\n"
				   " Выберите: \n"
			       " 1. Открыть файл\n"
			       " 2. Создать новую базу\n"
			       " 3. Я не желаю работать.\n\n"
			       " Введите номер:                    ");
			break;		
		case 2:
			printf(" ----================================================----\n"
			       "                --== ТИП СПЕКТАКЛЯ ==-- \n"
			       " ----================================================----\n"
				   " Выберите тип: \n"
			       " 1. Детский\n"
			       " 2. Взрослый\n"
			       " 3. Музыкальный\n\n"
			       " Введите номер:                    ");
			break;
		case 3:
			printf(" ----================================================----\n"
			       "                   --== ДЕТСКИЙ ==-- \n"
			       " ----================================================----\n"
				   " Выберите жанр: \n"
			       " 1. Сказка\n"
			       " 2. Пьеса\n"
			       " 3. Музыкальный\n\n"
			       " Введите номер:                    ");
			break;			
		case 4:
			printf(" ----================================================----\n"
				   "                   --== ВЗРОСЛЫЙ ==-- \n"
				   " ----================================================----\n"
				   " Выберите тип:\n"
				   " 1. Пьеса\n"
				   " 2. Драма\n"
				   " 3. Комедия\n\n"
				   " Введите номер:                    ");
			break;	
	}   
	int result; 
	result = check_answer(3);
	return result;
}

//Выводит сообщение в зависимости от полученного значения
int show_error(int flag)
{
	switch (flag)
	{
		case INV_INPUT:
			printf("\n Что-то пошло не так... Плохой ввод.\n");
			break;
			
		case EMPTY_BASE:
			printf("\n База данных пуста.\n");
			break; 
			
		case EXIT:
			printf("\n Благодарю.\n Всего хорошего.\n");
			break;
			
		case BAD_BEHAVE:
			printf(" Как и я. Всего доброго. \n");
			return BAD_BEHAVE;
			
		case BAD_DATA:
			printf(" Прошу, проверьте данные в файле. \n");
			break;
			
		case NO_MATCHES:
			printf(" Совпадений не найдено. \n");
			break;
			
		case SUCCESS:
			printf(" Успешно.\n");
			break;
	}
	return SUCCESS;
}

void show_title(int flag, int number)
{
	switch (flag)
	{
		case 1: 
			printf(" ----================================================----\n"
			       "                  --== МУЗЫКАЛЬНЫЙ ==-- \n"
		           " ----================================================----\n"
				   " Введите: \n");	
			break;
			
		case 2: 
			printf(" ----================================================----\n"
			       "               --== РЕПЕРТУАР ТЕАТРОВ ==--\n"
				   " ----================================================----\n");
			break;
		
		case 3:
			printf(" ----================================================----\n"
			       "                  --== ТЕАТР № %d ==-- \n"
		           " ----================================================----\n", 
				   number);
			break;	
			
		case 4:
			printf(" ----================================================----\n"
			       "               --== РАБОТА С ФАЙЛОМ ==--\n"
				   " ----================================================----\n"
				   " Введите название файла: ");
			break;
			
		case 5:
			printf(" ----================================================----\n"
				   "                --== УДАЛИТЬ ЭЛЕМЕНТ ==--\n"
				   " ----================================================----\n"
				   " Найти и удалить репертуар театра по названию спектакля.\n\n"
				   " Введите название спектакля: ");
			break;
			
		case 6: 
			printf(" ----================================================----\n"
				   "                     --== КЛЮЧИ ==--\n"
				   " ----================================================----\n"
				   "      Номер         Номер в таблице         Значение\n"
				   " ----================================================----\n");
			break;
				   
		case 7:
			printf(" ----================================================----\n"
				   "               --== ПРОИЗВОДИТЕЛЬНОСТЬ ==--\n"
				   " ----================================================----\n");
			break;
			
		case 8:
			printf(" ----================================================----\n"
			       "                --== ЗАВЕРШЕНИЕ РАБОТЫ ==--\n"
				   " ----================================================----\n");
			break;
	}
}

void show_text(int flag)
{
	switch (flag)
	{
		case 1:
			printf(" Спектакли для детей соответствующего возраста,\n"
				   " продолжительности, меньше заданной.\n");
	}
}