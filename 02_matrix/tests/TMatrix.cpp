#include "gtest/gtest.h"
#include "TMatrix.h"

TEST(TMatrix, can_create_matrix)
{
    ASSERT_NO_THROW(TMatrix<int> m(3));
}

TEST(TMatrix, throws_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TMatrix<int> m(-3));
}

TEST(TMatrix, can_create_copied_matrix)
{
    TMatrix<int> m(3);
    ASSERT_NO_THROW(TMatrix<int> mm(m));
}

TEST(TMatrix, can_get_size)
{
    TMatrix<int> m(3);
    ASSERT_NO_THROW(m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
    TMatrix<int> m(3);
    m[1][1] = 1;
    ASSERT_EQ(1, m[1][1]);
}

TEST(TMatrix, throws_set_element_with_negative_index)
{
    TMatrix<int> m(3);
    ASSERT_ANY_THROW(m[1][-1] = 1);
}

TEST(TMatrix, compare_equal_matrices)
{
    TMatrix<int> m(3), mm(3);
    ASSERT_TRUE(m == mm);
}

TEST(TMatrix, compare_matrix_with_itself)
{
    TMatrix<int> m(3);
    ASSERT_TRUE(m == m);
}

TEST(TMatrix, matrices_with_different_size)
{
    TMatrix<int> m(3), mm(4);
    ASSERT_FALSE(m == mm);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
    TMatrix<int> m(2), mm(2);
    TMatrix<int> s(2);
    m[0][0] = 1;
    mm[0][0] = 2;
    s = m + mm;
    TMatrix<int> r(2);
    r[0][0] = 3;
    ASSERT_TRUE(s == r);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
    TMatrix<int> m(3), mm(4);
    ASSERT_ANY_THROW(m + mm);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
    TMatrix<int> m(2), mm(2);
    TMatrix<int> s(2);
    m[0][0] = 1;
    mm[0][0] = 2;
    s = m - mm;
    TMatrix<int> r(2);
    r[0][0] = -1;
    ASSERT_TRUE(s == r);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TMatrix<int> m(3), mm(4);
    ASSERT_ANY_THROW(m - mm);
}
