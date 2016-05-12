//�����ǶԷ���һ�ļ�ʵ�֣���ҿ��Խ����ͼ���ܵ�����һ��ȱ��
 
#define _CRT_SECURE_NO_WARNINGS 1
 
#include<iostream>
using namespace std;
#include<assert.h>
 
class String
{
public:
    String(char* str = "")    //����strlen��NULL��
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
        
       //������Ȼ���������������_refCount��ȣ�
       //������������������_strָ�붼ָ��ͬһ���ڴ�ʱ��
       //���޷������ж����_refCount������һ��
       //���Ƿ���һ��ȱ��֮һ
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