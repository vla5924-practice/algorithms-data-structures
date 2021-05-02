#include "gtest/gtest.h"
#include "TMultiStack.h"

TEST(TMultiStack, can_create_mstack_with_positive_length)
{
	ASSERT_NO_THROW(TMultiStack<int> s(3, 3));
}

TEST(TMultiStack, cant_create_mstack_with_zero_length)
{
	ASSERT_ANY_THROW(TMultiStack<int> s(0));
}

TEST(TMultiStack, check_empty_mstack)
{
	TMultiStack<int> s(3, 3);
	ASSERT_TRUE(s.IsEmpty(1));
}

TEST(TMultiStack, check_for_non_existent_empty_mstack)
{
	TMultiStack<int> s(3, 3);
	ASSERT_ANY_THROW(s.IsEmpty(4));
}

TEST(TMultiStack, check_negative_empty_mstack)
{
	TMultiStack<int> s(3, 3);
	ASSERT_ANY_THROW(s.IsEmpty(-1));
}

TEST(TMultiStack, check_full_mstack)
{
	TMultiStack<int> s(3, 3);
	ASSERT_FALSE(s.IsFull(1));
}

TEST(TMultiStack, check_for_non_existent_full_mstack)
{
	TMultiStack<int> s(3, 3);
	ASSERT_ANY_THROW(s.IsFull(4));
}

TEST(TMultiStack, check_negative_full_mstack)
{
	TMultiStack<int> s(3, 3);
	ASSERT_ANY_THROW(s.IsFull(-1));
}

TEST(TMultiStack, can_put_with_mem)
{
	TMultiStack<int> s(3, 3);
	ASSERT_NO_THROW(s.Put(1, 1));
}

TEST(TMultiStack, cant_put_with_no_mem)
{
	TMultiStack<int> s(3, 3);
	ASSERT_ANY_THROW(s.Put(1, 4));
}

TEST(TMultiStack, can_get)
{
	TMultiStack<int> s(3, 3);
	s.Put(1, 1);
	ASSERT_NO_THROW(s.Get(1));
}

TEST(TMultiStack, cant_get_nonexistent)
{
	TMultiStack<int> s(3, 3);
	s.Put(1, 1);
	ASSERT_ANY_THROW(s.Get(4));
}

TEST(TMultiStack, cant_get_negative)
{
	TMultiStack<int> s(3, 3);
	s.Put(1, 1);
	ASSERT_ANY_THROW(s.Get(-1));
}

TEST(TMultiStack, can_GetSize)
{
	TMultiStack<int> s(3, 3);
	ASSERT_NO_THROW(s.GetSize());
}

TEST(TMultiStack, can_resize)
{
	TMultiStack<int> s(1, 1);
	s.Put(1, 0);
	ASSERT_NO_THROW(s.Resize(10, 0));
}

TEST(TMultiStack, cant_resize_negative)
{
	TMultiStack<int> s(1, 1);
	s.Put(1, 0);
	ASSERT_ANY_THROW(s.Resize(-1, 0));
}

TEST(TMultiStack, can_do_stack_relocation)
{
	TMultiStack<int> s(3, 3);
	s.Put(1, 0);
	s.Put(2, 1);
	s.Put(3, 1);
	s.Put(4, 1);
	ASSERT_NO_THROW(s.Put(1, 1));
}
