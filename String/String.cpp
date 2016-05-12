//ʵ��String�����ɾ���

#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
using namespace std;
#include<assert.h>

class String
{
public:
	String(char* str = "")          //����strlen��NULL��
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

	String& operator=(String s)   //��s���ܼ����ã������ı�ʵ�ε�ֵ��
	{
		_size = strlen(s._str);
		_capacity = _size + 1;
		swap(_str, s._str);
		return *this;
	}
	char& operator[](const size_t index)        //��������ã����Ըı���s[i]��ֵ��
	{
		return *(_str + index);
	}
	char* CStr()
	{
		return _str;
	}
	~String()
	{
		delete[] _str;
		_size = 0;
		_capacity = 0;
		_str = NULL;
	}


	

	void PopBack()
	{
		assert(_str);
		_str[_size - 1] = '\0';
		--_size;
	}
	//β������ַ�
	void PushBack(const char ch)
	{
		CheckCapaciy(_size + 2);
		_str[_size] = ch;
		_str[++_size] = '\0';
	}
	// ĳλ�ú�����ַ���
	void Insert(size_t pos, char * str)     // 1.���� 2.Ų������ 3.�����ַ���
	{
		assert(str != NULL);
		assert(pos <= _size);
		int size = strlen(str);
		CheckCapaciy(_size + 1 + size);
		int index = _size;      //  _str[_size]='\0'
		while (index>-1 && index >= pos)
		{
			_str[index + size] = _str[index];
			index--;
		}
		for (int i = 0; i < size; i++)
		{
			_str[pos++] = str[i];
		}
		if (pos == _size + size)
		{
			_str[pos] = '\0';
		}
		_size += size;
	}
	//�����ַ�
	size_t Find(char ch)
	{
		assert(ch);
		for (int i = 0; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return -1;
	}
	//�����ַ���
	size_t Find(char* sub)
	{
		assert(sub);
		assert(_str);
		int begin = 0;
		int be = begin;
		while (_str[begin])
		{
			int i = 0;
			while (_str[begin] == sub[i] && _str[begin] && sub[i])
			{
				begin++;
				i++;
			}
			if (sub[i] == '\0')
				return be;
			else
			{
				i = 0;
				be++;
				begin++;
			}
		}
		return -1;
	}
	//ĳλ�ú�����ַ�
	void Insert(size_t pos, char ch)
	{
		assert(ch);
		assert(pos <= _size);
		CheckCapaciy(_size + 1);
		int index = _size;      //  _str[_size]='\0'
		while (index>-1 && index >= pos)
		{
			_str[index + 1] = _str[index];
			index--;
		}
		_str[pos] = ch;
		if (pos == _size)
		{
			_str[++pos] = '\0';
		}
		_size++;
	}
private:
	//����������������ݣ�
	void CheckCapaciy(int needsize)
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

void Test()
{
	String s1("abcde");
	cout << s1.CStr() << endl;
	String s2(s1);
	cout << s2.CStr() << endl;

	int ret = s2.Find("bd");
	if (ret != -1)
	{
		cout << "ret->[" << ret << "]" << endl;
	}
	else
	{
		cout << "not exit !" << endl;
	}
	//s2.Insert(0, "00");
	//cout << s2.CStr() << endl;
	/*s2.Insert(1, "00");
	cout << s2.CStr() << endl;*/
	/*s2.Insert(5, "00");
	cout << s2.CStr() << endl;*/
	/*	s2.Insert(1, 'y');
	cout << s2.CStr() << endl;*/

	/*	int ret=s2.Find('d');
	if (ret != -1)
	{
	cout << "ret->[" << ret<<"]" << endl;
	}
	else
	{
	cout << "not exit !" << endl;
	}*/
}
int main()
{
	Test();
	system("pause");
	return 0;
}

