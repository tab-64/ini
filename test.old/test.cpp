#include <iostream>
#include "ini.hpp"

using namespace std;

int main(void){
    tab::ini test("tmp.txt");

    cout << "=======READ_TEST=======" << endl;
    cout << (string)test["Section"]("Key1") << endl;
    cout << (string)test["Section"]("114 514") << endl;
    cout << (string)test["Section"]("115") << endl;
    test["Section"]("114514") = "ehhhhhh";
    cout << (string)test["Section"]("114514") << endl;
    cout << "=======READ_TEST=======" << endl;
    
    cout << "======WRITE_TEST=======" << endl;
    tab::Writer(test.sections()).write_order(cout);
    cout << "======WRITE_TEST=======" << endl;

    return 0;
}
