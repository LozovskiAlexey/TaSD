FILE_LIST := main.o file_funcs.o funcs.o 
HEADER := libs.h struct.h funcs.h 
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
RM := rm -rf

main.o: main.c $(HEADER)
	$(CC) $(CFLAGS) -c $^
	
funcs.o: funcs.c $(HEADER)
	$(CC) $(CFLAGS) -c $^

file_funcs.o: file_funcs.c 	$(HEADER)
	$(CC) $(CFLAGS) -c $^
	
app.exe: $(FILE_LIST) 
	$(CC) $(CFLAGS) -o $@ $^
	
clear: *.o *.exe
	 $(RM) *.o *.exe