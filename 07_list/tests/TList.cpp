#include "gtest/gtest.h"
#include "TList.h"

TEST(TList, can_create_list)
{
	ASSERT_NO_THROW(TList<int> l);
}

TEST(TList, can_copy_list)
{
	TList<int> l;
	ASSERT_NO_THROW(TList<int> l2(l));
}

TEST(TList, can_insert_elem_in_first_list)
{
	TList<int> l;
	ASSERT_NO_THROW(l.InsFirst(10));
}

TEST(TList, can_insert_elem_in_last_list)
{
	TList<int> l;
	ASSERT_NO_THROW(l.InsLast(10));
}

TEST(TList, check_is_empty)
{
	TList<int> l;
	ASSERT_TRUE(l.IsEmpty());
}

TEST(TList, can_get_elem_first)
{
	TList<int> l;
	l.InsFirst(1);
	ASSERT_NO_THROW(l.GetFirst());
}

TEST(TList, can_get_elem_last)
{
	TList<int> l;
	l.InsLast(1);
	l.InsLast(2);
	ASSERT_NO_THROW(l.GetLast());
}

TEST(TList, can_del_elem_first)
{
	TList<int> l;
	l.InsLast(1);
	l.InsLast(2);
	ASSERT_NO_THROW(l.DelFirst());
}

TEST(TList, can_del_elem_last)
{
	TList<int> l;
	l.InsFirst(1);
	l.InsLast(2);
	ASSERT_NO_THROW(l.DelLast());
}

TEST(TList, can_get_count)
{
	TList<int> l;
	l.InsLast(1);
	l.InsLast(2);
	ASSERT_EQ(l.GetCount(), 2);
}
