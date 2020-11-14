#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
typedef unsigned long BitString;
#define BIT_STR_BYTE_COUNT sizeof(BitString)
#define BIT_STR_BIT_COUNT (sizeof(BitString)*8)

/*位串结构体定义*/
typedef struct bitSequence {
	//比特串的单位数组,每一个单位有BIT_STR_BIT_COUNT个比特---
	BitString* sequences_;
	unsigned int arrayLength_;//指定当前比特串单位数组长度
	unsigned long long stringLength_;//指定比特串的长度
	unsigned long long size_;//记录sequences_数组内存大小
	/*获取位串第参数位*/
	unsigned operator[](unsigned long long index) const {
		if (index >= stringLength_)return 0;
		const unsigned indexInSequences = (unsigned)(index / BIT_STR_BIT_COUNT);
		const unsigned indexInBitStringFromLow = BIT_STR_BIT_COUNT - (unsigned)(index % BIT_STR_BIT_COUNT) - 1;
		return  1 & (sequences_[indexInSequences] >> indexInBitStringFromLow);
	}
}*BitSequence;

/*within free() calling*/
void DestroySequence(BitSequence s);

/*初始化位序列(根据给定长度分配内存)*/
BitSequence InitSequence(unsigned long long length);

/*定长度初始化*/
BitSequence InitSequence();

/*设定序列特定位置比特值*/
void SetBit(BitSequence s, unsigned long long pos, int bit);

/*往比特序列后添加一个比特值*/
void AppendBit(BitSequence s, int bit);

/*设置比特值*/
void SetBit(BitSequence s, unsigned long long pos, char bit);

/*添加比特值*/
void AppendBit(BitSequence s, char bit);

/*字符串创建比特串*/
BitSequence ToBitSequence(std::string s);
BitSequence ToBitSequence(const char* s, unsigned length);

/*从文件流当前定位处读入一个位串*/
BitSequence ReadBitSequenceFromFILE(FILE* fin);

/*写入位串到文件流*/
void WriteBitSequenceToFILE(BitSequence bs, FILE* fout);

/*从位串中转换一个无号数*/
unsigned ConvertAnUnsigned(BitSequence bs, unsigned long long begin, unsigned length);
