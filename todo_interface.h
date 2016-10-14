#include "list.h"

#define MAX_PROPERTY_LEN   255

typedef struct _Todo {
	char *title;
	char *description;
	int completed;
} Todo;

Todo *new_todo(char *title, char *description, int completed);
void remove_newline(char *str);
LinkedList *read_file(char *filename);
void write_file(LinkedList *todos, char *filename);
void display_todos(LinkedList *todos);