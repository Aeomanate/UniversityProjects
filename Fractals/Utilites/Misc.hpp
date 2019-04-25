//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LAB_3_MISC_HPP
#define LAB_3_MISC_HPP

#include <algorithm>
#include <string>
#include <iostream>
#include <windows.h>

template <class Base, class Derived, class... Params>
Base* createDerived(Params&&... args) {
    return new Derived(args...);
}


class ErrorPrinter {
  public:
    ErrorPrinter(std::string cause);
    void print();
  
  private:
    std::string cause;
};

#endif //LAB_3_MISC_HPP
