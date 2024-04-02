#include "message_handler.h"
#include <stdio.h>

/**
 * print_error_message() - Print out error message.
 * @arg1: Integer which provides a number that maps to specific message
 *
 * Print out an error message to stderr, according to provided message code.
 *
 */
void print_error_message(int message_code)
{
	switch (message_code) {
	case EMPTY_LIST:
		fprintf(stderr, "%s\n", "Address book is currently empty.");
		break;
	case RECORD_CREATE_ERROR:
		fprintf(stderr, "%s\n", "Record couldn't be created.");
		break;
	case RECORD_DELETE_ERROR:
		fprintf(stderr, "%s\n", "Record couldn't be deleted.");
		break;
	case RECORD_NOT_FOUND:
		fprintf(stderr, "%s\n", "Record couldn't be found.");
		break;
	case INVALID_INDEX:
		fprintf(stderr, "%s\n", "Invalid index entered.");
		break;
	case INVALID_SEARCH_KEY:
		fprintf(stderr, "%s\n", "Invalid search key entered.");
		break;
	case INVALID_OPTION:
		fprintf(stderr, "%s\n", "Invalid option entered.");
		break;
	case ERROR_LIST_CREATION:
		fprintf(stderr, "%s\n", "Memory for list couldn't be allocated.");
		break;
	case ERROR_FILE_CLOSE:
		fprintf(stderr, "%s\n", "File couldn't be closed.");
		break;
	case ERROR_LIST_DELETE:
		fprintf(stderr, "%s\n", "List couldn't be deleted.");
		break;
	case ERROR_SIGNAL_SET:
		fprintf(stderr, "%s\n", "Error setting a signal.");
		break;
	default:
		break;
	}
}