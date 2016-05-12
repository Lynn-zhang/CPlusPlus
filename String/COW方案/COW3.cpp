#define _CRT_SECURE_NO_WARNINGS 1
 
#include<iostream>
using namespace std;
#include<assert.h>
 
class String
{
public:
    String(char* str = "")    //����strlen��NULL��
    {
        _refCount = new int(1);     //��_refCount���ٿռ䣬������ֵ1
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
        (*_refCount)++;      //����һ��_refCount��Ҫ��1
         
    }
     
    //Ҫ������s1=s2ʱ��s1ԭ�Ȳ�Ϊ�յ������Ҫ���ͷ�ԭ�ڴ�
    //���Ҫ�ͷ�ԭ�ڴ�ʱ��Ҫ��������_refCount��1���Ƿ�Ϊ0��Ϊ�����ͷţ�������������ָ���޷��ٷ�����Ƭ�ռ�
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
    //����޸����ַ��������ݣ�������ָ������ڴ�Ķ���ָ������ݼ�ӱ��ı�
    //�����������ָ��ָ������ڴ棬���ǿ��ԴӶ������¿���һ���ڴ�ռ䣬
    //��ԭ�ַ�����������
    //��ȥ�ı��������ݣ��Ͳ��������ʽ��Ӧ
    //  1.�����ü���  2.����   3.�����µ����ü���
    char& String::operator[](const size_t index) //�ο����      
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
        if (--(*_refCount)== 0)  //��_refCount=0��ʱ����ͷ��ڴ�
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
    char* _str;      //ָ���ַ�����ָ��
    size_t  _size;      //�ַ�����С
    size_t  _capacity;   //����
    int* _refCount;    //����ָ��
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
 
void Test()    //��������
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