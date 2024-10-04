#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    const int size = 5;
    TDynamicVector<int> v1(10);
    v1[0] = 0; v1[1] = 1; v1[2] = 2; v1[3] = 3; v1[4] = 4; v1[5] = 5; v1[6] = 6; v1[7] = 7; v1[8] = 8; v1[9] = 9;
    TDynamicVector<int> v2(10);
    v2[0] = 9; v2[1] = 8; v2[2] = 7; v2[3] = 6; v2[4] = 5; v2[5] = 4; v2[6] = 3; v2[7] = 2; v2[8] = 1; v2[9] = 0;
    TDynamicMatrix<int> m1(size);
    m1[1] = v1;
    m1[2] = v2;

    TDynamicMatrix<int> m2(m1);

    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    const int size = 15;
    TDynamicMatrix<long long> m1(size);
    TDynamicVector<long long>* v1 = m1.data();
    long long* p1 = (*v1).data();

    TDynamicMatrix<long long> m2(m1);
    TDynamicVector<long long>* v2 = m2.data();
    long long* p2 = (*v2).data();

    EXPECT_NE(&p1, &p2);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(40);

    EXPECT_EQ(40, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    const int size = 5;
    TDynamicVector<int> v(size);
    for (int i = 0; i < size; i++) v[i] = i;
    TDynamicMatrix<int> m(4);

    m[0] = v;

    EXPECT_EQ(v, m[0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    const int size = 3;
    TDynamicMatrix<char> m(size);

    ASSERT_ANY_THROW(m.at(-5));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    const int size = 10;
    TDynamicMatrix<long long> m(size);

    ASSERT_ANY_THROW(m.at(20));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    const int size = 10;
    TDynamicMatrix<int> m1(size);

    EXPECT_EQ(m1 = m1, m1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    const int size = 5;
    TDynamicVector<int> v(size);
    for (int i = 0; i < size; i++)
        v[i] = i;
    TDynamicMatrix<int> m1(size);
    m1[0] = v;
    TDynamicMatrix<int> m2(size);

  EXPECT_EQ(m2=m1, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    const int size = 5;
    TDynamicMatrix<int> m1(size * 2);
    TDynamicMatrix<int> m2(size);

    m2 = m1;

    EXPECT_NE(m2.size(), size);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    const int size = 5;
    TDynamicVector<int> v(size);
    for (int i = 0; i < size; i++)
        v[i] = i;
    TDynamicMatrix<int> m1(size);
    m1[0] = v;
    TDynamicMatrix<int> m2(size + 5);

    EXPECT_EQ(m2 = m1, m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    const int size = 10;
    TDynamicVector<int> v(size);
    for (int i = 0; i < size; i++)
        v[i] = i;
    TDynamicMatrix<int> m1(size);
    TDynamicMatrix<int> m2(size);
    m1[0] = m2[0] = v;

    ASSERT_EQ(m1 == m2, 1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    const int size = 10;
    TDynamicMatrix<int> m1(size);

    ASSERT_EQ(m1 == m1, 1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    const int size = 10;
    TDynamicMatrix<int> m1(size);
    TDynamicMatrix<int> m2(size + 1);

    ASSERT_EQ(m1 == m2, 0);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    const int size = 10;
    TDynamicVector<int> v(size);
    for (int i = 0; i < size; i++)
        v[i] = i;
    TDynamicMatrix<int> m1(size);
    for (int i = 0; i < size; i++)
        m1[i] = v; 
    v = v * 2;
    TDynamicMatrix<int> m2(size);
    for (int i = 0; i < size; i++)
        m2[i] = v;
    v = v * 1.5;
    TDynamicMatrix<int> m3(size);
    for (int i = 0; i < size; i++)
        m3[i] = v;
    TDynamicMatrix<int> res(size);

    res = m1 + m2;

    ASSERT_EQ(res, m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    const int size = 10;
    TDynamicMatrix<int> m1(size);
    TDynamicMatrix<int> m2(size+1);

    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    const int size = 10;
    TDynamicVector<int> v(size);
    for (int i = 0; i < size; i++)
        v[i] = i;
    TDynamicMatrix<int> m1(size);
    for (int i = 0; i < size; i++)
        m1[i] = v;
    v = v * 2;
    TDynamicMatrix<int> m2(size);
    for (int i = 0; i < size; i++)
        m2[i] = v;
    v = v * 0.5;
    TDynamicMatrix<int> m3(size);
    for (int i = 0; i < size; i++)
        m3[i] = v;
    TDynamicMatrix<int> res(size);

    res = m2-m1;

    ASSERT_EQ(res, m3);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    const int size = 10;
    TDynamicMatrix<int> m1(size);
    TDynamicMatrix<int> m2(size + 1);

    ASSERT_ANY_THROW(m1 - m2);
}

