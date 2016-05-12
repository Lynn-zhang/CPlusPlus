#define _CRT_SECURE_NO_WARNINGS 1
 
#include<iostream>
using namespace std;
#include<assert.h>
 
class String
{
public:
    String(char* str = "")    //不能strlen（NULL）
    {
        _refCount = new int(1);     //给_refCount开辟空间，并赋初值1
        _size = strlen(str);
        _capacity = _size + 1;
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
    }
    String(const String &s)
    {
        _refCount = s._refCount;
        _str = s._str;
        _size = strlen(s._str);
        _capacity = _size + 1;
        (*_refCount)++;      //拷贝一次_refCount都要加1
         
    }
     
    //要考虑是s1=s2时，s1原先不为空的情况，要先释放原内存
    //如果要释放原内存时，要考虑它的_refCount减1后是否为0，为零再释放，否则其它对象指针无法再访问这片空间
    String& operator=(String& s)  
    {
        if (_str!= s._str)
        {
            _size = strlen(s._str);
            _capacity = _size + 1;
            if (--(*_refCount) == 0)
            {
                delete[] _str;
                delete _refCount;
            }
             
            _str = s._str;
            _refCount = s._refCount;
            (*_refCount)++;
        }      
        return *this;
    }
    //如果修改了字符串的内容，那所有指向这块内存的对象指针的内容间接被改变
    //如果还有其它指针指向这块内存，我们可以从堆上重新开辟一块内存空间，
    //把原字符串拷贝过来
    //再去改变它的内容，就不会产生链式反应
    //  1.减引用计数  2.拷贝   3.创建新的引用计数
    char& String::operator[](const size_t index) //参考深拷贝      
    {
        if (*_refCount==1)
        {
            return *(_str + index);
        }
        else
        {
            --(*_refCount);
            char* tmp = new char[strlen(_str)+1];
            strcpy(tmp, _str);
            _str = tmp;
            _refCount = new int(1);
            return *(_str+index);
        }
    }
    ~String()
    {
        if (--(*_refCount)== 0)  //当_refCount=0的时候就释放内存
        {
            delete[] _str;
            delete _refCount;
            _str = NULL;
            cout << "~String " << endl;
        }
        _size = 0;
        _capacity = 0;
    }
    friend ostream& operator<<(ostream& output, const String &s);
    friend istream& operator>>(istream& input, const String &s);
private:
    char* _str;      //指向字符串的指针
    size_t  _size;      //字符串大小
    size_t  _capacity;   //容量
    int* _refCount;    //计数指针
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
 
void Test()    //用例测试
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