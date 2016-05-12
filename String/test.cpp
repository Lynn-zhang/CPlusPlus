	
	#include"String.h"


	String& String::operator=(String s)   //（s不能加引用，否则会改变实参的值）
			{
				_size = strlen(s._str);
				_capacity = _size + 1;
				swap(_str, s._str);
				return *this;
			}
	String String::operator+(const String&s)
			{
				assert(s._str != NULL);
				String tmp(_str);
				Insert(_size, s._str);
				return tmp;
			}
	String& String::operator+=(const String&s)
			{
				CheckCapaciy(_size + 1 + s._size);
				strcat(_str, s._str);
				return *this;
			}
	char& String::operator[](const size_t index)      
			{
				return *(_str + index);
			}
		
	char* String::CStr()
	{
		return _str;
	}

	//尾删字符
	void String::PopBack()
	{
		assert(_str);
		_str[_size - 1] = '\0';
		--_size;
	}
	//尾部添加字符
	void String::PushBack(const char ch)
	{
		CheckCapaciy(_size + 2);
		_str[_size] = ch;
		_str[++_size] = '\0';
	}
	// 某位置后添加字符串
	void String::Insert(size_t pos, char * str)     // 1.增容 2.挪动数据 3.拷贝字符串
	{
		assert(str != NULL);
		assert(pos <= _size);
		int size = strlen(str);
		CheckCapaciy(_size + 1 + size);
		size_t index = _size;      //  _str[_size]='\0'
		while (index>-1&&index>=pos)
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
	//查找字符
	size_t String::Find(char ch)
	{
		assert(ch);
		for (size_t i = 0; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return -1;
	}
	//查找字符串
	size_t String::Find(char* sub)
	{
		assert(sub);
		assert(_str);
		int begin = 0;
		int be = begin;
		while (_str[begin])
		{				
			int i = 0;
			while(_str[begin]== sub[i]&&_str[begin]&&sub[i])
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
				begin ++;
			}
		}
		return -1;
	}
	//某位置后添加字符
	void String::Insert(size_t pos, char ch)
	{
		assert(ch);
		assert(pos <= _size);	
		CheckCapaciy(_size + 1);
		size_t index = _size;      //  _str[_size]='\0'
		while (index>-1 && index >= pos)
		{
			_str[index + 1] = _str[index];
			index--;
		}
		_str[pos] = ch;		
		if (pos == _size )
		{
			_str[++pos] = '\0';
		}
		_size ++;
	}
	//删除pos后面len个字符
	void String::Erase(size_t pos, size_t len)
	{
		assert(pos >= 0 && pos < _size);
		assert(len < _size);
		if (len == _size - pos-1)
		{
			_str[pos] = '\0';
		}
		else
		{
			while (pos != _size)
			{
				_str[pos] = _str[pos + len];
				pos++;
			}
			_str[pos] = '\0';
		}
	}
	// 计算字符串长度
	int String::Length()
			{
				return _size;
			}

	
		
	
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
	String s1("abcde");
	cout << s1.CStr() << endl;	
	String s2("fghi");
	cout << s2 << endl;
	s1.operator+(s2);
	cout << s1.CStr() << endl;
	s1.Erase(0,4);
	cout << s1.CStr() << endl;
//	s1 += s2;
	//cout << s2.CStr() << endl;
	//cout << s1 << endl;
	//s2.PopBack();
	//cout << s2.CStr() << endl;
	//s2 += "uvw";
	//cout << s2.CStr() << endl;
		

/*	int ret=s2.Find("bd");
	if (ret != -1)
	{
		cout << "ret->[" << ret << "]" << endl;
	}
	else
	{
		cout << "not exit !" << endl;
	}*/
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

