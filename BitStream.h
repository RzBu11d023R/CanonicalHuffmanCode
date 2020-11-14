#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
typedef unsigned long BitString;
#define BIT_STR_BYTE_COUNT sizeof(BitString)
#define BIT_STR_BIT_COUNT (sizeof(BitString)*8)

/*λ���ṹ�嶨��*/
typedef struct bitSequence {
	//���ش��ĵ�λ����,ÿһ����λ��BIT_STR_BIT_COUNT������---
	BitString* sequences_;
	unsigned int arrayLength_;//ָ����ǰ���ش���λ���鳤��
	unsigned long long stringLength_;//ָ�����ش��ĳ���
	unsigned long long size_;//��¼sequences_�����ڴ��С
	/*��ȡλ���ڲ���λ*/
	unsigned operator[](unsigned long long index) const {
		if (index >= stringLength_)return 0;
		const unsigned indexInSequences = (unsigned)(index / BIT_STR_BIT_COUNT);
		const unsigned indexInBitStringFromLow = BIT_STR_BIT_COUNT - (unsigned)(index % BIT_STR_BIT_COUNT) - 1;
		return  1 & (sequences_[indexInSequences] >> indexInBitStringFromLow);
	}
}*BitSequence;

/*within free() calling*/
void DestroySequence(BitSequence s);

/*��ʼ��λ����(���ݸ������ȷ����ڴ�)*/
BitSequence InitSequence(unsigned long long length);

/*�����ȳ�ʼ��*/
BitSequence InitSequence();

/*�趨�����ض�λ�ñ���ֵ*/
void SetBit(BitSequence s, unsigned long long pos, int bit);

/*���������к����һ������ֵ*/
void AppendBit(BitSequence s, int bit);

/*���ñ���ֵ*/
void SetBit(BitSequence s, unsigned long long pos, char bit);

/*��ӱ���ֵ*/
void AppendBit(BitSequence s, char bit);

/*�ַ����������ش�*/
BitSequence ToBitSequence(std::string s);
BitSequence ToBitSequence(const char* s, unsigned length);

/*���ļ�����ǰ��λ������һ��λ��*/
BitSequence ReadBitSequenceFromFILE(FILE* fin);

/*д��λ�����ļ���*/
void WriteBitSequenceToFILE(BitSequence bs, FILE* fout);

/*��λ����ת��һ���޺���*/
unsigned ConvertAnUnsigned(BitSequence bs, unsigned long long begin, unsigned length);
