#include <iostream>

using namespace std;

int main()
{
    int a = 500;
    int b = 500;
    cout << &a << endl;//0x7ffe3b5cd808
    cout << &b << endl;//0x7ffe3b5cd804
    
    std::string c = "this is cpp";
    std::string d = "this is cpp";
    cout << &c << endl;//0x7ffe3b5cd7e0
    cout << &d << endl;//0x7ffe3b5cd7c0
    
    return 0;
}
