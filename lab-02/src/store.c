/*
 * store.c
 *
 *  Created on: Oct 3, 2009
 *      Author: wesley
 */
#include "store.h"

#include <stdio.h>

int save(const order_list_t* list, char* filename) {
	FILE* fp;
	
	if ((fp = fopen(filename, "wb")) != NULL) {
		
		{
			int value = 0;
			
			value = stock_bean();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
			
			value = stock_corn();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
			
			value = stock_milk();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
			
			value = stock_rice();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
			
			value = stock_wine();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
		}
		
		{
			unsigned value;
			order_t* it;
			
			value = get_curr_code();
			fwrite((const void*)&(value), sizeof(unsigned), 1, fp);
			
			for (it = list->tail; it && (it != list->head->prev);
					it = it->prev) {
				fwrite((const void*)&(it->data), sizeof(order_item_t), 1, fp);
			}
		}
		
		fclose(fp);
	}
}


int load(order_list_t* list, char* filename) {
	FILE* fp;
	
	int value = 0;
	
	if ((fp = fopen(filename, "rb")) != NULL) {
		
		{
			int bean = 0;
			int corn = 0;
			int milk = 0;
			int rice = 0;
			int wine = 0;
			
			fread(&bean, sizeof(int), 1, fp);
			fread(&corn, sizeof(int), 1, fp);
			fread(&milk, sizeof(int), 1, fp);
			fread(&rice, sizeof(int), 1, fp);
			fread(&wine, sizeof(int), 1, fp);
			
			stock_load(bean, corn, milk, rice, wine);
		}
		
		{
			unsigned code;
			order_t order;
			
			code = 0;
			fread(&code, sizeof(unsigned), 1, fp);
			
			while (fread(&(order.data), sizeof(order_item_t), 1, fp)) {
				request_order(list, order);
			}
			
			set_curr_code(code);
		}
		
		fclose(fp);
	}
}
