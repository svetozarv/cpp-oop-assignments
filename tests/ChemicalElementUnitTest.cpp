#include <gtest/gtest.h>
#include "../include/ChemicalElement.hpp"

TEST (ChemicalElementTest, noConstructorConstraints) {
    EXPECT_NO_THROW(ChemicalElement("Carbon", "C", 12.0116, 6, 14, 2));
}

TEST (ChemicalElementTest, invalidMass) {
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", -1.0, 6, 14, 2));
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 9999, 6, 14, 2));
}

TEST (ChemicalElementTest, invalidAtomicNumber) {
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 12.0116, -1, 14, 2));
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 12.0116, 999, 14, 2));
}

TEST (ChemicalElementTest, invalidGroupNumber) {
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 12.0116, 6, -1, 2));
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 12.0116, 6, 999, 2));
}

TEST (ChemicalElementTest, invalidPeriodNumber) {
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 12.0116, 6, 14, -1));
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 12.0116, 6, 14, 999));
}

TEST (ChemicalElementTest, nameAndSymbol) {
    ChemicalElement elem("Carbon", "C", 12.0116, 6, 14, 2);
    ASSERT_EQ(elem.getName(), "Carbon");
    ASSERT_EQ(elem.getSymbol(), "C");
}

TEST (ChemicalElementTest, massAndAtomicNumber) {
    ChemicalElement elem("Carbon", "C", 12.0116, 6, 14, 2);
    ASSERT_DOUBLE_EQ(elem.getMass(), 12.0116);
    ASSERT_EQ(elem.getAtomicNumber(), 6);
}

TEST (ChemicalElementTest, groupAndPeriodNumber) {
    ChemicalElement elem("Carbon", "C", 12.0116, 6, 14, 2);
    ASSERT_EQ(elem.protons(), 6);
    ASSERT_EQ(elem.electrons(), 6);
    ASSERT_EQ(elem.electronShells(), 2);
    ASSERT_EQ(elem.valentialElectrons(), 4);
}
