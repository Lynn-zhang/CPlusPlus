//дʱ�������Ż���

#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<assert.h>

class String
{
public:
	String(char* str = "")    //����strlen��NULL��
	{
		_str = new char[strlen(str) + 5];
		_str += 4;
		strcpy(_str, str);
		GetRefCount(_str) = 1;
	}
	String(const String &s)
	{
		_str = s._str;
		++GetRefCount(_str);
	}

	//Ҫ������s1=s2ʱ��s1ԭ�Ȳ�Ϊ�յ������Ҫ���ͷ�ԭ�ڴ�
	//���Ҫ�ͷ�ԭ�ڴ�ʱ��Ҫ��������_refCount��1���Ƿ�Ϊ0��Ϊ�����ͷţ�������������ָ���޷��ٷ�����Ƭ�ռ�
	String& operator=(String& s)
	{
		if (this != &s)
		{
			if (GetRefCount(_str ) == 1)
			{
				delete (_str-4);
				_str = s._str;
				++GetRefCount(_str );
			}
			else
			{
				--GetRefCount(_str );
				_str = s._str;
				++GetRefCount(_str );
			}
		}
		return *this;
	}
	//����޸����ַ��������ݣ�������ָ������ڴ�Ķ���ָ������ݼ�ӱ��ı�
	//�����������ָ��ָ������ڴ棬���ǿ��ԴӶ������¿���һ���ڴ�ռ䣬��ԭ�ַ�����������
	//��ȥ�ı��������ݣ��Ͳ��������ʽ��Ӧ
	//  1.�����ü���  2.����   3.�����µ����ü���
	char& String::operator[](const size_t index) //���      
	{
		
			if (GetRefCount(_str) == 1)
			{
				return _str[index];
			}
			else
			{
				--GetRefCount(_str );
				char* tmp = new char[strlen(_str) + 5];
				*((int*)tmp) = 1;
				tmp += 4;
				strcpy(tmp, _str);
				_str = tmp;
				return _str[index];
			}
	}

	int& GetRefCount(char* ptr)   //��ȡ���ü���
	{
		return *((int*)(ptr-4));
	}
	~String()
	{
		if (--GetRefCount(_str) == 0)
		{
			cout << "~String" << endl;
			delete[] (_str-4);		
		}
	
	}
	friend ostream& operator<<(ostream& output, const String &s);
	friend istream& operator>>(istream& input, const String &s);
private:
	char* _str;

};


ostream& operator<<(ostream& output, const String &s)
{
	output << s._str;
	return output;
}
istream& operator>>(istream& input, const String &s)
{
	input >> s._str;
	return input;
}
void Test()
{
	String s1("abcdefg");
	String s2(s1);
	String s3;
	s3 = s2;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	s2[3] = '0';
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;

	//String s4("opqrst");
	//String s5(s4);
	//String s6 (s5);
	//s6 = s4;
	//cout << s4 << endl;
	//cout << s5 << endl;
	//cout << s6 << endl;

}
int main()
{
	Test();
	system("pause");
	return 0;
}




