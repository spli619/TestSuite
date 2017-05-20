#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>
#include <memory>
#include <list>
#include <map>

#define _test(cond) \
    doTest(cond, #cond, __FILE__, __LINE__);

namespace SuiteTest {
class Test
{
    std::string name;
    long nbPass;
    long nbFail;
    std::list<Test*>subTest;
    std::multimap<std::string, bool> conditions;
    std::ostream* os;
    Test(const Test&);
    Test& operator =(const Test&);
protected:
    void doTest(bool condition, std::string lbl, const char* nameFile, long line);
    virtual void tests() =0;
public:
    Test(const std::string& name="", std::ostream* os= &std::cout): name(name), nbPass(0), nbFail(0), os(os) {}
    virtual ~Test() {}

    void exec();
    long getNbPass() const{return nbPass;}
    long getNbFail() const{return nbFail;}
    long getNbAllPass() const;
    long getNbAllFail() const;
    const std::ostream& getStream() const {return *os;}
    void setStream(std::ostream& os) {this->os = &os;}
    std::string getName() const {return name;}
    void setName(const std::string& name) {this->name=name;}
    void addTest(Test& test) {subTest.push_back(&test);}

    void reset();
    void report() const;

};
}


#endif // TEST_H
