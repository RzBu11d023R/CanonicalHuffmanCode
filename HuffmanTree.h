#pragma once
#include "FrequencyCount.h"
typedef char ElemType;//��������Ϊchar
typedef char ChildFlag;//���������Һ�
#define LChild '0'//��ChildFlag�õ�,�󺢱���0
#define RChild '1'//��ChildFlag�õ�,�Һ�����1
#define ROOT 0 
#define UNKNOWN 1
/*�������������ṹ�嶨��*/
typedef struct huffmanTree {
	int weight;//����ڵ�Ȩֵ
	ElemType val;//����Ҷ�ӵı����ַ�
	ChildFlag whichChild;//��ע�����Һ���
	struct huffmanTree* father;//��¼���׽ڵ�(��˫��Ҳ���ǲ���)
	struct huffmanTree* left, * right;//��¼���Һ���
}*HuffmanTree, * Leaf;//��������


/*����Ҷ�ӽڵ�*/
Leaf CreateLeaf(ElemType val, int weight);

/*�ݹ�������*/
ElemType DestroyTree(HuffmanTree ht);

/*�����ڵ������������*/
HuffmanTree MergeTwoHtree(HuffmanTree t1, HuffmanTree t2);

/*����WPL*/
int CalcWPL(HuffmanTree huffman, int level);

/*��״ͼ��ʾһ�Ź�����������*/
void VisualizeBiTree(HuffmanTree tree, int level);

/*���ɹ�����������*/
HuffmanTree GenerateHuffmanTree(char* charArray, int* weightArray, int count, Leaf*&leafSet );
