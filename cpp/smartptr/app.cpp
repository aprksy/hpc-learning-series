#include <iostream>
#include <memory>

void someFunc(int newVar1)
{
    std::cout << "value: " << newVar1 << std::endl;
}

int main()
{
    std::unique_ptr<int> pdata1;
    {
        auto pdata0 { std::make_unique<int>(10) };
        std::cout << "pdata0: " << *pdata0 << std::endl;
        pdata1 = std::move(pdata0);
        if (pdata0)
        {
            std::cout << "pdata0: " << *pdata0 << std::endl;
        } else {
            std::cout << "pdata0 is nullptr" << std::endl;
        }
    }
    std::cout << "pdata1: " << *pdata1 << std::endl;
    // auto rawPtr1 = pdata1.release();

    std::unique_ptr<int>* newVar = nullptr;
    someFunc(*pdata1);

    auto pdata2 = std::make_shared<int>(100);
    auto pdata3 = pdata2;

    if (pdata2) {
        std::cout << "pdata2 not nullptr" << std::endl;
    }
    if (pdata3) {
        std::cout << "pdata3 not nullptr" << std::endl;
    }

    pdata2.reset();
    if (pdata2) {
        std::cout << "pdata2 not nullptr" << std::endl;
    } else {
        std::cout << "pdata2 is nullptr" << std::endl;
        std::cout << "pdata2 address: " << pdata2.get() << std::endl;
    }
    if (pdata3) {
        std::cout << "pdata3 not nullptr" << std::endl;
        std::cout << "pdata3 address: " << pdata3.get() << std::endl;
    }

    
}