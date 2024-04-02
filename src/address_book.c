#include "address_book.h"
#include "helper_functions.h"
#include "message_handler.h"
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int signal_active = 1;
int main(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTSTP, signal_handler);
	if (signal(SIGINT, signal_handler) == SIG_ERR || signal(SIGTERM, signal_handler) == SIG_ERR ||
	    signal(SIGQUIT, signal_handler) == SIG_ERR || signal(SIGTSTP, signal_handler) == SIG_ERR)
		goto error_signal_setting;

	char option_line[2];
	char search_line[3];
	int option;
	int search = -1;
	char index_line[400];
	int index = -1;
	char record_line[400];
	size_t size;
	size_t search_size;
	int return_code		  = 0;
	FILE *address_file	  = NULL;
	struct address_book *list = NULL;
	list			  = create_list();
	if (list == NULL) {
		goto error_list_creation;
	}
	char path[128];
	char *fname  = "addresses.csv";
	address_file = handle_load_file(path, sizeof(path), fname, list);

	if (address_file != NULL) {
		int rt = fclose(address_file);
		if (rt != 0)
			goto error_file_close;
	}

	print_options();
	while (fgets(option_line, sizeof(option_line), stdin) && signal_active) {
		if (!strchr(option_line, '\n')) {
			scanf("%*[^\n]");
			scanf("%*c");
		}
		if (list == NULL) {
			list = create_list();
			if (list == NULL) {
				goto error_list_creation;
			}
		}
		if (sscanf(option_line, "%d", &option) == 1) {
			switch (option) {
			case DISPLAY:
				return_code = print_linked_list(list);
				if (return_code != 0)
					print_error_message(return_code);
				break;
			case ADD_RECORD:
				size	    = sizeof(record_line) / sizeof(record_line[0]);
				return_code = handle_record_add(record_line, size, list);
				if (return_code != 0)
					print_error_message(return_code);
				break;
			case ADD_RECORD_POS:
				size = sizeof(record_line) / sizeof(record_line[0]);
				return_code =
					handle_record_add_pos(record_line, index_line, size, index, list);
				if (return_code != 0)
					print_error_message(return_code);
				break;
			case DELETE_RECORD_POS:
				size	    = sizeof(index_line) / sizeof(index_line[0]);
				return_code = handle_record_delete_pos(index_line, size, index, list);
				if (return_code != 0)
					print_error_message(return_code);
				break;
			case DELETE_LIST:
				return_code = delete_list(&list);
				if (list != NULL)
					goto error_list_deletion;
				else if (return_code != 0)
					print_error_message(return_code);
				break;
			case FIND_RECORD_POS:
				size	    = sizeof(index_line) / sizeof(index_line[0]);
				return_code = handle_record_find_pos(index_line, size, index, list);
				if (return_code != 0) {
					print_error_message(return_code);
				}
				break;
			case FIND_RECORD_VALUE:
				search_size = sizeof(search_line) / sizeof(search_line[0]);
				size	    = sizeof(record_line) / sizeof(record_line[0]);
				return_code = handle_record_find_value(search_line, search_size, search,
								       record_line, size, list);
				if (return_code != 0) {
					print_error_message(return_code);
				}
				break;
			case EXIT_PROGRAM:
				goto cleanup;
				break;
			default:
				print_error_message(INVALID_OPTION);
				break;
			}
		} else {
			print_error_message(INVALID_OPTION);
		}
		print_options();
	}
	if (!signal_active) {
		goto cleanup;
	}

error_list_creation:
	print_error_message(ERROR_LIST_CREATION);
	exit(EXIT_FAILURE);

error_file_close:
	print_error_message(ERROR_FILE_CLOSE);
	exit(EXIT_FAILURE);

error_list_deletion:
	print_error_message(ERROR_LIST_DELETE);
	exit(EXIT_FAILURE);

error_signal_setting:
	print_error_message(ERROR_SIGNAL_SET);
	exit(EXIT_FAILURE);

cleanup:
	delete_list(&list);
	if (list == NULL)
		exit(EXIT_SUCCESS);
	else {
		exit(EXIT_FAILURE);
	}
}

/**
 * signal_handler() - Handler for processing signals.
 * @arg1: An integer that specifies signal's number
 *
 * On called signal changes global variable to inactive.
 *
 */
void signal_handler(int signum)
{
	signal_active = 0;
}
