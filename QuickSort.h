#pragma once
#define BIG_SCALE 16
template<class T>
/*快排分区函数, cmp: T1<=T2*/
int partition(T* data, int low, int high, int(*cmp)(T, T)) {
	T pivot;
	int index=high;
	if (high - low >= BIG_SCALE) {
		T a = data[low], b = data[low + (high - low) / 2], c = data[high];
		if (cmp(a, b) && cmp(b, c)) {
			pivot = b;
			data[low + (high - low) / 2] = data[high];
		}
		else if (cmp(a, c) && cmp(c, b))
			pivot = c;
		else {
			pivot = a;
			data[low] = data[high];
		}
	}
	else pivot = data[high];
	while(low<high)
	{
		while (low < high && cmp(data[low], pivot))low++;
		if (low < high)
		{
			data[index] = data[low];
			index = low;
		}
		while (low < high && cmp(pivot, data[high]))high--;
		if(low<high)
		{
			data[index] = data[high];
			index = high;
		}
		
	}
	data[index] = pivot;
	return index;
}
template<class T>
/*快排, 使用递归, 需要使用左闭右闭区间*/
void QuickSort(T* data, int low, int high,int(*cmp)(T,T))//[low,high]
{
	if (low >= high)return;
	int s = partition(data, low, high,cmp);
	QuickSort(data, low, s - 1,cmp);
	QuickSort(data, s+1, high,cmp);
}

template<class T,class S>
int partition(T* data,S* satelite, int low, int high, int(*cmp)(T, T)) {
	T pivot; S spivot;
	int index = high;
	//选择中位数来做pivot值, 趋近平均复杂度O(nlogn)
	if (high - low >= BIG_SCALE) {
		T a = data[low], b = data[low + (high - low) / 2], c = data[high];
		if (cmp(a, b) && cmp(b, c)) {
			pivot = b;
			spivot = satelite[low + (high - low) / 2];
			satelite[low + (high - low) / 2] = satelite[high];
			data[low + (high - low) / 2] = data[high];
		}
		else if (cmp(a, c) && cmp(c, b)) { pivot = c; spivot = satelite[high]; }
		else {
			pivot = a;
			spivot = satelite[low];
			satelite[low] = satelite[high];
			data[low] = data[high];
		}
	}
	else { pivot = data[high]; spivot = satelite[high]; }
	while(low<high)
	{
		while (low < high && cmp(data[low], pivot))low++;
		if (low < high)
		{
			data[index] = data[low];
			satelite[index] = satelite[low];
			index = low;
		}
		while (low < high && cmp(pivot, data[high]))high--;
		if(low<high)
		{
			data[index] = data[high];
			satelite[index] = satelite[high];
			index = high;
		}
		
	}
	satelite[index] = spivot;
	data[index] = pivot;
	return index;
}
template<class T,class S>
/*快排, data为基准数据数组, satelite为卫星数据,使用递归, 需要使用左闭右闭区间*/
void QuickSort(T* data, S* satelite, int low, int high,int(*cmp)(T,T))//[low,high]
{
	if (low >= high)return;
	int s = partition(data, satelite,low, high,cmp);
	QuickSort(data,satelite, low, s - 1,cmp);
	QuickSort(data,satelite, s+1, high,cmp);
}