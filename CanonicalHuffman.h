#pragma once
#define CHAR_OFFSET 128
#define BYTE_CHAR_UPPER_LIMIT 256
#include <string>

#include "HuffmanTree.h"

/*��ʽ���������ṹ��(�洢)*/
typedef struct canonicalHuffman
{
	char* charSet_;//�����ַ���
	unsigned* charCodeLength_;//�����ַ���Ӧ�볤ֵ
	unsigned maximumCodeLength_;//�����볤ֵ���ֵ
	unsigned length_;//����
}*CanonicalHuffman;

/*����ƥ���*/
typedef struct encodingMap
{
	std::string* originCodeSet[BYTE_CHAR_UPPER_LIMIT];//��charΪindex, �Ƿ�ʽ���뼯
	std::string* canonicalCodeSet[BYTE_CHAR_UPPER_LIMIT];//��ʽ���뼯
	/*�����Ա����*/
	std::string* encode(char ch)
	{
		return canonicalCodeSet[ch + CHAR_OFFSET];
	}
}*EncodingMap;

/*����ƥ���*/
typedef struct decodingMap
{
	char* map;//�Է�ʽ��ʮ����ֵΪ����
	unsigned* charCodeLength;//����
	unsigned maximumLength;//����볤
	unsigned length;//����
	/*�����Ա����*/
	char decode(unsigned val)
	{
		return map[val];
	}
}*DecodingMap;

/*need to manually delete c, em, dm*/
void DestroyCanonicalHuffman(CanonicalHuffman c, EncodingMap em, DecodingMap dm);

/*���ɷ�ʽ����ͷ, charSet:�������ַ���, length:�����ķǷ�ʽ�볤��*/
CanonicalHuffman GenerateCanonicalHuffman(char* charSet, unsigned* length, unsigned maximumCodeLength, int count);

/*��QuickSort��*/
int compareStringLength(unsigned a, unsigned b);

/*���ɷ�ʽ����ƥ���*/
EncodingMap GenerateEncodingMap(Leaf* leafSet, char* charSet, unsigned*& length, unsigned& maximumCodeLength, int count);

/*���ɷ�ʽ����ƥ���*/
DecodingMap GenerateDecodingMap(CanonicalHuffman c);

/*��ʽ����ͷд���ļ�*/
void WriteHuffmanToFILE(FILE* fout, CanonicalHuffman p);

/*���ļ������뷶ʽ����ͷ*/
CanonicalHuffman ReadHuffmanFromFILE(FILE* fin);

/*���ɶ������ַ���*/
std::string* GenerateBinaryString(int val, unsigned length);
