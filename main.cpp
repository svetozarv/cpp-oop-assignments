#include "./include/ChemicalElement.hpp"
#include <iostream>

auto main() -> int {
    ChemicalElement elem = ChemicalElement("Carbon", "C", 12.0116, 6, 14, 2);
    std::cout << "Element:" << std::endl;
    std::cout << elem.getName() << std::endl;
    std::cout << elem.getSymbol() << std::endl;

    std::cout << "Characteristics:" << std::endl;
    std::cout << "Protons:" << elem.protons() << std::endl;
    std::cout << "Electrons:" << elem.electrons() << std::endl;
    std::cout << "Shells" << elem.electronShells() << std::endl;
    std::cout << "Valential electrons:" << elem.valentialElectrons() << std::endl;
}