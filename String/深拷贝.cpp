//���

///////////////////////////////////////////////////////////////////////////////////////
 
//          дString��Ĺ��캯��ʱһ��Ҫע���������
//          ����Ҫ���ǵ�����Ķ�����в������޲����������
//          ��������ʱ����ֱ�Ӹ�ֵ������һ���ڴ������ͷŵĻ���������
//          �޲εĹ��캯�����ܽ�_strָ�븳ֵΪNULL����Ϊ����strlen(NULL)
//          ��ֵ�����������Ҫ���ǵ��п��ܷ����ڴ�ʧ�ܵ�����
//          ��Ȼ���ǵ�Ҫ��'\0'����ռ�Ŷ
//                                                                     By��Lynn-Zhang
//////////////////////////*****************////////////////////////////////////////////
 
#include<iostream>
using namespace std;
 
class String
{
public:
            
           String(char * str="")          //����strlen��NULL��
                    :_str(new char [strlen(str ) + 1])
           {
                    strcpy(_str, str);
           }
           String(const String &s)
                    :_str(new char [strlen(s ._str) + 1])
           {
                    strcpy(_str, s._str);
           }
            
           //��ֵ�����������
           String& operator=(const String& s)
           {
                    if (this != &s )
                    {
                        /*     //�п��ܿ��ٿռ�ʧ�ܣ�����ȴ�ƻ���_str������
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
 
 
//��������
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