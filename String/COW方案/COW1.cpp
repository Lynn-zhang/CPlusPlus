//以下是对方案一的简单实现，大家可以结合上图感受到方案一的缺陷
 
#define _CRT_SECURE_NO_WARNINGS 1
 
#include<iostream>
using namespace std;
#include<assert.h>
 
class String
{
public:
    String(char* str = "")    //不能strlen（NULL）
       :_refCount(0)
    {
       _str = new char[strlen( str) + 1];
       strcpy(_str, str);
       _refCount++;
    }
    String(String &s)
       :_refCount( s._refCount)     
    {
       _str = s._str;
       _refCount++;
       s._refCount = _refCount;
        
       //这里虽然可以让两个对象的_refCount相等，
       //但如果超过两个对象的_str指针都指向同一块内存时，
       //就无法让所有对象的_refCount都保持一致
       //这是方案一的缺陷之一
    }
    ~String()
    {
       if (--_refCount == 0)
       {
            delete[] _str;
           _str = NULL;
           cout << "~String " << endl;
       }
    }
    friend ostream& operator<<( ostream& output, const String &s);
private:
    char* _str;
    int _refCount;
};
ostream& operator<<( ostream& output, const String & s)
{
    output << s._str;
    return output;
}
void Test()
{
    String s1("aaa");
    String s2(s1);
    String s3(s2);
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
}
int main()
{
    Test();
    system("pause");
    return 0;
}