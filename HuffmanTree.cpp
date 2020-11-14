#pragma once
#include<iostream>
#include "Stack.h"
#include "HuffmanTree.h"
#include "PriorityQueue.h"

/* 定义优先队列(数组二叉堆实现)的别名作为森林
 */
typedef PriorityQueue<HuffmanTree>* Forest;

/*创建一个叶子节点(初始状态为叶子的节点)*/
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
/*递归销毁一颗HuffmanTree*/
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
/*合并两个树节点返回一个非叶子节点,同时标记父亲*/
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

/*计算一颗哈夫曼树的WPL(带权路径长度和)(递归)*/
int CalcWPL(HuffmanTree huffman, int level) {
	if (huffman->left == NULL && huffman->right == NULL) return huffman->weight * level;
	return CalcWPL(huffman->left, level + 1) + CalcWPL(huffman->right, level + 1);
}
int compareWeight(HuffmanTree h1, HuffmanTree h2)
{
	return h1->weight < h2->weight;
}
/*定义函数别名*/
Forest CreateForest() { return new PriorityQueue<Leaf>; }
/*二叉树的可视化,递归打印(以树型图的形式)*/
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
/* 获取一颗哈夫曼树,其中传入参数为编码字符集,对应字符权值,数目, 以及一个编码串序列引用
 * 注解: leafSet将返回所有的叶子节点.
 */
HuffmanTree GenerateHuffmanTree(char* charArray, int* weightArray, int count, Leaf *&leafSet) {
	Forest forest = CreateForest();
	leafSet = (HuffmanTree*)malloc(sizeof(HuffmanTree) * count);//用于记录所有的叶子节点方便编码
	//创建叶子节点并加入到按权值排序的优先队列forest中,
	for (int i = 0; i < count; i++) {
		HuffmanTree ht = CreateLeaf(charArray[i], weightArray[i]);
		leafSet[i] = ht;
		forest->Offer(ht,compareWeight);
	}
	//根据哈夫曼树生成算法, 初始森林全是对应字符的叶子节点
	//每当森林中有大于1个节点时, 取两个最小的节点
	//进行merge后返回森林中
	while (forest->Length()>1) {
		HuffmanTree min1 = forest->Poll(compareWeight);
		HuffmanTree min2 = forest->Poll(compareWeight);
		huffmanTree* merge = (HuffmanTree)malloc(sizeof(huffmanTree));
		merge = MergeTwoHtree(min1, min2);
		forest->Offer(merge, compareWeight);
	}
	//最后森林中剩下的就是一颗二叉树, 而这颗二叉树是哈夫曼树
	HuffmanTree result = forest->Poll(compareWeight);
	//释放森林
	delete forest;
	//返回哈夫曼树
	return result;
}


