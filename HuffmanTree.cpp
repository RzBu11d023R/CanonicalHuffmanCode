#pragma once
#include<iostream>
#include "Stack.h"
#include "HuffmanTree.h"
#include "PriorityQueue.h"

/* �������ȶ���(��������ʵ��)�ı�����Ϊɭ��
 */
typedef PriorityQueue<HuffmanTree>* Forest;

/*����һ��Ҷ�ӽڵ�(��ʼ״̬ΪҶ�ӵĽڵ�)*/
Leaf CreateLeaf(ElemType val, int weight) {
	struct huffmanTree* ht = (HuffmanTree)malloc(sizeof(struct huffmanTree));
	if (!ht)return ht;
	ht->left = nullptr;
	ht->right = nullptr;
	ht->val = val;
	ht->weight = weight;
	ht->whichChild = UNKNOWN;
	ht->father = NULL;
	return ht;
}
/*�ݹ�����һ��HuffmanTree*/
ElemType DestroyTree(HuffmanTree ht) {
	if (ht->left != nullptr) {
		DestroyTree(ht->left);
	}
	if (ht->right != nullptr) {
		DestroyTree(ht->right);
	}
	ElemType v = ht->val;
	free(ht);
	return v;
}
/*�ϲ��������ڵ㷵��һ����Ҷ�ӽڵ�,ͬʱ��Ǹ���*/
HuffmanTree MergeTwoHtree(HuffmanTree t1, HuffmanTree t2) {
	if (!t1 || !t2)return nullptr;
	HuffmanTree ht = (HuffmanTree)malloc(sizeof(struct huffmanTree));
	if (!ht)return ht;
	ht->weight = t1->weight + t2->weight;
	if (t1->weight <= t2->weight) {
		ht->left = t1;
		t1->father = ht;
		t1->whichChild = LChild;
		ht->right = t2;
		t2->father = ht;
		t2->whichChild = RChild;
	}
	else {
		ht->left = t2;
		t2->father = ht;
		t2->whichChild = LChild;
		ht->right = t1;
		t1->father = ht;
		t1->whichChild = RChild;
	}
	ht->father = NULL;
	ht->whichChild = UNKNOWN;
	return ht;
}

/*����һ�Ź���������WPL(��Ȩ·�����Ⱥ�)(�ݹ�)*/
int CalcWPL(HuffmanTree huffman, int level) {
	if (huffman->left == NULL && huffman->right == NULL) return huffman->weight * level;
	return CalcWPL(huffman->left, level + 1) + CalcWPL(huffman->right, level + 1);
}
int compareWeight(HuffmanTree h1, HuffmanTree h2)
{
	return h1->weight < h2->weight;
}
/*���庯������*/
Forest CreateForest() { return new PriorityQueue<Leaf>; }
/*�������Ŀ��ӻ�,�ݹ��ӡ(������ͼ����ʽ)*/
void VisualizeBiTree(HuffmanTree tree, int level) {
	if (!tree)return;
	if (level == 0)std::cout << "[ROOT].";
	std::cout << "weight:" << tree->weight;
	if (!tree->left && !tree->right)std::cout << ",val:" << tree->val;
	std::cout << "\n";
	if (tree->left) {
		for (int i = 0; i < level; i++)std::cout << "    "; std::cout << "----";
		std::cout << "[L].";
	}
	VisualizeBiTree(tree->left, level + 1);
	if (tree->right) {
		for (int i = 0; i < level; i++)std::cout << "    "; std::cout << "----";
		std::cout << "[R].";
	}
	VisualizeBiTree(tree->right, level + 1);
}
/* ��ȡһ�Ź�������,���д������Ϊ�����ַ���,��Ӧ�ַ�Ȩֵ,��Ŀ, �Լ�һ�����봮��������
 * ע��: leafSet���������е�Ҷ�ӽڵ�.
 */
HuffmanTree GenerateHuffmanTree(char* charArray, int* weightArray, int count, Leaf *&leafSet) {
	Forest forest = CreateForest();
	leafSet = (HuffmanTree*)malloc(sizeof(HuffmanTree) * count);//���ڼ�¼���е�Ҷ�ӽڵ㷽�����
	//����Ҷ�ӽڵ㲢���뵽��Ȩֵ��������ȶ���forest��,
	for (int i = 0; i < count; i++) {
		HuffmanTree ht = CreateLeaf(charArray[i], weightArray[i]);
		leafSet[i] = ht;
		forest->Offer(ht,compareWeight);
	}
	//���ݹ������������㷨, ��ʼɭ��ȫ�Ƕ�Ӧ�ַ���Ҷ�ӽڵ�
	//ÿ��ɭ�����д���1���ڵ�ʱ, ȡ������С�Ľڵ�
	//����merge�󷵻�ɭ����
	while (forest->Length()>1) {
		HuffmanTree min1 = forest->Poll(compareWeight);
		HuffmanTree min2 = forest->Poll(compareWeight);
		huffmanTree* merge = (HuffmanTree)malloc(sizeof(huffmanTree));
		merge = MergeTwoHtree(min1, min2);
		forest->Offer(merge, compareWeight);
	}
	//���ɭ����ʣ�µľ���һ�Ŷ�����, ����Ŷ������ǹ�������
	HuffmanTree result = forest->Poll(compareWeight);
	//�ͷ�ɭ��
	delete forest;
	//���ع�������
	return result;
}


