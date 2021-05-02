#include "gtest/gtest.h"
#include "TArrayList.h"

TEST(TArrayList, can_create_list)
{
	ASSERT_NO_THROW(TArrayList<int> l);
}

TEST(TArrayList, can_copy_list)
{
	TArrayList<int> l;
	ASSERT_NO_THROW(TArrayList<int> l2(l));
}

TEST(TArrayList, can_insert_elem_in_first_list)
{
	TArrayList<int> l;
	ASSERT_NO_THROW(l.InsFirst(1));
}

TEST(TArrayList, can_insert_elem_in_last_list)
{
	TArrayList<int> l;
	ASSERT_NO_THROW(l.InsLast(1));
}

TEST(TArrayList, check_is_full)
{
	TArrayList<int> l;
	ASSERT_FALSE(l.IsFull());
}

TEST(TArrayList, check_is_empty)
{
	TArrayList<int> l;
	ASSERT_TRUE(l.IsEmpty());
}

TEST(TArrayList, can_get_elem_first)
{
	TArrayList<int> l;
	l.InsFirst(1);
	ASSERT_NO_THROW(l.GetFirst());
}

TEST(TArrayList, can_get_elem_last)
{
	TArrayList<int> l;
	l.InsLast(1);
	l.InsLast(2);
	ASSERT_NO_THROW(l.GetLast());
}

TEST(TArrayList, can_del_elem_first)
{
	TArrayList<int> l;
	l.InsLast(1);
	l.InsLast(2);
	ASSERT_NO_THROW(l.DelFirst());
}

TEST(TArrayList, can_del_elem_last)
{
	TArrayList<int> l;
	l.InsLast(1);
	l.InsLast(2);
	ASSERT_NO_THROW(l.DelLast());
}

TEST(TArrayList, can_get_count)
{
	TArrayList<int> l;
	l.InsLast(1);
	l.InsLast(2);
	ASSERT_EQ(2, l.GetCount());
}
