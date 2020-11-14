#include "CanonicalHuffman.h"

#include "QuickSort.h"

void DestroyCanonicalHuffman(CanonicalHuffman c, EncodingMap em, DecodingMap dm) {
	for (unsigned i = 0; i < c->length_; i++) {
		const char ch = c->charSet_[i];
		const unsigned id = ch + CHAR_OFFSET; if (em) {
			delete em->canonicalCodeSet[id];
			delete em->originCodeSet[id];
		}
	}if (dm) {
		free(dm->map);
		free(dm->charCodeLength);
	}
	if (c->charSet_)free(c->charSet_);
	if (c->charCodeLength_)free(c->charCodeLength_);
}

CanonicalHuffman GenerateCanonicalHuffman(char* charSet, unsigned* length, unsigned maximumCodeLength, int count) {
	CanonicalHuffman can = new canonicalHuffman;
	can->charCodeLength_ = length;
	can->maximumCodeLength_ = maximumCodeLength;
	can->charSet_ = charSet;
	can->length_ = count;
	return can;
}

int compareStringLength(unsigned a, unsigned b) {
	return a <= b;
}
EncodingMap GenerateEncodingMap(Leaf* leafSet, char* charSet, unsigned*& length, unsigned& maximumCodeLength, int count) {
	EncodingMap e = new encodingMap();
	unsigned* lengthSet = (unsigned*)malloc(sizeof(unsigned) * count);
	length = lengthSet;
	std::string** codeSet = e->originCodeSet;
	//计算所有字符的编码结果存到codeSet中
	//由于数据结构中定义了father和whichChild, 自底向上构建编码串
	for (int i = 0; i < count; i++) {
		//从leafSet中获取对应的叶子节点
		Leaf leaf = leafSet[i];
		unsigned index = (unsigned)(leaf->val + CHAR_OFFSET);
		codeSet[index] = new std::string("");
		//自底向上构建编码串
		while (leaf->father) {
			*codeSet[index] = leaf->whichChild + *codeSet[index];
			leaf = leaf->father;
		}
		//保存编码串
		lengthSet[i] = (unsigned)codeSet[index]->length();
	}
	QuickSort<unsigned, char>(lengthSet, charSet, 0, count - 1, compareStringLength);
	codeSet = e->canonicalCodeSet;
	int currentCode = 0;
	unsigned prelength = 0;
	maximumCodeLength = 0;
	for (int i = 0; i < count; i++) {
		unsigned currentLength = lengthSet[i];
		char ch = charSet[i];
		currentCode = currentCode << (currentLength - prelength);
		codeSet[ch + CHAR_OFFSET] = GenerateBinaryString(currentCode, currentLength);
		maximumCodeLength = maximumCodeLength < currentLength ? currentLength : maximumCodeLength;
		currentCode++;
		prelength = currentLength;
	}
	return e;
}

DecodingMap GenerateDecodingMap(CanonicalHuffman c) {
	DecodingMap m = new decodingMap();
	unsigned memoryCount = 1;
	m->maximumLength = c->maximumCodeLength_;
	for (unsigned i = 0; i < m->maximumLength; i++)memoryCount *= 2;
	m->map = (char*)malloc(memoryCount * sizeof(char));
	m->charCodeLength = (unsigned*)malloc(memoryCount * sizeof(unsigned));
	unsigned maxLength = m->maximumLength;
	unsigned charIndex, decodeIndex = 0;
	for (charIndex = 0; charIndex < c->length_; charIndex++) {
		unsigned repeatTimes = 1;
		for (unsigned i = 0;
			i < maxLength - c->charCodeLength_[charIndex];
			i++) repeatTimes *= 2;
		for (unsigned repeatIndex = 0; repeatIndex < repeatTimes;
			repeatIndex++) {
			m->map[decodeIndex] = c->charSet_[charIndex];
			m->charCodeLength[decodeIndex++] = c->charCodeLength_[charIndex];
		}
	}
	m->length = decodeIndex;
	return m;
}

void WriteHuffmanToFILE(FILE* fout, CanonicalHuffman p) {
	fwrite(&p->length_, sizeof(unsigned), 1, fout);
	fwrite(p->charSet_, sizeof(char), p->length_, fout);
	fwrite(p->charCodeLength_, sizeof(unsigned), p->length_, fout);
	fwrite(&p->maximumCodeLength_, sizeof(unsigned), 1, fout);
}

CanonicalHuffman ReadHuffmanFromFILE(FILE* fin) {
	CanonicalHuffman p = new canonicalHuffman();
	fread(&p->length_, sizeof(unsigned), 1, fin);
	p->charSet_ = (char*)malloc(sizeof(char) * p->length_);
	p->charCodeLength_ = (unsigned*)malloc(sizeof(unsigned) * p->length_);
	if (!p->charSet_ || !p->charCodeLength_)return NULL;
	fread(p->charSet_, sizeof(char), p->length_, fin);
	fread(p->charCodeLength_, sizeof(unsigned), p->length_, fin);
	fread(&p->maximumCodeLength_, sizeof(unsigned), 1, fin);
	return p;
}

std::string* GenerateBinaryString(int val, unsigned length) {
	std::string* result = new std::string("");
	while (val != 0) {
		*result = (result->insert(0, 1, ((val % 2) + '0')));
		val /= 2;
	}
	*result = (result->insert(0, length - result->length(), '0'));
	return result;
}
