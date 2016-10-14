#include "todo_interface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wordexp.h>

Todo *new_todo(char *title, char *description, int completed)
{
	Todo *new_todo = malloc(sizeof(Todo));
	new_todo->title = strdup(title);
	new_todo->description = strdup(description);
   new_todo->completed = completed;
	return new_todo;
}

long fgetlong(int n, FILE *fd)
{
   char num[n];
   fgets(num, n, fd);
   long l = strtol(num, NULL, 10);
   return l;
}

void remove_newline(char *str)
{
   char *s = str;
   char c;
   while ((c = *str++) != '\0') {
      if (c == '\n') {
         *(str - 1) = '\0';
         break;
      }
   }
}

LinkedList *read_file(char *filename)
{
   char str[128];
   wordexp_t exp_result;
   FILE *todo_fd;

   memset(str, '\0', 128);

   wordexp("~", &exp_result, 0);
   strncpy(str, exp_result.we_wordv[0], 128);
   wordfree(&exp_result);

   strcat(str, "/");
   strcat(str, filename);

   if (!(todo_fd = fopen(str, "r"))) {
      return NULL;
   }

   LinkedList *todos = new_list(sizeof(Todo));

   char num_todos[MAX_PROPERTY_LEN];
   fgets(num_todos, MAX_PROPERTY_LEN, todo_fd);
   long n = strtol(num_todos, NULL, 10);
   printf("num todos in file: %ld\n", n);

   char read_title[MAX_PROPERTY_LEN];
   char read_desc[MAX_PROPERTY_LEN];
   long read_completed;
   for (long x = 0; x < n; x++) {
      memset(read_title, '\0', MAX_PROPERTY_LEN);
      memset(read_desc, '\0', MAX_PROPERTY_LEN);

      fgets(read_title, MAX_PROPERTY_LEN, todo_fd);
      remove_newline(read_title);
      fgets(read_desc, MAX_PROPERTY_LEN, todo_fd);
      remove_newline(read_desc);
      read_completed = fgetlong(MAX_PROPERTY_LEN, todo_fd);

      Todo *new = new_todo(read_title, read_desc, (int)read_completed);
      list_add(todos, new);
   }

   fclose(todo_fd);
   return todos;
}

void write_todo(Todo *todo, FILE *fd)
{
   char title_write[MAX_PROPERTY_LEN];
   char desc_write[MAX_PROPERTY_LEN];
   char completed_write[MAX_PROPERTY_LEN];

   memset(title_write, '\0', MAX_PROPERTY_LEN);
   memset(desc_write, '\0', MAX_PROPERTY_LEN);
   memset(completed_write, '\0', MAX_PROPERTY_LEN);

   strncpy(title_write, todo->title, MAX_PROPERTY_LEN);
   strncpy(desc_write, todo->description, MAX_PROPERTY_LEN);
   snprintf(completed_write, MAX_PROPERTY_LEN, "%d", todo->completed);

   fprintf(fd, "%s\n", title_write);
   fprintf(fd, "%s\n", desc_write);
   fprintf(fd, "%s\n", completed_write);
}

void write_file(LinkedList *todos, char *filename)
{
   char str[128];
   wordexp_t exp_result;
   FILE *todo_fd;

   memset(str, '\0', 128);

   wordexp("~", &exp_result, 0);
   strncpy(str, exp_result.we_wordv[0], 128);
   wordfree(&exp_result);

   strcat(str, "/");
   strcat(str, filename);

   if (!(todo_fd = fopen(str, "w+"))) {
      return;
   }

   fprintf(todo_fd, "%d\n", todos->num_elements);

   ListNode *dummy = todos->head;
   ListNode *tmp = dummy->next;

   while (tmp != dummy) {
      write_todo((Todo *)tmp->value, todo_fd);
      tmp = tmp->next;
   }

   fclose(todo_fd);
}

void print_todo(Todo *todo)
{
   printf("Title: %s\n\tDescription: %s\n\tCompleted: %d\n", todo->title, todo->description, todo->completed);
}

void display_todos(LinkedList *todos)
{
   ListNode *dummy = todos->head;
   ListNode *tmp = dummy->next;

   while (tmp != dummy) {
      print_todo((Todo *)tmp->value);
      tmp = tmp->next;
   }
}
