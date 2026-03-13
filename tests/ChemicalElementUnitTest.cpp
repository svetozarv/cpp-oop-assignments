#include <gtest/gtest.h>
#include "../ChemicalElement.hpp"

TEST (ChemicalElementTest, constructorConstraints) {
    EXPECT_NO_THROW(("Carbon", "C", 12.0116, 6, 14, 2));

    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 12.0116, 6, 14, 999));
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 12.0116, 6, 999, 2));
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 12.0116, 999, 14, 2));
    EXPECT_ANY_THROW(ChemicalElement("Carbon", "C", 9999, 6, 14, 2));
}


TEST (ChemicalElementTest, atom) {
    ChemicalElement elem = ChemicalElement("Carbon", "C", 12.0116, 6, 14, 2);
    ASSERT_EQ(elem.protons(), 6);
    ASSERT_EQ(elem.electrons(), 6);
    ASSERT_EQ(elem.electronShells(), 2);
    ASSERT_EQ(elem.valentialElectrons(), 4);
}