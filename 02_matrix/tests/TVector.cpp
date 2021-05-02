#include "gtest/gtest.h"
#include "TVector.h"

TEST(TVector, can_create_vector)
{
	ASSERT_NO_THROW(TVector<int> v(3));
}

TEST(TVector, throws_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TVector<int> v(-1));
}

TEST(TVector, throws_create_vector_with_negative_startindex)
{
	ASSERT_ANY_THROW(TVector<int> v(3, -1));
}

TEST(TVector, can_create_copied_vector)
{
	TVector<int> v(3);

	ASSERT_NO_THROW(TVector<int> vv(v));
}

TEST(TVector, can_get_size)
{
	TVector<int> v(3);

	ASSERT_EQ(v.GetSize(), 3);
}

TEST(TVector, can_get_start_index)
{
	TVector<int> v(3, 1);

	ASSERT_EQ(1, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(3);
	v[0] = 2;

	ASSERT_EQ(2, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(3);
	ASSERT_ANY_THROW(v[-1] = 1);
}

TEST(TVector, compare_equal_vectors)
{
	TVector<int> v(3), vv(3);
	for (int i = 0; i < 3; i++)
		v[i] = 1;
	for (int i = 0; i < 3; i++)
		vv[i] = 1;
	ASSERT_TRUE(vv == v);
}

TEST(TVector, compare_vector_with_itself)
{
	TVector<int> v(3);
	for (int i = 0; i < 3; i++)
		v[i] = 1;
	ASSERT_TRUE(v == v);
}

TEST(TVector, vectors_are_not_equal)
{
	TVector<int> v(3), vv(4);
	ASSERT_FALSE(v == vv);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v(3);
	for (int i = 0; i < 3; i++)
		v[i] = 1;
	TVector<int> s(3);
	s = v + 2;
	TVector<int> r(3);
	for (int i = 0; i < 3; i++)
		r[i] = 3;
	ASSERT_TRUE(s == r);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(3);
	for (int i = 0; i < 3; i++)
		v[i] = 3;
	TVector<int> s(3);
	s = v - 2;
	TVector<int> r(3);
	for (int i = 0; i < 3; i++)
		r[i] = 1;
	ASSERT_TRUE(s == r);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(3);
	for (int i = 0; i < 3; i++)
		v[i] = 3;
	TVector<int> m(3);
	m = v * 2;
	TVector<int> r(3);
	for (int i = 0; i < 3; i++)
		r[i] = 6;
	ASSERT_TRUE(m == r);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v(3), vv(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	vv[0] = 2;
	vv[1] = 3;
	vv[2] = 4;
	TVector<int> s(3);
	s = v + vv;
	TVector<int> r(3);
	r[0] = 3;
	r[1] = 5;
	r[2] = 7;
	ASSERT_TRUE(s == r);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v(3), vv(4);
	ASSERT_ANY_THROW(v + vv);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v(3), vv(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	vv[0] = 2;
	vv[1] = 3;
	vv[2] = 4;
	TVector<int> s(3);
	s = vv - v;
	TVector<int> r(3);
	r[0] = 1;
	r[1] = 1;
	r[2] = 1;
	ASSERT_TRUE(s == r);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v(3), vv(4);
	ASSERT_ANY_THROW(v - vv);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v(3), vv(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	vv[0] = 2;
	vv[1] = 3;
	vv[2] = 4;
	int m;
	m = v * vv;
	int r = 20;
	ASSERT_TRUE(m == r);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v(3), vv(4);
	ASSERT_ANY_THROW(v * vv);
}
