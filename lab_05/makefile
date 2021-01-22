OBJS:= main.o menu.o funcs.o array_queue.o list_queue.o test.o
CFLAGS:= -std=c99 -Wall -Werror -pedantic 
CC:= gcc 
RM:= rm -rf

main.exe: $(OBJS)
	$(CC) $(CFLAGS) -o  $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	
menu.o: menu.c 
	$(CC) $(CFLAGS) -c $^
	
funcs.o: funcs.c
	$(CC) $(CFLAGS) -c $^

array_queue.o: array_queue.c
	$(CC) $(CFLAGS) -c $^

list_queue.o: list_queue.c 
	$(CC) $(CFLAGS) -c $^
	
test.o: test.c 
	$(CC) $(CFLAGS) -c $^
	
clear: *.o *.exe
	$(RM)