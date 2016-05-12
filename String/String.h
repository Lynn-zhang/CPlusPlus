//ʵ��String�����ɾ���


#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<assert.h>

class String
{
public:
	String(char* str = "")    //����strlen��NULL��
	{
		_size = strlen(str);
		_capacity = _size + 1;
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	String(const String &s)
	{
		_str = NULL;
		_size = strlen(s._str);
		_capacity = _size + 1;

		String tmp(s._str);
		swap(_str, tmp._str);
	}
    ~String()
	{
		delete[] _str;
		_size = 0;
		_capacity = 0;
		_str = NULL;
	}


	//���������
	String& operator=(String s);
	String operator+(const String&s);
	String& operator+=(const String&s);
	char& operator[](const size_t index);


	friend ostream& operator<<(ostream& output, const String &s);
	friend istream& operator>>(istream& input, const String &s);

	char* CStr();
	

	//βɾ�ַ�
	void PopBack();
	//β������ַ�
	void PushBack(const char ch);
	// ĳλ�ú�����ַ���
	void Insert(size_t pos, char * str); 
	//�����ַ�
	size_t Find(char ch);
	//�����ַ���
	size_t Find(char* sub);
	//ĳλ�ú�����ַ�
	void Insert(size_t pos, char ch);
	//ɾ��pos����len���ַ�
	void Erase(size_t pos, size_t len);
	// �����ַ�������
	int Length();
private:
	//����������������ݣ�
	void CheckCapaciy(size_t needsize)
	{

		if (needsize >= _capacity)
		{
			if (needsize > 2 * _capacity)
			{
				_capacity = needsize;
			}
			else
				_capacity *= 2;
		}
		_str = (char *)realloc(_str, _capacity);
	}
private:
	char* _str;
	size_t  _size;
	size_t  _capacity;
};

ostream& operator<<(ostream& output, const String &s);
istream& operator>>(istream& input, const String &s);
