//20171015 ���⼮
#pragma once
#include<iostream>
#include<string>


int reverseDigits(int number, int number2 = 0)  //	(658,0)
{
	int a = (int)log10(number);		//number�� �ڸ����� �˱����ؼ� �� �� log10
	int n1 = number; int n2 = number2; int result = 0;
	if (n1 == 0)
	{
		return result;
	}
	n1 /= 10;	//65
	n2 = number % 10;	//8
	result = reverseDigits(n1, n2) + ((n2)*pow(10, a));
	return result;
}

bool isPalindromeInt(int number)
{
	if (number == reverseDigits(number))
	{
		return true;
	}
	else { return false; }
}
std::string reverseString(std::string str)
{
	int a = str.length();
	std::string result;
	if (a == 0)
	{
		return result;
	}
	std::string C = str.substr(a - 1, a); //C�� str�� ���� banana�� �� �� ���� a�����ϰ�
	std::string A = str.erase(a - 1, a);	//�� ���� A�� �� �� ����a�� �� banan�����ؼ�
	result = C + reverseString(A);	//�ǵ� ���� a + n +a +n +a +b�̷������� �ϵ���
	return result;
}
bool isPalindromeString(std::string str)
{
	std::string S = str;
	if (reverseString(S) == str)
	{
		return true;
	}
	else { return false; }

}