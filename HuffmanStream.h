#pragma once
#include "BitStream.h"
#include "CanonicalHuffman.h"

typedef struct huffmanFile
{
	CanonicalHuffman canonical;
	DecodingMap decodingMap;
	EncodingMap encodingMap;
	BitSequence sequences;
	FrequencyTable frequency;
	HuffmanTree tree;
}*HuffmanFile,*HuffmanStream;

void Encoding(FILE* fin, FILE* fout);

void Decoding(FILE* fin, FILE* fout);

/*creator should delete or free the parameter*/
void DestroyHuffmanFileContent(HuffmanFile file);