#include "linked_list.h"
#include "message_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DELIMETER ","

int get_size(struct address_book *list);

struct address_book {
	int size;
	struct record *head;
};

enum search_key { NAME = 1, SURNAME = 2, EMAIL = 3, PHONE_NUMBER = 4 };

/**
 * create_node() - Create a record.
 * @arg1: A string of the record user is trying to create
 *
 * Additionaly parses the provided string, allocates memory for the record.
 *
 * Return: Returns NULL if parsing has failed, or memory for the node couldn't be allocated, otherwise returns
 * the created record.
 */
struct record *create_node(char *address_line)
{
	char *name;
	char *surname;
	char *email;
	char *phoneNumber;
	name	    = strtok(address_line, DELIMETER);
	surname	    = strtok(NULL, DELIMETER);
	email	    = strtok(NULL, DELIMETER);
	phoneNumber = strtok(NULL, DELIMETER);
	if (surname == NULL || email == NULL || phoneNumber == NULL)
		return NULL;
	struct record *newNode = (struct record *)malloc(sizeof(struct record));
	if (newNode == NULL)
		return NULL;
	strncpy(newNode->name, name, sizeof(newNode->name));
	strncpy(newNode->surname, surname, sizeof(newNode->surname));
	strncpy(newNode->email, email, sizeof(newNode->email));
	strncpy(newNode->phoneNumber, phoneNumber, sizeof(newNode->phoneNumber));
	newNode->next = NULL;
	return newNode;
}

/**
 * create_list() - Create a linked list.
 *
 * Additionaly allocates memory for the linked list, initializes its members.
 *
 * Return: Returns RECORD_CREATE_ERROR message code if the record couldn't be created, otherwise returns 0.
 */
struct address_book *create_list()
{
	struct address_book *list = (struct address_book *)malloc(sizeof(struct address_book));
	if (list == NULL) {
		return NULL;
	}
	list->head = NULL;
	list->size = 0;
	return list;
}

/**
 * insert_at_end() - Insert a record at the end of linked list.
 * @arg1: A string of the record user is trying to insert
 * @arg2: A linked list of type 'struct address_book *'
 *
 * Return: Returns RECORD_CREATE_ERROR message code if the record couldn't be created, otherwise returns 0.
 */
int insert_at_end(char *address_line, struct address_book *list)
{
	struct record *current = NULL;
	if (list->head == NULL) {
		list->head = create_node(address_line);
		if (list->head == NULL)
			return RECORD_CREATE_ERROR;
		list->size++;
	} else {
		current = list->head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = create_node(address_line);
		if (current->next == NULL)
			return RECORD_CREATE_ERROR;
		list->size++;
	}
	return 0;
}

/**
 * insert_at_position() - Insert a record in linked list.
 * @arg1: An integer that specifies an index of record to be found
 * @arg2: A string of the record user is trying to insert
 * @arg3: A linked list of type 'struct address_book *'
 *
 * Return: Returns INVALID_INDEX message code if given index is larger than the list or is less than 1.
 * Returns RECORD_CREATE_ERROR message code if the record couldn't be created, otherwise returns 0.
 */
int insert_at_position(int index, char *address_line, struct address_book *list)
{
	int list_size = get_size(list);
	if (index < 1 || index > list_size) {
		return INVALID_INDEX;
	}
	struct record *current = NULL;
	if (list->head == NULL) {
		list->head = create_node(address_line);
		if (list->head == NULL)
			return RECORD_CREATE_ERROR;
		list->size++;
	} else {
		int pos = 0;
		current = list->head;
		while (pos < index - 1) {
			pos++;
			if (current->next != NULL) {
				current = current->next;
			}
		}
		struct record *temp = create_node(address_line);
		if (temp == NULL)
			return RECORD_CREATE_ERROR;
		temp->next    = current->next;
		current->next = temp;
		list->size++;
	}
	return 0;
}

/**
 * delete_at_position() - Delete a linked list record at specified index.
 * @arg1: An integer that specifies an index of entry to be found
 * @arg2: A linked list of type 'struct address_book *'
 *
 * Return: Returns INVALID_INDEX message code if given index is larger than the list or is less than 1.
 * Returns RECORD_DELETE_ERROR message code if the record couldn't be deleted, otherwise returns 0.
 */
int delete_at_position(int index, struct address_book *list)
{
	int list_size = get_size(list);
	if (index < 1 || index > list_size) {
		return INVALID_INDEX;
	} else if (index == 1 && list->head != NULL) {
		struct record *remove = list->head;
		list->head	      = list->head->next;
		free(remove);
		list->size--;
	} else {
		struct record *temp = list->head;
		for (int i = 1; i < index - 1; i++) {
			if (temp != NULL) {
				temp = temp->next;
			}
		}
		if (temp != NULL && temp->next != NULL) {
			struct record *remove = temp->next;
			temp->next	      = temp->next->next;
			free(remove);
			list->size--;
		} else
			return RECORD_DELETE_ERROR;
	}
	return 0;
}

