#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//Работа с меню
int main_menu();
int show_menu();
int choose_menu(int flag);
int choose_source_menu(int result, int *n, FILE **file);
void show_title(int flag, int number);
int choose_type_menu(int type, theater_t *theater);

//Заполнение структуры с консоли
theater_t *make_base(int size, key_t **);
int check_struct_data(char **str, int flag);
int addition(theater_t *theater, key_t *);
int fill_children_struct(child_t *child);
int fill_music_struct(musical_t *music);
int choose_child_type(int flag, child_t *child);

//Проверки ввода
int check_answer(int n);
int show_error(int flag);
int iSdigit(char *lineptr, size_t size);
size_t my_getline(char **lineptr, size_t *n, FILE *stream);

//Отображение структуры
void show_base(theater_t theater);
void show_childtype(child_t child);
void show_adulttype(int type);
void show_text(int flag);
void show_musictype(musical_t music);
int show(theater_t *theater, int n);
int find_base(theater_t theater, int given_age, int given_length);

//чтение структуры из файла
int open_file(int *n, FILE **file);
int fill_struct(theater_t *theater, key_t *, FILE *file);
int check_file_data(char **str, int flag, FILE *file);
int read_struct_type(theater_t *theater, FILE *file);
int fill_music(musical_t *music, FILE *file);
int fill_adult(adult_t *adult, FILE *file);
int fill_child(child_t *child, FILE *file);
int read_child_type(child_t *child, FILE *file);

//запись структуры в файл
void finish_job(theater_t *theater, int size);
void open_outfile(theater_t *theater, int size);
void fill_file(theater_t theater, FILE *file);
void put_child(theater_t theater, FILE *file);
void put_adult(theater_t theater, FILE *file);
void put_music(musical_t music, FILE *file);

//Работа со структурами
int delete_el(theater_t **theater, int *size);
void fill_keys(theater_t *theater, key_t **key, int size);
void show_keys(key_t *keys, int size);
void key_qsort(key_t *keys, int element);
int compare(const void * x1, const void * x2);
int compare_base(const void *price1, const void *price2);
void base_qsort(theater_t *theater, int size);
void sort_by_key(theater_t* theater, key_t *key, int size);
void swap(void *a, void *b, size_t size);
unsigned long long tick(void);
void key_mysort(key_t *keys, int size);
void base_mysort(theater_t *theater, int size);
void time_cmp(theater_t *theater, key_t *keys, int size);
void sort_speed(key_t *keys, int size);
#endif