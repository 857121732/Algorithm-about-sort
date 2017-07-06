#pragma once

#include<map>
#include<stack>
#include<assert.h>
#include<iostream>
#include<functional>
using namespace std;

// 1.直接插入排序
template<class T, class Compare = less<T>>
void InsertSort(T* array, size_t n)
{
	assert(array != NULL);
	for (size_t index = 1; index < n; ++index)
	{
		int end = index - 1;
		T tmp = array[index];
		while (end >= 0)
		{
			if (Compare()(tmp, array[end]))
				array[end + 1] = array[end];
			else
				break;
			--end;
		}
		array[end + 1] = tmp;
	}
}
// 2.希尔排序
template<class T, class Compare = less<T>>
void ShellSort(T* array, size_t n)
{
	assert(array != NULL);
	size_t group = n;
	while (group > 1)
	{
		group = group / 3 + 1;
		for (size_t index = group; index < n; ++index)
		{
			int end = index - group;
			T tmp = array[index];
			while (end >= 0)
			{
				if (Compare()(tmp, array[end]))
					array[end + group] = array[end];
				else
					break;
				end -= group;
			}
			array[end + group] = tmp;
		}
	}
}
// 3.选择排序
template<class T, class Compare = less<T>>
void SelectSort(T* array, size_t n)
{
	assert(array != NULL);
	for (size_t idx = 0; idx < n; ++idx)
	{
		size_t min = idx;
		for (size_t j = idx + 1; j < n; ++j)
		{
			if (Compare()(array[j], array[min]))
				min = j;
		}
		swap(array[min], array[idx]);
	}
}
// 4.堆排序
template<class T, class Compare = less<T>>
void _AdjustDown(T* array, int n, int root)
{
	int child = root * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && Compare()(array[child], array[child + 1]))
			++child;
		if (Compare()(array[root], array[child]))
			swap(array[root], array[child]);
		root = child;
		child = root * 2 + 1;
	}
}
template<class T, class Compare = less<T>>
void HeapSort(T* array, size_t n)
{
	assert(array != NULL);
	// 1.建堆
	for (int i = (n - 2) / 2; i >= 0; --i)
		_AdjustDown<T, Compare>(array, n, i);
	for (int end = n - 1; end > 0; --end)
	{
		// 2.将堆顶元素放入数组末尾
		swap(array[0], array[end]);
		// 3.将新的堆顶元素进行向下调整
		_AdjustDown<T, Compare>(array, end, 0);
	}
}
// 5.冒泡排序
template<class T, class Compare = less<T>>
void BubbleSort(T* array, size_t n)
{
	assert(array != NULL);
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n - i - 1; ++j)
		{
			if (Compare()(array[j + 1], array[j]))
				swap(array[j + 1], array[j]);
		}
	}
}
// 6.快速排序
template<class T>	// 三数取中
int _GetMid(T* array, int a, int b, int c)
{
	if (array[a] < array[b])
	{
		if (array[c] < array[a])
			return a;
		else if (array[c] > array[b])
			return b;
		else
			return c;
	}
	else
	{
		if (array[c] < array[b])
			return b;
		else if (array[c] > array[a])
			return a;
		else
			return c;
	}
}
template<class T, class Compare>	// a.左右指针法
int _PartSort1(T* array, int left, int right)
{
	int mid = _GetMid(array, left, left + ((right - left) >> 1), right);
	swap(array[right], array[mid]);
	int key = right;
	while (left < right)
	{
		while (left < right && Compare()(array[left], array[key]))
			++left;
		while (left < right && Compare()(array[key], array[right]))
			--right;
		if (left < right)
			swap(array[left], array[right]);
	}
	swap(array[right], array[key]);
	return left;
}
template<class T, class Compare>	// b.挖坑法
int _PartSort2(T* array, int left, int right)
{
	int mid = _GetMid(array, left, left + ((right - left) >> 1), right);
	swap(array[mid], array[right]);
	T key = array[right];
	while (left < right)
	{
		while (left < right && Compare()(array[left], key))
			++left;
		array[right] = array[left];
		while (left < right && Compare()(key, array[right]))
			--right;
		array[left] = array[right];
	}
	array[right] = key;
	return right;
}
template<class T, class Compare>	// c.前后指针法
int _PartSort3(T* array, int left, int right)
{
	int mid = _GetMid(array, left, left + ((right - left) >> 1), right);
	swap(array[mid], array[right]);
	int prev = left - 1;
	while (left < right)
	{
		if (Compare()(array[left], array[right]) && ++prev != left)
			swap(array[prev], array[left]);
		++left;
	}
	swap(array[++prev], array[right]);
	return prev;
}
template<class T, class Compare>
void _InsertSort(T* array, int left, int right)
{
	int cur = left;
	while (++cur <= right)
	{
		T tmp = array[cur];
		int i = cur - 1;
		while(i >= 0 && Compare()(tmp, array[i]))
		{
				array[i + 1] = array[i--];
		}
		array[i + 1] = tmp;
	}
}
template<class T, class Compare = less_equal<T>, int fun = 1>
void QuickSort(T* array, int left, int right)
{
	assert(array != NULL);
	if (left < right)
	{
		if (right - left < 2)
			_InsertSort<T, Compare>(array, left, right);
		else
		{
			int mid = 0;
			switch (fun)
			{
			case 1:
				mid = _PartSort1<T, Compare>(array, left, right);
				break;
			case 2:
				mid = _PartSort2<T, Compare>(array, left, right);
				break;
			case 3:
				mid = _PartSort3<T, Compare>(array, left, right);
				break;
			default:
				break;
			}
			QuickSort<T, Compare>(array, left, mid - 1);
			QuickSort<T, Compare>(array, mid + 1, right);
		}
	}
}
template<class T, class Compare = less_equal<T>, int fun = 1>
void QuickSortNoR(T* array, size_t n)
{
	assert(array != NULL);
	stack<int> s;
	s.push(n - 1);			s.push(0);
	while (!s.empty())
	{
		int left = s.top();	s.pop();
		int right = s.top();	s.pop();
		int mid = 0;
		switch (fun)
		{
		case 1:
			mid = _PartSort1<T, Compare>(array, left, right);
			break;
		case 2:
			mid = _PartSort2<T, Compare>(array, left, right);
			break;
		case 3:
			mid = _PartSort3<T, Compare>(array, left, right);
			break;
		default:
			break;
		}
		if (mid - 1 - left > 0)
		{
			s.push(mid - 1);
			s.push(left);
		}
		if (right - mid - 1 > 0)
		{
			s.push(right);
			s.push(mid + 1);
		}
	}
}
// 7.归并排序
template<class T, class Compare>
void _Merge(T* array, T* tmp, int left, int right)
{	// tmp存放合并的数据
	if (right - left < 1)
		return;	// 无需进行排序
	// 1.递归排序左右两半区间
	int mid = left + ((right - left) >> 1);
	_Merge<T, Compare>(array, tmp, left, mid);
	_Merge<T, Compare>(array, tmp, mid + 1, right);
	// 2.合并左右两个有序区间
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (Compare()(array[begin1], array[begin2]))
			tmp[index++] = array[begin1++];
		else
			tmp[index++] = array[begin2++];
	}
	while (begin1 <= end1)
		tmp[index++] = array[begin1++];
	while (begin2 <= end2)
		tmp[index++] = array[begin2++];
	memcpy(array + left, tmp + left, sizeof(T)*(right - left + 1));
}
template<class T, class Compare = less_equal<T>>
void MergeSort(T* array, size_t n)
{
	assert(array != NULL);
	T* tmp = new T[n];
	_Merge<T, Compare>(array, tmp, 0, n - 1);
	delete[] tmp;
}
// 8.计数排序
template<class T, class Compare = less<T>>
void CountSort(T* array, size_t n)
{
	assert(array != NULL);
	map<T, T, Compare> m;
	for (size_t i = 0; i < n; ++i)
		++m[array[i]];
	map<T, T>::iterator it = m.begin();
	int index = 0;
	while (it != m.end())
	{
		for (int i = 0; i < (*it).second; ++i)
			array[index++] = (*it).first;
		++it;
	}
}
// 9.基数排序
template<class T, class Compare>
size_t GetMaxDigit(T* array, size_t n)
{
	int base = 10;
	size_t max = 1;
	for (size_t i = 0; i < n; ++i)
	{
		while (array[i] >= base)
		{
			++max;
			base *= 10;
		}
	}
	return max;
}
template<class T, class Compare = less<T>>
void BucketSort(T* array, size_t n)
{
	assert(array != NULL);
	T* tmp = new T[n];
	size_t maxDigit = GetMaxDigit<T, Compare>(array, n);
	int base = 1;
	for (size_t i = 0; i < maxDigit; ++i)
	{
		int count[10] = { 0 };
		int start[10] = { 0 };
		// 1.计算当前位每个数字出现的次数
		for (size_t idx = 0; idx < n; ++idx)
			++count[array[idx] / base % 10];
		// 2.计算当前位每个数字起始的位置
		start[0] = 0;
		for (int idx = 1; idx < 10; ++idx)
			start[idx] = count[idx - 1] + start[idx - 1];
		// 3.将数组以当前位有序存放到tmp中
		for (size_t idx = 0; idx < n; ++idx)
			tmp[start[array[idx] / base % 10]++] = array[idx];
		base *= 10;
	}
	memcpy(array, tmp, sizeof(T)*n);
	delete[] tmp;
	if (Compare()(array[n - 1], array[0]))
		reverse(array + 0, array + n);
}