/**
 * delete_list() - Delete the provided list.
 * @arg1: A linked list of type 'struct address_book *'
 *
 * Return: Returns EMPTY_LIST message code if list doesn't exist otherwise returns 0.
 */
int delete_list(struct address_book **list)
{
	if (*list == NULL)
		return EMPTY_LIST;
	struct record *current = (*list)->head;
	struct record *next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	free(*list);
	*list = NULL;
	return 0;
}

/**
 * find_at() - Find a record in linked list according to specified index.
 * @arg1: An integer that specifies an index of record to be found
 * @arg2: A linked list of type 'struct address_book *'
 * @arg3: An integer pointer to a message code
 *
 * Return: Returns NULL in case of an error and sets the message code, otherwise returns a found record.
 */
struct record *find_at(int index, struct address_book *list, int *error_code)
{
	int list_size = get_size(list);
	if (index < 1 || index > list_size) {
		*error_code = INVALID_INDEX;
		return NULL;
	}
	struct record *current = list->head;
	if (current != NULL) {
		int pos = 0;
		while (pos < index - 1) {
			pos++;
			if (current->next != NULL) {
				current = current->next;
			}
		}
		return current;
	} else {
		*error_code = EMPTY_LIST;
		return NULL;
	}
}

/**
 * find_by() - Find records in linked list that match a criteria and print them.
 * @arg1: An integer that specifies a criteria
 * @arg2: A string of the record user is looking for
 * @arg3: A linked list of type 'struct address_book *'
 *
 * Finds entries according to provided search key, and prints them.
 * If there's more than one record found it will print them all.
 *
 * Return: Returns EMPTY_LIST message code if linked list is empty, otherwise returns 0.
 */
int find_by(int search_key, char *address_key, struct address_book *list)
{
	struct record *current = list->head;
	if (current == NULL) {
		return EMPTY_LIST;
	}
	while (current != NULL) {
		switch (search_key) {
		case NAME:
			if (strcmp(current->name, address_key) == 0)
				print_record(current);
			break;
		case SURNAME:
			if (strcmp(current->surname, address_key) == 0)
				print_record(current);
			break;
		case EMAIL:
			if (strcmp(current->email, address_key) == 0)
				print_record(current);
			break;
		case PHONE_NUMBER:
			if (strcmp(current->phoneNumber, address_key) == 0)
				print_record(current);
			break;
		default:
			return INVALID_SEARCH_KEY;
			break;
		}
		current = current->next;
	}

	return 0;
}

/**
 * print_linked_list() - Print linked list whole.
 * @arg1: A linked list of type 'struct address_book *'
 *
 * Prints out the provided linked list, including table headers.
 *
 * Return: Returns EMPTY_LIST message code if linked list is empty, otherwise returns 0
 */
int print_linked_list(struct address_book *list)
{
	if (list->head == NULL) {
		return EMPTY_LIST;
	}
	struct record *temp = list->head;
	int table_size	    = 142;
	char buf[table_size];
	memset(buf, '-', table_size - 1);
	buf[table_size - 1] = '\0';

	printf("%s\n", "ADDRESS BOOK");
	printf("%s\n", buf);
	printf("%s %-32s %s %-32s %s %-32s %s %-32s %s\n", "|", "Name", "|", "Surname", "|", "Email", "|",
	       "Phone Number", "|");
	printf("%s\n", buf);
	while (temp != NULL) {
		print_record(temp);
		temp = temp->next;
	}
	printf("%s\n", buf);
	return 0;
}

/**
 * print_record() - Print a record in a linked list.
 * @arg1: A linked list record of type 'struct record *'
 *
 * Return: Returns 0 if record exists, otherwise returns RECORD_NOT_FOUND message code.
 */
int print_record(struct record *record)
{
	if (record == NULL) {
		return RECORD_NOT_FOUND;
	}
	printf("%s %-32s %s %-32s %s %32s %s %32s %s\n", "|", record->name, "|", record->surname, "|",
	       record->email, "|", record->phoneNumber, "|");
	return 0;
}

/**
 * get_size() - Get size of the linked list.
 * @arg1: A linked list of type 'struct address_book *'
 *
 * Return: Returns 0 if list doesn't exist, otherwise returns the size of list.
 */
int get_size(struct address_book *list)
{
	if (list != NULL)
		return list->size;
	else
		return 0;
}