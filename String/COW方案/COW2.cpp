//   设置一个静态整形变量来计算指向一块内存的指针的数量，每析构一次减1，
//   直到它等于0（也就是没有指针在指向它的时候）再去释放那块内存，看似可行，其实不然！

// 这个方案只适用于只调用一次构造函数、只有一块内存的情形，如果多次调用构造函数构造对象，
// 新构造的对象照样会改变count的值，那么以前的内存无法释放会造成内存泄漏。

#define_CRT_SECURE_NO_WARNINGS 1
 
 
#include<iostream>
using namespace std;
#include<assert.h>
 
class String
{
public:
    String(char* str = "")    //不能strlen（NULL）
    {
       _str = new char[strlen( str) + 1];
       strcpy(_str, str);
 
       count++;
    }
    String(const String &s)
    {
       _str = s._str;
       count++;
        
    }
    String& operator=( String& s)  
    {
       _str = s._str;
       count++;
       return *this;
    }
    ~String()
    {
       if (--count == 0)
       {
            delete[] _str;
           _str = NULL;
           cout << "~String " << endl;
       }
    }
    friend ostream& operator<<( ostream& output, const String &s);
    friend istream& operator>>( istream& input, const String &s);
private:
    char* _str;
    static int count;
};
ostream& operator<<( ostream& output, const String & s)
{
    output << s._str;
    return output;
}
istream& operator>>( istream& input, const String & s)
{
    input >> s._str;
    return input;
}
 
int String::count = 0;      //初始化count
 
void Test()
{
    String s1("aaa");
    String s2(s1);
    String s3 = s2;
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