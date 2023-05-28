#include "gtest/gtest.h"
#include "Cells/FormulaCell.h"
#include "Exceptions/InvalidFormulaException.h"
#include "Exceptions/DivisionByZeroException.h"

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

TEST_F(FormulaCellTests, constructorTwo) {
    try {
        FormulaCell f("=((1 + 3)", 1, 1);
        f.update({});
    } catch (InvalidFormulaException& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Error: row 1, col 1, =((1 + 3) is an invalid formula");
    }
}

TEST_F(FormulaCellTests, aLotOfOperations) {
    FormulaCell f("=(1 + 5) * 2^(4 - 7/2) - 18/3 * 2", 1, 1);
    f.update({});

    EXPECT_EQ(f.getNumericValue(), -3.5147);
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

TEST_F(FormulaCellTests, constructorWithFormulaThatIsDividingByZero) {
    try {
        FormulaCell f("=(1 + 3) / 0", 1, 1);
        f.update({});
    } catch (DivisionByZeroException& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Error: row 1, col 1, =(1 + 3) / 0 has division by 0");
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