FILE_LIST := main.o funcs.o lfuncs.o test.o
HEADER := funcs.h 
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
RM := rm -rf

main.o: main.c $(HEADER)
	$(CC) $(CFLAGS) -c $^
	
funcs.o: funcs.c $(HEADER)
	$(CC) $(CFLAGS) -c $^

lfuncs.o: lfuncs.c $(HEADER)
	$(CC) $(CFLAGS) -c $^
	
test.o:  test.c $(HEADER)
	$(CC) $(CFLAGS) -c $^
	
app.exe: $(FILE_LIST) 
	$(CC) $(CFLAGS) -o $@ $^
	
clear: *.o *.exe
	 $(RM) *.o *.exe