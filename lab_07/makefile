OBJS := main.o funcs.o menu.o
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
RM := rm -rf

main.o: main.c
	$(CC) $(CFLAGS) -c $^
	
menu.o: menu.c
	$(CC) $(CFLAGS) -c $^
	
funcs.o: funcs.c
	$(CC) $(CFLAGS) -c $^	
	
app.exe: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^
	
clear: *.o *.exe *.gv 
	 $(RM) $^