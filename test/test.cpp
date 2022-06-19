#include <iostream>
#include "ini/ini.hpp"

using namespace std;

int main(void){
    tab::ini test("tmp.txt");
    cout << (string)test["Section"]("Key1") << endl;
    cout << (string)test["Section"]("114 514") << endl;
    cout << (string)test["Section"]("115") << endl;
    test["Section"]("114514") = "ehhhhhh";
    cout << (string)test["Section"]("114514") << endl;
    return 0;
}