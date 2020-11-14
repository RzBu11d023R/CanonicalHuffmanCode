#pragma once
#include "FrequencyCount.h"
typedef char ElemType;//编码类型为char
typedef char ChildFlag;//定义是左孩右孩
#define LChild '0'//给ChildFlag用的,左孩编码0
#define RChild '1'//给ChildFlag用的,右孩编码1
#define ROOT 0 
#define UNKNOWN 1
/*哈夫曼二叉树结构体定义*/
typedef struct huffmanTree {
	int weight;//定义节点权值
	ElemType val;//定义叶子的编码字符
	ChildFlag whichChild;//备注是左右孩子
	struct huffmanTree* father;//记录父亲节点(叫双亲也不是不行)
	struct huffmanTree* left, * right;//记录左右孩子
}*HuffmanTree, * Leaf;//别名声明


/*创建叶子节点*/
Leaf CreateLeaf(ElemType val, int weight);

/*递归销毁树*/
ElemType DestroyTree(HuffmanTree ht);

/*创建节点包含两颗子树*/
HuffmanTree MergeTwoHtree(HuffmanTree t1, HuffmanTree t2);

/*计算WPL*/
int CalcWPL(HuffmanTree huffman, int level);

/*树状图显示一颗哈夫曼二叉树*/
void VisualizeBiTree(HuffmanTree tree, int level);

/*生成哈夫曼二叉树*/
HuffmanTree GenerateHuffmanTree(char* charArray, int* weightArray, int count, Leaf*&leafSet );
