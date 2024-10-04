#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    const int size = 5;
    TDynamicVector<int> v1(size);
    v1[0] = 0; v1[1] = 1; v1[2] = 2; v1[3] = 3; v1[4] = 4;

    TDynamicVector<int> v2(v1);
    
    EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    const int size = 3;
    TDynamicVector<double> v1(size);
    v1[0] = 0.123; v1[1] = 1.32; v1[2] = 2.1;
    double* p1 = v1.data();

    TDynamicVector<double> v2(v1);
    double* p2 = v2.data();
    
    EXPECT_NE(&p1, &p2);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

/*TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}*/

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    const int size = 3;
    TDynamicVector<char> v(size);

    ASSERT_ANY_THROW(v.at(-5));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    const int size = 10;
    TDynamicVector<long long> v(size);
    
    ASSERT_ANY_THROW(v.at(20));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    const int size = 10;
    TDynamicVector<int> v1(size);
    v1[0] = 0; v1[1] = 1; v1[2] = 2; v1[3] = 3; v1[4] = 4;
    TDynamicVector<int> v2(size);
    v2[0] = 0; v2[1] = 1; v2[2] = 2; v2[3] = 3; v2[4] = 4;

    ASSERT_NO_THROW(v2=v1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    const int size = 5;
    TDynamicVector<int> v1(size);
    v1[0] = 0; v1[1] = 1; v1[2] = 2; v1[3] = 3; v1[4] = 4;
    TDynamicVector<int> v2(size);

    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    const int size1 = 10;
    const int size2 = 1;
    TDynamicVector<int> v1(size1);
    TDynamicVector<int> v2(size2);

    v2 = v1;

    ASSERT_NE(v2.size(), size2);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    const int size1 = 10;
    const int size2 = 1;
    TDynamicVector<int> v1(size1);
    TDynamicVector<int> v2(size2);

    v2 = v1;

    ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    const int size = 10;
    TDynamicVector<int> v1(size);
    v1[0] = 0; v1[1] = 1; v1[2] = 2; v1[3] = 3; v1[4] = 4;
    TDynamicVector<int> v2(size);
    v2[0] = 0; v2[1] = 1; v2[2] = 2; v2[3] = 3; v2[4] = 4;

    ASSERT_EQ(v2 == v1, 1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    const int size = 10;
    TDynamicVector<int> v1(size);
    v1[0] = 0; v1[1] = 1; v1[2] = 2; v1[3] = 3; v1[4] = 4;

    ASSERT_EQ(v1 == v1, 1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    const int size1 = 10;
    const int size2 = 1;

    TDynamicVector<int> v1(size1);
    TDynamicVector<int> v2(size2);

    ASSERT_EQ(v2 != v1, 1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    const int size = 5;
    const int scalar = 5;
    TDynamicVector<int> v2(size);
    for (int i = 0; i < size; i++)
        v2[i] = i + scalar;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;

    v1 = v1 + scalar;
    
    ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    const int size = 5;
    const int scalar = 5;
    TDynamicVector<int> v2(size);
    for (int i = 0; i < size; i++)
        v2[i] = i - scalar;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;

    v1 = v1 - scalar;

    ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    const int size = 5;
    const int scalar = 5;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;
    TDynamicVector<int> v2(size);
    for (int i = 0; i < size; i++)
        v2[i] = i * scalar;

    v1 = v1 * scalar;

    ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    const int size = 5;
    const int scalar = 5;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;
    TDynamicVector<int> v2(size);
    for (int i = 0; i < size; i++)
        v2[i] = 2 * i;
    TDynamicVector<int> v3(size);
    for (int i = 0; i < size; i++)
        v3[i] = 3 * i;

    ASSERT_EQ(v1+v2, v3);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    const int size1 = 10;
    const int size2 = 1;
    TDynamicVector<int> v1(size1);
    TDynamicVector<int> v2(size2);

    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    const int size = 5;
    const int scalar = 5;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;
    TDynamicVector<int> v2(size);
    for (int i = 0; i < size; i++)
        v2[i] = 4 * i;
    TDynamicVector<int> v3(size);
    for (int i = 0; i < size; i++)
        v3[i] = 3 * i;

    ASSERT_EQ(v2 - v1, v3);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    const int size1 = 10;
    const int size2 = 1;
    TDynamicVector<int> v1(size1);
    TDynamicVector<int> v2(size2);

    ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    const int size = 5;
    const int scalar = 5;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;
    TDynamicVector<int> v2(size);
    for (int i = 0; i < size; i++)
        v2[i] = 2 * i;
    int v3 = 0;
    for (int i = 0; i < size; i++)
        v3 += 2 * i * i;

    ASSERT_EQ(v2 * v1, v3);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    const int size1 = 10;
    const int size2 = 1;
    TDynamicVector<int> v1(size1);
    TDynamicVector<int> v2(size2);

    ASSERT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, move_constructor_check)
{
    const int size = 10;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;
    TDynamicVector<int> v3(v1);
    
    TDynamicVector<int> v2(std::move(v1));

    ASSERT_EQ(v2, v3);
    ASSERT_EQ(v1.data(), nullptr);
    ASSERT_EQ(v1.size(), 0);
}

TEST(TDynamicVector, move_opertor_check)
{
    const int size = 10;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;
    TDynamicVector<int> v3(v1);

    TDynamicVector<int> v2 = std::move(v1);

    ASSERT_EQ(v2, v3);
    ASSERT_EQ(v1.data(), nullptr);
    ASSERT_EQ(v1.size(), 0);
}