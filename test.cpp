#include "test.h"
namespace SuiteTest {

void Test::doTest(bool condition, std::string lbl, const char* nameFile, long line) {
    if (condition) {
        ++nbPass;
    } else {
        ++nbFail;
        if(os) {
            *os << nameFile << ":" << line << ": Failure: (" << lbl << ")"
                << (name.empty()?"":("\t" + name)) << "\n";
        }
    }
    conditions.insert(std::make_pair(lbl, condition));
}

void Test::exec() {
    reset();
    tests();
    if (!subTest.empty()) {
        for (auto& test: subTest) {
            if (test) {
                test->exec();
            }
        }
    }
}

long Test::getNbAllPass() const {
    long nbAllPass{0};
    if (!subTest.empty()) {
        for (auto const& test: subTest) {
            if (test) {
                nbAllPass += test->getNbAllPass();
            }
        }
    }
    nbAllPass+=getNbPass();
    return nbAllPass;
}

long Test::getNbAllFail() const {
    long nbAllFail{0};
    if (!subTest.empty()) {
        for (auto const& test: subTest) {
            if (test) {
                nbAllFail+= test->getNbAllFail();
            }
        }
    }
    nbAllFail+=getNbFail();
    return nbAllFail;
}

void Test::reset() {
    nbPass = nbFail = 0;
    if(!subTest.empty()) {
        for (auto& test: subTest) {
            if (test) {
                test->reset();
            }
        }
    }
}

void Test::report() const{
    if(!subTest.empty()) {
        for(auto & test: subTest) {
            if(test) {
                if(!test->getStream() && os) {
                    test->setStream(*os);
                }
                test->report();
            }
        }
    }
    if (os) {
        *os << "\n" << getName() << ": \n"
            << "Nombre de ratée: " << getNbAllFail() << "\n"
            << "Nombre de réussite: " << getNbAllPass() << "\n"
            << "Pourcentage de réussite: " << static_cast<double>(getNbAllPass())/(getNbAllFail()+getNbAllPass())*100 << "%" << std::endl;
    }
}

}
