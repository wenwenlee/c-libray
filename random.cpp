//main1.cpp 采用srand和rand方式
#include <iostream>
#include <cstdlib>
#include <ctime>

//random num range is min to max, template function
template <typename T> T cRandom(int min, int max)
{
	return (min + static_cast<T>(max * rand() / static_cast<T>(RAND_MAX + 1)));
}

int main(void)
{
	srand((unsigned)time(NULL));
	//生成10个整数
	std::cout << "int: " << std::endl;
	for (int i = 0; i < 10; ++i) {
		std::cout << cRandom<int>(1, 15) << " ";
	}
	std::cout << std::endl;
	//生成10个小数
	std::cout << "double: " << std::endl;
	for (int i = 0; i < 10; ++i) {
		std::cout << cRandom<double>(1, 15) << " ";
	}
	std::cout << std::endl;
	return 0;
}

/*
生成指定范围的随机数表达式：
要取得[a,b)的随机整数，使用(rand() % (b-a))+ a;
要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a;
要取得(a,b]的随机整数，使用(rand() % (b-a))+ a + 1;
通用公式:a + rand() % n；其中的a是起始值，n是整数的范围。
要取得a到b之间的随机整数，另一种表示：a + (int)b * rand() / (RAND_MAX + 1)。
要取得0～1之间的浮点数，可以使用rand() / double(RAND_MAX)。
*/

//main2.cpp 采用random方式
#include <random>
#include <iostream>
#include <ctime>

//该函数接受三个参数分别指定随机数范围和种子，返回double
double random_unint(unsigned int min, unsigned int max, unsigned int seed = 0)
{
    static std::default_random_engine e(seed);
    static std::uniform_real_distribution<double> u(min, max);
    return u(e);
}

int main(void)
{
    for (int i = 0; i < 15; ++i) {
        std::cout << random_unint(0, 15, time(NULL)) << " ";
    }
    std::cout << std::endl;
    return 0;
}

/*
random中定义了多种随机数引擎及分布类型，
常用的引擎是默认伪随机数引擎类default_random_engine，
常用的分布类有产生整型分布的uniform_int_distribution，
产生浮点型的分布uniform_real_distribution。
*/
