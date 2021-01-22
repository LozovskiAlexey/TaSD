OBJS := main.o menu.o avl_tree.o hash_table.o tree.o test.o
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
RM := rm -rf

main.o: main.c
	$(CC) $(CFLAGS) -c $^
	
avl_tree.o: avl_tree.c
	$(CC) $(CFLAGS) -c $^
	
hash_table.o: hash_table.c
	$(CC) $(CFLAGS) -c $^
	
menu.o: menu.c
	$(CC) $(CFLAGS) -c $^
	
test.o: test.c
	$(CC) $(CFLAGS) -c $^
	
tree.o: tree.c
	$(CC) $(CFLAGS) -c $^
	
app.exe: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^
	
clear: *.o *.exe
	 $(RM) *.o *.exe