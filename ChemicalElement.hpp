#pragma once

#include <string>
using namespace std;

class ChemicalElement
{
private:
    string name;
    string symbol;
    double mass;
    unsigned int atomicNumber;
    unsigned int groupNumber;
    unsigned int periodNumber;

public:
    ChemicalElement(string name, string symbol, double mass, unsigned int atomicNumber, unsigned int groupNumber, unsigned int periodNumber);
    auto protons() -> int;
    auto electrons() -> int;
    auto electronShells() -> int;
    auto valentialElectrons() -> int;
    auto getName() -> string;
    auto getSymbol() -> string;
    auto getMass() -> double;
    auto getAtomicNumber() -> unsigned int;
    auto getGroupNumber() -> unsigned int;
    auto getPeriodNumber() -> unsigned int;
};
