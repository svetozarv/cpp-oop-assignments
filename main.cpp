#include "./include/ChemicalElement.hpp"
#include <print>

auto main() -> int {
    ChemicalElement elem("Carbon", "C", 12.0116, 6, 14, 2);
    std::println("Element: {}", elem.getName());
    std::println("Symbol: {}", elem.getSymbol());

    std::println("Characteristics:");
    std::println("Protons: {}", elem.protons());
    std::println("Electrons: {}", elem.electrons());
    std::println("Shells: {}", elem.electronShells());
    std::println("Valence electrons: {}", elem.valentialElectrons());
}