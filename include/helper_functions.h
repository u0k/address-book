#pragma once
#include <stdio.h>
#include "linked_list.h"

void print_options();
void signal_handler(int signum);
FILE *handle_load_file(char *path, int path_size, char *file_name, struct address_book *list);
int handle_record_add(char *record_line, size_t size, struct address_book *list);
int handle_record_add_pos(char *record_line, char *index_line, size_t size, int index,
			  struct address_book *list);
int handle_record_delete_pos(char *index_line, size_t size, int index, struct address_book *list);
int handle_record_find_pos(char *index_line, size_t size, int index, struct address_book *list);
int handle_record_find_value(char *search_line, size_t search_size, int search, char *record_line,
			     size_t size, struct address_book *list);