
#include "helper_functions.h"
#include "message_handler.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * handle_record_add() - Handler for adding a record to a linked list.
 * @arg1: A string of the record user is trying to add
 * @arg2: Length of the string
 * @arg3: A linked list of type 'struct address_book *'
 *
 * Return: Returns an integer that specifies a message code
 */
int handle_record_add(char *record_line, size_t size, struct address_book *list)
{
	printf("%s\n", "Enter comma separated name, surname, email, "
		       "phone number:");
	if (fgets(record_line, size, stdin)) {
		char *occurrence = strchr(record_line, '\n');
		if (occurrence) {
			*occurrence = '\0';
		}
		int rt = insert_at_end(record_line, list);
		print_linked_list(list);
		return rt;
	}
	return 0;
}

/**
 * handle_record_add_pos() - Handler for adding a record to a linked list at specific index.
 * @arg1: A string of the record user is trying to add
 * @arg2: A string of the index user provided
 * @arg3: Length of the strings
 * @arg4: An integer that specifies an index of record to be added
 * @arg5: A linked list of type 'struct address_book *'
 *
 * Return: Returns INVALID_INDEX if entered index was not an integer, otherwise  returns a specific message
 * code.
 */
int handle_record_add_pos(char *record_line, char *index_line, size_t size, int index,
			  struct address_book *list)
{
	printf("%s\n", "Enter position index:");
	if (fgets(index_line, size, stdin)) {
		if (sscanf(index_line, "%d", &index) == 1) {
			printf("%s\n", "Enter comma separated name, "
				       "surname, email, "
				       "phone number:");
			if (fgets(record_line, size, stdin)) {
				char *occurrence = strchr(record_line, '\n');
				if (occurrence) {
					*occurrence = '\0';
				}
				int rt = insert_at_position(index, record_line, list);
				print_linked_list(list);
				return rt;
			}
		} else
			return INVALID_INDEX;
	}
	return 0;
}

/**
 * handle_record_delete_pos() - Handler for deleting a record from a linked list at specific index.
 * @arg1: A string of the index user provided
 * @arg2: Length of the string
 * @arg3: An integer that specifies an index of record to be deleted
 * @arg4: A linked list of type 'struct address_book *'
 *
 * Return: Returns INVALID_INDEX if entered index was not an integer, otherwise  returns a specific message
 * code.
 */
int handle_record_delete_pos(char *index_line, size_t size, int index, struct address_book *list)
{
	printf("%s\n", "Enter position index:");
	if (fgets(index_line, size, stdin)) {
		if (sscanf(index_line, "%d", &index) == 1) {
			int rt = delete_at_position(index, list);
			print_linked_list(list);
			return rt;
		} else
			return INVALID_INDEX;
	}
	return 0;
}

/**
 * handle_record_find_pos() - Handler for finding a record in a linked list at specific index.
 * @arg1: A string of the index user provided
 * @arg2: Length of the string
 * @arg3: An integer that specifies an index of record to be found
 * @arg4: A linked list of type 'struct address_book *'
 *
 * Return: Returns INVALID_INDEX if entered index was not an integer, RECORD_NOT_FOUND if record was not
 * found, otherwise  returns a specific message code.
 */
int handle_record_find_pos(char *index_line, size_t size, int index, struct address_book *list)
{
	int error_code = 0;
	printf("%s\n", "Enter position index:");
	if (fgets(index_line, size, stdin)) {
		if (sscanf(index_line, "%d", &index) == 1) {
			struct record *found = find_at(index, list, &error_code);
			if (error_code != 0)
				return error_code;
			else if (found != NULL) {
				int rt = print_record(found);
				if (rt != 0)
					return rt;
				return 0;
			} else
				return RECORD_NOT_FOUND;
		} else
			return INVALID_INDEX;
	}
	return 0;
}

/**
 * handle_record_find_value() - Handler for finding a record in a linked list by provided criteria.
 * @arg1: A string of the criteria user provided
 * @arg2: Length of the criteria string
 * @arg3: An integer that specifies an index of criteria
 * @arg4: A string of the record user is trying to find
 * @arg5: Length of the record string
 * @arg6: A linked list of type 'struct address_book *'
 *
 * Return: Returns INVALID_SEARCH_KEY if entered criteria was not an integer, otherwise  returns a specific
 * message code.
 */
int handle_record_find_value(char *search_line, size_t search_size, int search, char *record_line,
			     size_t size, struct address_book *list)
{
	printf("%s\n", "Search by (1-name, 2-surname, 3-email, 4-number): ");
	if (fgets(search_line, search_size, stdin)) {
		if (!strchr(search_line, '\n')) {
			scanf("%*[^\n]");
			scanf("%*c");
		}
		if (sscanf(search_line, "%d", &search) == 1) {
			printf("%s\n", "Search for record: ");
			char *occurrence = strchr(search_line, '\n');
			if (occurrence) {
				*occurrence = '\0';
			}
			if (fgets(record_line, size, stdin)) {
				occurrence = strchr(record_line, '\n');
				if (occurrence) {
					*occurrence = '\0';
				}
				int rt = find_by(search, record_line, list);
				if (rt != 0)
					return rt;
			}
		} else
			return INVALID_SEARCH_KEY;
	}
	return 0;
}

/**
 * handle_load_file() - Handler for loading a file.
 * @arg1: A string of the file path
 * @arg2: Length of the file path string
 * @arg3: A string of the file name
 * @arg4: A linked list of type 'struct address_book *'
 *
 * Return: Returns NULL if file can not be loaded, otherwise returns a pointer to file.
 */
FILE *handle_load_file(char *path, int path_size, char *file_name, struct address_book *list)
{
	FILE *address_file = NULL;
	if (snprintf(path, path_size, "%s/%s", getenv("HOME"), file_name) >= path_size) {
		fprintf(stderr, "%s\n", strerror(errno));
	}
	address_file = fopen(path, "r");

	if (address_file == NULL) {
		fprintf(stderr, "%s\n", strerror(errno));
	} else {
		char line[400];
		while (fgets(line, sizeof(line), address_file)) {
			char *ptr = strchr(line, '\n');
			if (ptr) {
				*ptr = '\0';
			}
			if (strcmp(line, "\n") == 0) {
				continue;
			}
			int rt = insert_at_end(line, list);
			if (rt != 0)
				print_error_message(rt);
		}
	}
	return address_file;
}

/**
 * print_options() - Handler for printing user input interface.
 */
void print_options()
{
	printf("%s\n", "SELECT OPTION:");
	printf("%s\n", "1. Display all records");
	printf("%s\n", "2. Add new record");
	printf("%s\n", "3. Add new record by position");
	printf("%s\n", "4. Delete record by position");
	printf("%s\n", "5. Delete all records");
	printf("%s\n", "6. Find record by position");
	printf("%s\n", "7. Find record by name, surname, email, number");
	printf("%s\n", "8. Exit program");
}