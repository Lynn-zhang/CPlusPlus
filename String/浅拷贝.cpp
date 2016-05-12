#include <iostream>
using namespace std;

class String
{
public:
           String(char *str)
                    :_str(new char [strlen(str )+1])
           {
                              strcpy(_str, str);
           }
           String(const String & s)
           {
                    _str = s._str;
           }
           String& operator=(const String & s )
           {
                    if (this !=&s)
                    {
                              _str = s._str;
                    }
                    return *this ;
           }
           ~String()
           {
                    delete[] _str;
           }
private:
           char* _str;
};

void Test()
{
           String s1("Lynn" );
           String s2=s1;
}
int main()
{
           Test();
           system("pause" );
           return 0;
}

