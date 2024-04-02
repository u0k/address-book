#pragma once

struct record {
	char name[100];
	char surname[100];
	char email[100];
	char phoneNumber[100];
	struct record *next;
};
struct address_book;

struct address_book *create_list();
int insert_at_end(char *address_line, struct address_book *list);
int insert_at_position(int index, char *address_line, struct address_book *list);
int delete_at_position(int index, struct address_book *list);
int delete_list(struct address_book **list);
struct record *find_at(int index, struct address_book *list, int *error_code);
int find_by(int search_key, char *adress_key, struct address_book *list);
int print_record(struct record *record);
int print_linked_list(struct address_book *list);