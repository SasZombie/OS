#include "testHead.hpp"

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
    start();

}
