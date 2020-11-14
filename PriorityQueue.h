#pragma once
#ifndef PRIORITY_QUEUE_H
#endif
#define PQ_INCRE 21
#include <cstdlib>
#include <iostream>

template<class T>
struct PriorityQueue
{
private:
	T* data_;
	unsigned long long size_;
	int top_;
	void MemoryReallocate() ;
	void swap(int cur1, int cur2);
public:
	PriorityQueue() {
		size_ = sizeof(T) * PQ_INCRE;
		data_ = (T*)malloc(sizeof(T) * PQ_INCRE);
		top_ = 1;
	}
	/*���*/
	void Offer(T e);
	/*����*/
	T Poll();
	
	/*���*///compare: return (is T1 Prior to T2);
	void Offer(T e, int(*compare)(T, T));
	/*����*///compare: return (is T1 Prior to T2);
	T Poll(int(*compare)(T, T));
	/*�鿴����ֵ*/
	T Peek() const;
	/*�п�*/
	int IsEmpty() const;
	/*��*/
	int Length()const {
		return top_ - 1;
	}
	/*����*/
	~PriorityQueue() {
		free(data_);
	}
};

template <class T>
void PriorityQueue<T>::Offer(T e)
{
	int i;
	if (size_ <= sizeof(T) * top_)MemoryReallocate();
	for(i = top_++;i/2>0&&data_[i/2]>e;i/=2)
	{
		data_[i] = data_[i / 2];
	}
	data_[i] = e;
}


template <class T>
T PriorityQueue<T>::Poll()
{
	if (IsEmpty())return NULL;
	T min = data_[1],last = data_[--top_];
	int i, child;
	for(i = 1;i*2<=top_;i = child)
	{
		child = i * 2;
		//����С��
		if (child != top_ && data_[child + 1] < data_[child])
			child++;
		//�������βֵС����С�������ֽڷ���С��
		if (last < data_[child])break;
		//��Ȼ�Ͱ���С���Ź�ȥ
		data_[i] = data_[child];
	}
	data_[i] = last;
	return min;
}

template <class T>
void PriorityQueue<T>::Offer(T e, int(* compare)(T, T))
{
	int i;
	if (size_ <= sizeof(T) * (top_))MemoryReallocate();
	for(i = top_++;i/2>0&&compare(e,data_[i/2]);i/=2)
	{
		data_[i] = data_[i / 2];
	}
	data_[i] = e;
}

template <class T>
T PriorityQueue<T>::Poll(int(* compare)(T, T))
{
	if (IsEmpty())return NULL;
	int i, child;
	T min = data_[1], last = data_[--top_];
	for(i = 1;i*2<=top_;i = child)
	{
		child = i * 2;
		if (child + 1 <= top_ && compare(data_[child + 1], data_[child]))child++;
		if (compare(last, this->data_[child]))break;
		data_[i] = data_[child];
	}
	this->data_[i] = last;
	return min;
}


template <class T>
void PriorityQueue<T>::MemoryReallocate()
{
	size_ = size_ + sizeof(T) * PQ_INCRE;
	T* risk = data_;
	data_ = (T*)realloc(data_, size_);
	if (!data_)data_ = risk;
}

template <class T>
void PriorityQueue<T>::swap(int cur1, int cur2)
{
	T temp = data_[cur1];
	data_[cur1] = data_[cur2];
	data_[cur2] = temp;
}

template <class T>
T PriorityQueue<T>::Peek() const
{
	if (top_ <= 1)return NULL;
	return data_[1];
}

template <class T>
int PriorityQueue<T>::IsEmpty() const
{
	return top_ <= 1;
}
