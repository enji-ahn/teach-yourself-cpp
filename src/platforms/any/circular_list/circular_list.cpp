// circular_list.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include "circular_list.h"

void circular_list_create(circular_list* list, size_t size, size_t sizeof_elm)
{
	list->head = 0;
	list->tail = 0;
	list->size = size;
	list->elm_size = sizeof_elm;
	list->block = (void*)malloc(sizeof_elm * size);
}

void circular_list_destroy(circular_list* list)
{
	if (list->block) { free(list->block); }

	list->head = 0;
	list->tail = 0;
	list->size = 0;
	list->elm_size = 0;
	list->block = NULL;
}

bool circular_list_pushback(circular_list* list, void* data)
{
	memcpy((uint8_t*)list->block + (list->tail * list->elm_size), data, list->elm_size);
	++(list->tail);

	if (list->tail == list->size)
	{
		list->tail = 0;
		list->head = (list->head + 1 == list->size)? 0 : list->head + 1;
	}

	return true;
}

