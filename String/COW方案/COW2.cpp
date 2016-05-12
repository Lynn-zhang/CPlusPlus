//   ����һ����̬���α���������ָ��һ���ڴ��ָ���������ÿ����һ�μ�1��
//   ֱ��������0��Ҳ����û��ָ����ָ������ʱ����ȥ�ͷ��ǿ��ڴ棬���ƿ��У���ʵ��Ȼ��

// �������ֻ������ֻ����һ�ι��캯����ֻ��һ���ڴ�����Σ������ε��ù��캯���������
// �¹���Ķ���������ı�count��ֵ����ô��ǰ���ڴ��޷��ͷŻ�����ڴ�й©��

#define_CRT_SECURE_NO_WARNINGS 1
 
 
#include<iostream>
using namespace std;
#include<assert.h>
 
class String
{
public:
    String(char* str = "")    //����strlen��NULL��
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
 
int String::count = 0;      //��ʼ��count
 
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