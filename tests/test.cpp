#include "testHead.hpp"
#include <fstream>

extern "C"{
    void start()
    {
        char a = 'a';
        int b = 123;
        short c = 234;

        float pi = 3.14;

        // pr("Meow");
        // pr(b);
        // pr(c);
        pr(pi);
    }
}

int main()
{
    std::fstream f("SAS.txt");

    std::string s;
    char l[20];

    f << "aaa";
    int x;
    
    f >> x;

}