template<class T>
void Print(T* array, size_t n)
{
	for (size_t i = 0; i < n; ++i)
		cout << array[i] << "  ";
	cout << endl;
}

void TestSort()
{
	int a[] = { 2,5,4,9,3,6,8,7,1,0 };

	InsertSort<int>(a, 10);
	Print(a, 10);
	InsertSort<int, greater<int>>(a, 10);
	Print(a, 10);

	ShellSort<int>(a, 10);
	Print(a, 10);
	ShellSort<int, greater<int>>(a, 10);
	Print(a, 10);

	SelectSort<int>(a, 10);
	Print(a, 10);
	SelectSort<int, greater<int>>(a, 10);
	Print(a, 10);

	HeapSort<int>(a, 10);
	Print(a, 10);
	HeapSort<int, greater<int>>(a, 10);
	Print(a, 10);

	BubbleSort<int>(a, 10);
	Print(a, 10);
	BubbleSort<int, greater<int>>(a, 10);
	Print(a, 10);

	QuickSort<int>(a, 0, 9);
	Print(a, 10);
	QuickSort<int, greater_equal<int>>(a, 0, 9);
	Print(a, 10);
	int b = 3;
}
void TestQuickSort()
{
	int a[] = { 2,5,4,9,3,6,8,7,1,9 };
	QuickSort(a, 0, 9);
	Print(a, 10);
	QuickSort<int, greater_equal<int>, 2>(a, 0, 9);
	Print(a, 10);
	QuickSort<int, less_equal<int>, 3>(a, 0, 9);
	Print(a, 10);

	int b[] = { 1,3,5,6,4,2,8,9,0,1 };
	QuickSortNoR(b, 10);
	Print(b, 10);
	QuickSortNoR<int, greater_equal<int>, 2>(b, 10);
	Print(b, 10);
	QuickSortNoR<int, less_equal<int>, 3>(b, 10);
	Print(b, 10);
	int t = 3;
}
void TestMergeSort()
{
	int a[] = { 2,5,4,9,3,6,8,7,1,0 };
	MergeSort(a, 10);
	Print(a, 10);
	MergeSort<int, greater<int>>(a, 10);
	Print(a, 10);
}
void TestCountSort()
{
	int a[] = { 2,5,4,9,3,6,8,7,1,0 };
	CountSort(a, 10);
	Print(a, 10);
	CountSort<int, greater<int>>(a, 10);
	Print(a, 10);
}
void TestBucketSort()
{
	int a[] = { 2,5,4,9,3,6,8,7,1,0 };
	BucketSort(a, 10);
	Print(a, 10);
	BucketSort<int, greater<int>>(a, 10);
	Print(a, 10);
	int b = 3;
}
