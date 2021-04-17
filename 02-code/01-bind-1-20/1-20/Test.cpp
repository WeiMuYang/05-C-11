#include <iostream>
#include <functional>

// ����һ������    һ������ָ��  
void call_when_even(int x, const std::function<void(int)>& f)
{
	// & ��ʾ��λ�룬����λ�롱�������ǽ�������������Ӧ��ÿһλ�ֱ���С��߼��롱������
	if (!(x & 1))  // x % 2 == 0  �ж��ǲ���ż�� 
	{
		f(x);    // �����ż���Ļ������ô��ݹ����ĺ���
	}
}

// �������ֵ
void output(int x)
{
	std::cout << x << " ";
}

// �������ֵ��2
void output_add_2(int x)
{
	std::cout << x + 2 << " ";
}

int main(void)
{
	{
		// output��Ҫ���õĺ���   �����Ĳ�������������԰�һ���֣������Ƕ�Ԫ  
		// std::placeholders::_1 ��һ��ռλ����
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