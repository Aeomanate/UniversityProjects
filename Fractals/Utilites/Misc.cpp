//
// Created by Lyosha12 on 30.04.2018.
//

#include "Misc.hpp"

ErrorPrinter::
ErrorPrinter(std::string cause): cause(cause) { }

void ErrorPrinter::
print() {
ShowWindow(GetConsoleWindow(), SW_SHOW);
std::cerr << "Program will stop. Error: \n   \'" << cause << '\'' << std::endl;
system("PAUSE");
exit(1);
}