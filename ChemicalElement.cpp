#include <string>
#include "ChemicalElement.hpp"

using namespace std;

ChemicalElement::ChemicalElement(
    string name, string symbol, double mass, unsigned int atomicNumber, unsigned int groupNumber, unsigned int periodNumber) :
    name(name), symbol(symbol), mass(mass), atomicNumber(atomicNumber), groupNumber(groupNumber), periodNumber(periodNumber)
{
    if (mass < 0 || mass > 300)
    {
        throw string("Invalid mass.");
    }
    if (atomicNumber < 1 || atomicNumber > 118)
    {
        throw string("Invalid atomic number.");
    }
    if (groupNumber < 1 || groupNumber > 18)
    {
        throw string("Invalid group number.");
    }
    if (periodNumber < 1 || periodNumber > 7)
    {
        throw string("Invalid period number.");
    }
}

auto ChemicalElement::protons() -> int { return atomicNumber; }
auto ChemicalElement::electrons() -> int { return atomicNumber; }
auto ChemicalElement::electronShells() -> int { return periodNumber; }

auto ChemicalElement::valentialElectrons() -> int
{
    if ((1 <= groupNumber && groupNumber <= 2) || (13 <= groupNumber && groupNumber <= 18))
    {
        return groupNumber % 10;
    }
    return groupNumber;
}

auto ChemicalElement::getName() -> string { return name; }
auto ChemicalElement::getSymbol() -> string { return symbol; }
auto ChemicalElement::getMass() -> double { return mass; }
auto ChemicalElement::getAtomicNumber() -> unsigned int { return atomicNumber; }
auto ChemicalElement::getGroupNumber() -> unsigned int { return groupNumber; }
auto ChemicalElement::getPeriodNumber() -> unsigned int { return periodNumber; }