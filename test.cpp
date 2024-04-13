#include "testHead.hpp"

extern "C"{
    void start()
    {
        char a = 'a';
        int b = 123;
        short c = 234;

        pr("Meow");
        pr(b);
        pr(c);
    }
}

int main()
{
    start();

}
