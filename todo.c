#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "todo_interface.h"
#include "list.h"

#define TODO_FILENAME ".todos"

void print_help()
{
	printf("Todo -- A command line interface for keeping track of tasks\n\n");
	printf("usage: todo [global options] command [command options] [arguments...]\n\n");
	printf("COMMANDS:\n");
	printf("   list\t\t\tList current to-dos\n");
	printf("   add\t\t\tAdd new to-do\n");
}

int main(int argc, char **argv)
{
	/*char *command = NULL;
	int c;

	opterr = 0;
	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c)
		{
		case 'h':
			print_help();
			return 0;
		case '?':
			fprintf(stderr, "Unknown option `\\x%x'.\n", optopt);
			return 1;
		default:
			return 1;
		}
	}

	for (int index = optind; index < argc; index++) {
		printf("Non-option argument %s\n", argv[index]);
	}*/
	
	if (argc == 1) {
		print_help();
		return 0;
	}

	LinkedList *todos = read_file(TODO_FILENAME);	

	if (argc == 2) {
		if (strcmp("add", argv[1]) == 0) {
			printf("Title: ");
			char *title = calloc(MAX_PROPERTY_LEN, sizeof(char));
			fgets(title, MAX_PROPERTY_LEN - 1, stdin);
			remove_newline(title);

			printf("Description: ");
			char *desc = calloc(MAX_PROPERTY_LEN, sizeof(char));
			fgets(desc, MAX_PROPERTY_LEN - 1, stdin);
			remove_newline(desc);

			Todo *new = new_todo(title, desc, 0);

			list_add(todos, new);
			write_file(todos, TODO_FILENAME);

			printf("%s\n%s\n", title, desc);
		}
		else if (strcmp("list", argv[1]) == 0) {
			display_todos(todos);
		}
	}
	
	return 0;
}
