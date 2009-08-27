/*
 * main.c
 *
 *  Created on: Aug 27, 2009
 *      Author: wesley
 */

#include "contacts.h"

#include <stdio.h>

int main(int argc, char** argv) {
	contacts_t list;
	int len;
	int pos;
	
	init(&list);
	
	insert(&list, "I", "1234 5678", "Here");
	insert(&list, "You", "9876 5432", "There");
	insert(&list, "He", "1122 3344", "New York");
	
	printf("After Inserts\n");
	print_all(&list);
	
	
	if((pos = find_by_name(&list, "You")) >= 0) {
		printf("find_by_name found You\n");
		print_one(&list, pos);
	}
	else {
		printf("find_by_name failed!\n");
	}
	
	if((pos = find_by_place(&list, "New York")) >= 0) {
		printf("find_by_place found New York\n");
		print_one(&list, pos);
	}
	else {
		printf("find_by_place failed!\n");
	}
	
	delete(&list, "I");
	printf("After deletes I\n");
	print_all(&list);
	
	return 0;
}
