//kadane.h 定义Kadane类
#pragma once
#ifndef KADANE_H
#define KADANE_H
#include <algorithm>
using namespace std;

class Kadane
{
public:
	static int GetMax(int* array, int length);
	static int Detect(int* array, int length);
protected:
private:
};
#endif 


//kadane.cpp 实现Kadane类
#include "kadane.h"
/*
O(N)算法的思路：从头到尾依次遍历序列中的元素，在当前非负子序列上累加当前元素值，
得到的结果记作tmp_sum。比较tm_sum和当前最大值，如果tmp_sum更大，则将它设置成当前最大值。
判断tmp_sum是否小于0，若是，则表明当前子序列已经变成了负子序列，对随后的子序列和不再有“积极的贡献”了，
所以将tmp_sum重置为0。
*/
// O(n), Kadane's 演算法(dynamic porgramming), 至少取一个数值版本

int Kadane::GetMax(int* array, int length)
{
	int thisSum = Kadane::Detect(array, length);
	if (thisSum < 0)
		return thisSum;
	
	int Result_int = 0;
	for (int i = 0; i < length; i++)
	{
		thisSum += array[i];
		if (thisSum > Result_int)
			Result_int = thisSum;
		else if (thisSum <= 0)
			thisSum = 0;
	}
	return Result_int;
}
/*int Kadane::GetMax(int* array, int length)
{
int sum = Kadane::Detect(array, length);
if (sum < 0)
return sum;
int max_sum = array[0];
for (int i = 0; i < length; ++i)
{
sum += array[i];
sum = max(0, sum);
max_sum = max(sum, max_sum);
}
return max_sum;
}*/
// 测试数组是否全为负数，如果是，则返回值最大的负数，否则，就返回0，从而将thisSum = 0
int Kadane::Detect(int* array, int length)
{
	int max_num = array[0];
	for (int i = 0; i < length; ++i)
	{
		if (array[i] >= 0)
			return 0;
		max_num = max(array[i], max_num);
	}
	return max_num;
}

// kadane.cpp

//  main.cpp   测试程序 find the maximum subsequence 
#include <iostream>
#include <ctime>
#include <random> //random类是C++11中增加的类，该类可以用于生成随机数
#include "kadane.h"

using namespace std;


//该函数接受三个参数分别指定随机数范围和种子，返回int
//产生整型分布的uniform_int_distribution，产生浮点型的分布uniform_real_distribution。
int random_unint(unsigned int min, unsigned int max, unsigned int seed = 0)
{
	static std::default_random_engine e(seed);
	static std::uniform_int_distribution<int> u(min, max);
	return u(e);
}
int main()
{
	
	int n = 100;
	int * array_int = new int[n];

	for (int i = 0; i < 15; ++i) 
	{
		array_int[i] = random_unint(-15, 15, time(NULL));
		cout << "array_int[i]" << array_int[i] << endl;
	}
	
	Kadane MaxSeq;
	int sum = MaxSeq.GetMax(array_int,n);
	cout << "max:" << sum << endl;
  
	return 0;
}


