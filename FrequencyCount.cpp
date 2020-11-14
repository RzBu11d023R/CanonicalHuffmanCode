#include "FrequencyCount.h"

#include <ctime>

FrequencyTable InitTable() {
	FrequencyTable f = (FrequencyTable)malloc(sizeof(frequencyTable));
	if (f == nullptr)return f;
	f->length = 0;
	for (int i = 0; i < BYTE_CHAR_UPPER_LIMIT; i++) {
		f->isExist[i] = 0;
		f->totalWeight = 0;
	}
	return f;
}

FrequencyTable BuildTable(const char* Text, unsigned long long length)
{
	FrequencyTable table = InitTable();
	for (unsigned long long i = 0; i < length; i++)
	{
		int index = (int)Text[i] + CHAR_OFFSET;
		if (table->isExist[index])
		{
			table->weight[index]++;
			table->totalWeight++;
		}
		else
		{
			table->isExist[index] = 1;
			table->existChar[table->length++] = index;
			table->weight[index] = 1;
			table->totalWeight++;
		}
	}
	return table;
}


int GetLength(FrequencyTable table)
{
	return table->length;
}

void InitIterator(FrequencyTable table)
{
	table->iterator = 0;
}

int HasNext(FrequencyTable table)
{
	return table->iterator < table->length;
}

Iterator Next(FrequencyTable table)
{
	if (table->iterator < table->length)
	{
		return table->iterator++;
	}
	return 0;
}

inline char GetChar(FrequencyTable table, Iterator it)
{
	return (char)(table->existChar[it] - CHAR_OFFSET);
}

inline int GetWeight(FrequencyTable table, Iterator it)
{
	return table->weight[table->existChar[it]];
}

void GetCharSet(FrequencyTable table,char*& charSet, int*& weightSet)
{
	char* cs = (char*)malloc(sizeof(char) * table->length);
	int* ws = (int*)malloc(sizeof(int) * table->length);
	InitIterator(table);
	int index = 0;
	while(HasNext(table))
	{
		Iterator it = Next(table);
		cs[index] = GetChar(table,it);
		ws[index++] = GetWeight(table, it);
	}
	charSet = cs;
	weightSet = ws;
}

