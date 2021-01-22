FILE_LIST := functions.o fill_structure_functions.o fill_file.o base_funcs.o menu_functions.o show_base_functions.o main.o read_file_functions.o
HEADERS := structures.h
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<
	
functions.o: functions.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^

base_funcs.o: base_funcs.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^
	
fill_file.o: fill_file.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^
	
show_base_functions.o: show_base_functions.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^
	
fill_structure_functions.o: fill_structure_functions.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^

menu_functions.o: menu_functions.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^
	
read_file_functions.o: read_file_functions.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^
	
app.exe: $(FILE_LIST)
	$(CC) -o $@ $^
