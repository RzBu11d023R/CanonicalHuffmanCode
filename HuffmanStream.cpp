#include "HuffmanStream.h"
#include "FrequencyCount.h"
#define BUFFER_INCRE 100
void Encoding(FILE* fin, FILE* fout) {
	HuffmanFile file = new huffmanFile();
	unsigned long long length = 0;
	unsigned long long bufferMemorySize = sizeof(char) * BUFFER_INCRE;
	char* buffer = (char*)malloc(bufferMemorySize);
	std::cout << "Reading File..." << std::endl;//HINT
	while (fread(buffer + length, sizeof(char), 1, fin) == 1) {
		if ((length + 1) * sizeof(char) >= bufferMemorySize) {
			bufferMemorySize += BUFFER_INCRE * sizeof(char);
			buffer = (char*)realloc(buffer, bufferMemorySize);
		}
		length++;
	}
	std::cout << "File Read!" << std::endl;//HINT
	std::cout << "Calculating Character Frequency..." << std::endl;//HINT
	file->frequency = BuildTable(buffer, length);
	std::cout << "Character Frequency Calculating Finished!" << std::endl;//HINT
	char* charSet; int* weightSet; const int charCount = file->frequency->length;
	GetCharSet(file->frequency, charSet, weightSet);
	Leaf* leafSet;
	std::cout << "Generating Huffman Tree..." << std::endl;//HINT
	file->tree = GenerateHuffmanTree(charSet, weightSet, charCount, leafSet);
	std::cout << "Huffman Tree Generating Finished!\nTree Viewing:" << std::endl;//HINT
	VisualizeBiTree(file->tree,0);
	unsigned* lengthSet;
	unsigned maxCodeLength;
	std::cout << "Generating Canonical Huffman Code...\n";//HINT
	file->encodingMap = GenerateEncodingMap(leafSet, charSet, lengthSet, maxCodeLength, charCount);
	file->canonical = GenerateCanonicalHuffman(charSet, lengthSet, maxCodeLength, charCount);
	std::cout << "Encoding..." << std::endl;//HINT
	std::string zeroOneString = "";
	for (unsigned long long traverseIndex = 0; traverseIndex < length; traverseIndex++) {
		zeroOneString = zeroOneString.append(*(file->encodingMap->encode(buffer[traverseIndex])));
	}
	file->sequences = ToBitSequence(zeroOneString);
	std::cout << "Writing File...\nStoring Huffman Code File Head..." << std::endl;//HINT
	WriteHuffmanToFILE(fout, file->canonical);
	std::cout << "Writing Data..\n";//HINT
	WriteBitSequenceToFILE(file->sequences, fout);
	std::cout << "Clearing memory...\n";//HINT
	DestroyHuffmanFileContent(file);
	delete(file);
}

void Decoding(FILE* fin, FILE* fout)
{
	HuffmanFile f = new huffmanFile();
	f->canonical = ReadHuffmanFromFILE(fin);
	BitSequence bs = f->sequences = ReadBitSequenceFromFILE(fin);
	DecodingMap dm = f->decodingMap = GenerateDecodingMap(f->canonical);
	const unsigned maxCodeLength = f->canonical->maximumCodeLength_;
	for(unsigned long long i = 0; i < f->sequences->stringLength_;) {
		const unsigned val = ConvertAnUnsigned(bs, i, maxCodeLength);
		char ch = dm->decode(val);
		fwrite(&ch, sizeof(char), 1, fout);
		i += dm->charCodeLength[val];
	}
	DestroyHuffmanFileContent(f);
	delete(f);
}

void DestroyHuffmanFileContent(HuffmanFile file)
{
	if (!file)return;
	DestroyCanonicalHuffman(file->canonical, file->encodingMap, file->decodingMap);
	delete file->canonical;
	delete file->decodingMap;
	delete file->encodingMap;
	if (file->sequences)DestroySequence(file->sequences);
	if (file->frequency)DestroyTable(file->frequency);
	if (file->tree)DestroyTree(file->tree);
}
