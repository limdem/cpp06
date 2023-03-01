#include "../includes/Base.hpp"
#include "../includes/A.hpp"
#include "../includes/B.hpp"
#include "../includes/C.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <typeinfo>

Base::~Base(){}

Base * generate(void)
{
    int choose;
    Base    *ptr;

    srand((unsigned int)time(NULL));
    choose = rand() % 3 + 1;
    if (choose == 1)
    {
        std::cout << "A object generated" << std::endl;
        ptr = new (std::nothrow)A;
    }
    if (choose == 2)
    {
        std::cout << "B object generated" << std::endl;
        ptr = new (std::nothrow)B;
    }
    if (choose == 3)
    {
        std::cout << "C object generated" << std::endl;
        ptr = new (std::nothrow)C;
    }
    return (ptr);
}

void    identify(Base* p)
{
    std::cout << "pointer identifier" << std::endl;
    if (dynamic_cast<A *>(p))
        std::cout << "A object identified" << std::endl;
    if (dynamic_cast<B *>(p))
        std::cout << "B object identified" << std::endl;
    if (dynamic_cast<C *>(p))
        std::cout << "C object identified" << std::endl;
}

void    identify(Base& p)
{
    std::cout << "reference identifier" << std::endl;
    try
    {
        A &a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "A object identified" << std::endl;
    }
    catch (std::bad_cast)
    {}
    try
    {
        B &b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "B object identified" << std::endl;
    }
    catch (std::bad_cast)
    {}
    try
    {
        C &c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "C object identified" << std::endl;
    }
    catch (std::bad_cast)
    {}
}