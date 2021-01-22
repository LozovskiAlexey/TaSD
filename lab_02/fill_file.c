#include "mylib.h"
#include "structures.h"
#include "functions.h"

void finish_job(theater_t *theater, int size)
{
	show_title(8, 0);
	
	printf(" Не желаете сохранить новую базу?\n"
		   " 1. Да\n"
		   " 2. Нет\n"
		   " Введите: ");
	
	int result = check_answer(2);
	
	while (result == INV_INPUT)
	{
		printf(" Не желаете сохранить новую базу?\n"
		       " 1. Да\n"
		       " 2. Нет\n"
		       " Введите: ");
	
		result = check_answer(2);
	}
	
	if (result == 1)
		open_outfile(theater, size);
}

void open_outfile(theater_t *theater, int size)
{
	char *file_name = NULL;
	
	printf(" Введите имя файла: ");
	while (check_struct_data(&file_name, 0) == INV_INPUT)
		printf(" Введите имя файла: ");
	
	FILE *file = fopen(file_name, "w");
	
	fprintf(file, "%d\n", size);
	for(int i = 0; i < size; i++)
		fill_file(theater[i], file);
}

void put_music(musical_t music, FILE *file)
{

	fputs(music.composer, file);
	fputs("\n", file);

	fputs(music.country, file);
	fputs("\n", file);

	fputs(music.min_age, file);
	fputs("\n", file);

	fputs(music.length, file);
	fputs("\n", file);

}

void put_adult(theater_t theater, FILE *file)
{
	switch (theater.type.adult.type)
	{
		case 1:
			fputs("1\n", file);
			break;
			
		case 2:
			fputs("2\n", file);
			break;
			
		case 3:
			fputs("3\n", file);
			break;
	}
}

void put_child(theater_t theater, FILE *file)
{
	switch (theater.type.child.genre)
	{
		case 1:
			fputs("1\n", file);
			fputs(theater.type.child.age, file);
			fputs("\n", file);
			break;
			
		case 2:
			fputs("2\n", file);
			fputs(theater.type.child.age, file);
			fputs("\n", file);
			break;
			
		case 3:
			fputs("3\n", file);
			put_music(theater.type.child.type.music, file);
			break;	
	}
}

void fill_file(theater_t theater, FILE *file)
{
	fputs(theater.theater, file);
	fputs("\n", file);

	fputs(theater.spectacle, file);
	fputs("\n", file);

	fputs(theater.producer, file);
	fputs("\n", file);

	fputs(theater.min_price, file);
	fputs("\n", file);

	fputs(theater.max_price, file);
	fputs("\n", file);


	switch (theater.variable)
	{
		case 1:
			fputs("1\n", file);
			put_child(theater, file);

			break;
		case 2:
			fputs("2\n", file);
			put_adult(theater, file);

			break;
		case 3:
			fputs("3\n", file);
			put_music(theater.type.music, file);

			break;
	}
}