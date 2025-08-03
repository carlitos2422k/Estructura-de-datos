#ifndef BIGO_H
#define BIGO_H

#include <iostream>
#include <string>

class BigO {
private:
    std::string notation;
public:
    BigO(std::string notation);
    std::string getNotation() const;
    BigO operator+(const BigO& other) const;
    BigO operator*(const BigO& other) const;
    static void fundamentals();
    static void manipulationRules();
    static void applications();
};

#endif
