//深拷贝

///////////////////////////////////////////////////////////////////////////////////////
 
//          写String类的构造函数时一定要注意参数问题
//          首先要考虑到构造的对象分有参数和无参数两种情况
//          构造对象的时候不能直接赋值，否则一块内存两次释放的话程序会出错
//          无参的构造函数不能将_str指针赋值为NULL，因为不能strlen(NULL)
//          赋值运算符的重载要考虑到有可能分配内存失败的问题
//          当然，记得要给'\0'分配空间哦
//                                                                     By：Lynn-Zhang
//////////////////////////*****************////////////////////////////////////////////
 
#include<iostream>
using namespace std;
 
class String
{
public:
            
           String(char * str="")          //不能strlen（NULL）
                    :_str(new char [strlen(str ) + 1])
           {
                    strcpy(_str, str);
           }
           String(const String &s)
                    :_str(new char [strlen(s ._str) + 1])
           {
                    strcpy(_str, s._str);
           }
            
           //赋值运算符的重载
           String& operator=(const String& s)
           {
                    if (this != &s )
                    {
                        /*     //有可能开辟空间失败，但是却破坏了_str的内容
                               delete[] _str;
                               _str = new char[strlen(s._str) + 1];
                               strcpy(_str, s._str);   */
 
                              char* tmp = new char [strlen(s ._str) + 1];
                              strcpy(tmp, s._str);
                              delete[] _str;
                              swap(_str, tmp);
 
                    }
                    return *this ;
           }
           char* CStr()
           {
                    return _str;
           }
           ~String()
           {
                    delete[] _str;
           }
private:
           char* _str;
};
 
 
//函数测试
void Test()
{
           String s1("aaaaa" );
           cout << s1.CStr() << endl;
           String s2(s1);
           cout << s2.CStr() << endl;
           String s3 = s1;
           s3= s2;
           cout << s3.CStr() << endl;
           String s4;
           // s4 = s1;
           cout << s4.CStr() << endl;
           
}
int main()
{
           Test();
           system("pause" );
           return 0;
}