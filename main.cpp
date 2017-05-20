#include "test.h"
#include <iostream>
#include <fstream>

using namespace SuiteTest;

class TestCon: public Test {
protected:
    void tests() {
        _test(5<2);
        _test(2==2);
        _test(false==false);
        _test(false);
        _test(5.0==5);
    }
public:
    TestCon(const std::string comment=""): Test(comment) {}


};

int main()
{
    TestCon test("test1");
    TestCon test2("test2");
    TestCon Main("Main");

    Main.addTest(test);
    Main.addTest(test2);

    Main.report();
}
