#include "gtest/gtest.h"
#include "TStack.h"

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_put_elem)
{
	TStack<int> S;
	ASSERT_NO_THROW(S.Put(1));
}

TEST(TStack, get_elem)
{
	TStack<int> S;
	S.Put(1);
	S.Put(2);
	ASSERT_EQ(S.Get(), 2);
}

TEST(TStack, check_empty_if_yes)
{
	TStack<int> S;
	ASSERT_TRUE(S.IsEmpty());
}

TEST(TStack, check_empty_if_not)
{
	TStack<int> S;
	S.Put(1);
	S.Put(2);
	ASSERT_FALSE(S.IsEmpty());
}
