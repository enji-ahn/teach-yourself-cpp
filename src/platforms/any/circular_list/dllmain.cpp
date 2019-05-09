// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <cassert>
#include <cstring>
#include "circular_list.h"

#ifndef ASSERT_EQ
#define ASSERT_EQ(A, B) assert((A) == (B))
#endif

#ifndef EXPECT_EQ
#define EXPECT_EQ(A, B) assert((A) == (B))
#endif

#ifndef ASSERT_TRUE
#define ASSERT_TRUE(A) assert(A)
#endif


#ifndef EXPECT_TRUE
#define EXPECT_TRUE(A) assert(A)
#endif

#ifndef EXPECT_NE
#define EXPECT_NE(A, B) assert((A) != (B))
#endif


void clist_overrun()
 {
	circular_list list;
	circular_list_create(&list, 2, sizeof(char));

    ASSERT_EQ(list.head, 0);
	ASSERT_EQ(list.tail, 0);

	char a = 'a';
	circular_list_pushback(&list, (void*)&a);

	EXPECT_EQ(list.head, 0);
	EXPECT_EQ(list.tail, 1);

	char b = 'b';
	circular_list_pushback(&list, (void*)&b);

	EXPECT_EQ(list.head, 1);
	EXPECT_EQ(list.tail, 0);

	char c = 'c';
	circular_list_pushback(&list, (void*)&c);

	EXPECT_EQ(list.head, 0);
	EXPECT_EQ(list.tail, 1);

	circular_list_destroy(&list);
}

void clist_insert_item()
 {
	circular_list list;
	circular_list_create(&list, 10, sizeof(char));

	ASSERT_EQ(list.head, 0);
	ASSERT_EQ(list.tail, 0);

	char a = 'a';
	circular_list_pushback(&list, (void*)&a);

	EXPECT_EQ(list.head, 0);
	EXPECT_EQ(list.tail, 1); // index to push next

	char b = 'b';
	circular_list_pushback(&list, (void*)&b);

	EXPECT_EQ(list.head, 0);
	EXPECT_EQ(list.tail, 2); // index to push next

	circular_list_destroy(&list);
}

void clist_creation_deletion() {
	circular_list list;
	memset(&list, 0, sizeof(list));

	ASSERT_EQ(list.size, 0);
	ASSERT_TRUE(list.block == NULL);

	circular_list_create(&list, 10, sizeof(int));

	EXPECT_NE(list.size, 0);
	EXPECT_TRUE(list.block != NULL);
	EXPECT_EQ(list.elm_size, sizeof(int));

	circular_list_destroy(&list);

	EXPECT_EQ(list.size, 0);
	EXPECT_TRUE(list.block == NULL);
}

int main()
{
    clist_creation_deletion();

    clist_insert_item();

    clist_overrun();

    return 0;
}
