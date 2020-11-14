#pragma once
#define CHAR_OFFSET 128
#define BYTE_CHAR_UPPER_LIMIT 256
#include <string>

#include "HuffmanTree.h"

/*范式哈夫曼树结构体(存储)*/
typedef struct canonicalHuffman
{
	char* charSet_;//有限字符集
	unsigned* charCodeLength_;//有限字符对应码长值
	unsigned maximumCodeLength_;//有限码长值最大值
	unsigned length_;//集长
}*CanonicalHuffman;

/*编码匹配表*/
typedef struct encodingMap
{
	std::string* originCodeSet[BYTE_CHAR_UPPER_LIMIT];//以char为index, 非范式树码集
	std::string* canonicalCodeSet[BYTE_CHAR_UPPER_LIMIT];//范式树码集
	/*编码成员函数*/
	std::string* encode(char ch)
	{
		return canonicalCodeSet[ch + CHAR_OFFSET];
	}
}*EncodingMap;

/*解码匹配表*/
typedef struct decodingMap
{
	char* map;//以范式码十进制值为索引
	unsigned* charCodeLength;//马长集
	unsigned maximumLength;//最大码长
	unsigned length;//集长
	/*解码成员函数*/
	char decode(unsigned val)
	{
		return map[val];
	}
}*DecodingMap;

/*need to manually delete c, em, dm*/
void DestroyCanonicalHuffman(CanonicalHuffman c, EncodingMap em, DecodingMap dm);

/*生成范式编码头, charSet:排序后的字符集, length:排序后的非范式码长集*/
CanonicalHuffman GenerateCanonicalHuffman(char* charSet, unsigned* length, unsigned maximumCodeLength, int count);

/*供QuickSort用*/
int compareStringLength(unsigned a, unsigned b);

/*生成范式编码匹配表*/
EncodingMap GenerateEncodingMap(Leaf* leafSet, char* charSet, unsigned*& length, unsigned& maximumCodeLength, int count);

/*生成范式解码匹配表*/
DecodingMap GenerateDecodingMap(CanonicalHuffman c);

/*范式编码头写入文件*/
void WriteHuffmanToFILE(FILE* fout, CanonicalHuffman p);

/*从文件流读入范式编码头*/
CanonicalHuffman ReadHuffmanFromFILE(FILE* fin);

/*生成二进制字符串*/
std::string* GenerateBinaryString(int val, unsigned length);
