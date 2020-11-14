#pragma once
#define CHAR_OFFSET 128
#define BYTE_CHAR_UPPER_LIMIT 256
#include <cstdlib>
#include <iostream>
typedef char boolean;
typedef int Iterator;
typedef struct frequencyTable {
	//assume that size of char == 1byte
	boolean isExist[BYTE_CHAR_UPPER_LIMIT];
	int weight[BYTE_CHAR_UPPER_LIMIT];
	int existChar[BYTE_CHAR_UPPER_LIMIT];
	int length;
	int totalWeight;
	Iterator iterator;
}*FrequencyTable;

FrequencyTable InitTable();

FrequencyTable BuildTable(const char* Text, unsigned long long length);

//simply call free(table)
inline void DestroyTable(FrequencyTable table)
{
	free(table);
}

void InitIterator(FrequencyTable table);

int HasNext(FrequencyTable table);

Iterator Next(FrequencyTable table);

char GetChar(FrequencyTable table, Iterator it);

int GetWeight(FrequencyTable table, Iterator it);

void GetCharSet(FrequencyTable table, char*& charSet, int*& weightSet);

int GetLength(FrequencyTable table);

