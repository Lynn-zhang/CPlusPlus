//写时拷贝（优化）

#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<assert.h>

class String
{
public:
	String(char* str = "")    //不能strlen（NULL）
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

	//要考虑是s1=s2时，s1原先不为空的情况，要先释放原内存
	//如果要释放原内存时，要考虑它的_refCount减1后是否为0，为零再释放，否则其它对象指针无法再访问这片空间
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
	//如果修改了字符串的内容，那所有指向这块内存的对象指针的内容间接被改变
	//如果还有其它指针指向这块内存，我们可以从堆上重新开辟一块内存空间，把原字符串拷贝过来
	//再去改变它的内容，就不会产生链式反应
	//  1.减引用计数  2.拷贝   3.创建新的引用计数
	char& String::operator[](const size_t index) //深拷贝      
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

	int& GetRefCount(char* ptr)   //获取引用计数
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




