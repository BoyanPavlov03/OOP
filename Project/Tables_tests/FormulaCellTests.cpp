#include "gtest/gtest.h"
#include "FormulaCell.h"
#include "Exceptions/InvalidFormulaException.h"

class FormulaCellTests : public ::testing::Test {};

TEST_F(FormulaCellTests, constructor) {
    try {
        FormulaCell f("=(1 + 3))", 1, 1);
        f.update({});
    } catch (InvalidFormulaException& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Error: row 1, col 1, =(1 + 3)) is an invalid formula");
    }
}

TEST_F(FormulaCellTests, constructorWithRandomCharactersInFormula) {
    try {
        FormulaCell f("=(1a + 3)", 1, 1);
        f.update({});
    } catch (InvalidFormulaException& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Error: row 1, col 1, =(1a + 3) is an invalid formula");
    }
}

TEST_F(FormulaCellTests, constructorWithMoreInvalidNumberOfOperands) {
    try {
        FormulaCell f("=(1 + 3) 2", 1, 1);
        f.update({});
    } catch (InvalidFormulaException& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Error: row 1, col 1, =(1 + 3) 2 is an invalid formula");
    }
}

TEST_F(FormulaCellTests, constructorWithMoreInvalidNumberOfOperators) {
    try {
        FormulaCell f("=(1 + 3) +", 1, 1);
        f.update({});
    } catch (InvalidFormulaException& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Error: row 1, col 1, =(1 + 3) + is an invalid formula");
    }
}

TEST_F(FormulaCellTests, printToFile) {
    FormulaCell f("=(1 + 3)", 1, 1);
    std::stringstream ss;
    f.printToFile(ss);
    EXPECT_EQ(ss.str(), "=(1 + 3)");
}