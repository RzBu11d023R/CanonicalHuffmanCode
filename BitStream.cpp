#include "BitStream.h"

#include <iostream>
#define BIT_SEQUENCE_INCRE 100

void DestroySequence(BitSequence s)
{
	if (s->sequences_)free(s->sequences_);
	free(s);
}

void MemoryReallocate(BitSequence s)
{
	size_t cur = s->size_;
	size_t ca = BIT_STR_BYTE_COUNT * (BIT_SEQUENCE_INCRE / BIT_STR_BIT_COUNT);
	s->size_ +=ca;
	s->sequences_ = (BitString*)realloc(s->sequences_,s->size_);
	memset(s->sequences_ + cur/BIT_STR_BYTE_COUNT,0,ca);
}

BitSequence InitSequence(unsigned long long length) {
	BitSequence s = (BitSequence)malloc(sizeof(struct bitSequence));
	unsigned long long size;
	if (length > BIT_STR_BIT_COUNT)
	{
		size = length / BIT_STR_BIT_COUNT;
		if (length % BIT_STR_BIT_COUNT != 0)size += 1;
	}
	else size = 1;
	if (s == NULL)return NULL;
	s->arrayLength_ = (unsigned int)size;
	size *= BIT_STR_BYTE_COUNT;
	s->sequences_ = (BitString*)malloc(size);
	s->size_ = size;
	s->stringLength_ = 0;
	memset(s->sequences_, 0, size);
	return s;
}

BitSequence InitSequence() {
	return InitSequence(BIT_SEQUENCE_INCRE);
}

void SetBit(BitSequence s, unsigned long long pos, int bit) {
	if (pos >= s->stringLength_)s->stringLength_ = pos + 1;
	unsigned int indexInSequences = (unsigned int)(pos / BIT_STR_BIT_COUNT);
	unsigned int posInBitString = (unsigned int)(pos % BIT_STR_BIT_COUNT);
	if(indexInSequences*BIT_STR_BYTE_COUNT>=s->size_)
	{
		MemoryReallocate(s);
	}
	BitString operate;
	if(!bit)
	{
		operate =  ~(1 <<(BIT_STR_BIT_COUNT- posInBitString-1));
		s->sequences_[indexInSequences] &= operate;
	}
	else {
		operate = 0 | (1 <<(BIT_STR_BIT_COUNT- posInBitString-1));
		s->sequences_[indexInSequences]|= operate;
	}
}

void AppendBit(BitSequence s, int bit)
{
	unsigned long long pos = s->stringLength_;
	if (bit)
		SetBit(s, pos, bit);
	else s->stringLength_++;
}

inline void SetBit(BitSequence s, unsigned long long pos, char bit)
{
	SetBit(s, pos, bit == '1');
}

void AppendBit(BitSequence s, char bit)
{
	AppendBit(s, bit == '1');
}

BitSequence ReadBitSequenceFromFILE(FILE* fin)
{
	BitSequence bs = InitSequence();
	fread(&bs->stringLength_, sizeof(unsigned long long), 1, fin);
	bs->arrayLength_ = 0;
	while (1 == fread(bs->sequences_+bs->arrayLength_, BIT_STR_BYTE_COUNT, 1, fin)) {
		bs->arrayLength_++;
		if(bs->arrayLength_*BIT_STR_BYTE_COUNT>=bs->size_)
		{
			MemoryReallocate(bs);
		}
	}
	return bs;
}

void WriteBitSequenceToFILE(BitSequence bs, FILE* fout)
{
	fwrite(&bs->stringLength_, sizeof(unsigned long long), 1, fout);
	for(unsigned i = 0;i<bs->stringLength_/BIT_STR_BIT_COUNT+1;i++)
	{
		fwrite(bs->sequences_+i, BIT_STR_BYTE_COUNT, 1, fout);
	}
}

unsigned ConvertAnUnsigned(BitSequence bs, unsigned long long begin, unsigned length)
{
	unsigned result = 0;
	if (length + begin >= bs->arrayLength_ * BIT_STR_BIT_COUNT) {
		MemoryReallocate(bs);
	}
	for (unsigned i = 0; i < length; i++) {
		result *= 2;
		result += (*bs)[i + begin];
	}
	return result;
}


BitSequence ToBitSequence(std::string s)
{
	return ToBitSequence(s.c_str(),s.length());
}

BitSequence ToBitSequence(const char* s,unsigned length)
{
	BitSequence bs = InitSequence(length);
	for(unsigned  i = 0;i<length;i++)
	{
		AppendBit(bs, s[i]);
	}
	return  bs;
}
