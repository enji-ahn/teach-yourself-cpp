﻿// BitOrder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdint>
#include <cstring>

int main()
{
	uint32_t value;
	value = 1;

	printf("value : %d ==> ", value);
	for (int i = 0; i < 32; ++i) {
		printf("%d ", value & (1 << i));
	}
	std::cout << std::endl;

	uint8_t arr[4];
	memset(arr, 0, sizeof(arr));
	arr[0] = 1;
	printf("value : %d%d%d%d ==> ", arr[0], arr[1], arr[2], arr[3]);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 8; ++j) {
			printf("%d ", arr[i] & (1 << j));
		}
	}
	std::cout << std::endl;

	getchar();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
