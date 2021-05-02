#include "gtest/gtest.h"
#include "TStack.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, can_put_elem)
{
	TStack<int> S(5);
	ASSERT_NO_THROW(S.Put(1));
}

TEST(TStack, check_full)
{
	TStack<int> S(4);
	S.Put(1);
	S.Put(2);
	S.Put(3);
	S.Put(4);
	ASSERT_TRUE(S.IsFull());
}

TEST(TStack, get_elem)
{
	TStack<int> S(2);
	S.Put(0);
	S.Put(2);
	ASSERT_EQ(S.Get(), 2);
}

TEST(TStack, throws_when_set_stack_with_too_large_index)
{
	TStack<int> S(2);
	S.Put(1);
	S.Put(2);
	ASSERT_ANY_THROW(S.Put(3));
}
