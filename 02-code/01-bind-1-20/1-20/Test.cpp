#include <iostream>
#include <functional>

// 传递一个整数    一个函数指针  
void call_when_even(int x, const std::function<void(int)>& f)
{
	// & 表示按位与，“按位与”的作用是将两个操作数对应的每一位分别进行“逻辑与”操作。
	if (!(x & 1))  // x % 2 == 0  判断是不是偶数 
	{
		f(x);    // 如果是偶数的话，调用传递过来的函数
	}
}

// 输出单个值
void output(int x)
{
	std::cout << x << " ";
}

// 输出单个值加2
void output_add_2(int x)
{
	std::cout << x + 2 << " ";
}

int main(void)
{
	{
		// output是要调用的函数   函数的参数，参数表可以绑定一部分，可以是多元  
		// std::placeholders::_1 是一个占位符，
		auto fr = std::bind(output, std::placeholders::_1);
		for (int i = 0; i < 10; ++i)
		{
			call_when_even(i, fr);
		}

		std::cout << std::endl;
	}
	{
	auto fr = std::bind(output_add_2, std::placeholders::_1);

	for (int i = 0; i < 10; ++i)
	{
		call_when_even(i, fr);
	}
	std::cout << std::endl;
}
	system("pause");
	return 0;
}