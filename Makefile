CFLAGS=-g

all: todo

todo: list.o todo_interface.o todo.o
	cc $(CFLAGS) todo.o list.o todo_interface.o -o todo

todo.o: todo.c
	cc $(CFLAGS) -c todo.c

list.o: list.c
	cc $(CFLAGS) -c list.c

todo_interface.o: todo_interface.c
	cc $(CFLAGS) -c todo_interface.c

clean:
	rm *.o todo