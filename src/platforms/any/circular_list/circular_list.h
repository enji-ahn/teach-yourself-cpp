#pragma once

#if defined(_MSC_VER)
  #ifdef CIRCULARLIST_EXPORTS
    #define DLL_DECL __declspec(dllexport)
  #else
    #define DLL_DECL __declspec(dllimport)
  #endif
#else
  #define DLL_DECL
#endif

struct circular_list_ {
	int head;
	int tail;

	size_t size;
	size_t elm_size; // sizeof each item
	void* block;
};

typedef circular_list_ circular_list;

DLL_DECL void circular_list_create(circular_list* list, size_t size, size_t sizeof_elm);
DLL_DECL void circular_list_destroy(circular_list* list);
DLL_DECL bool circular_list_pushback(circular_list* list, void* data);
