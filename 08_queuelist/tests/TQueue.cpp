#include "gtest/gtest.h"
#include "TQueue.h"

TEST(TQueue, can_create_queue)
{
	ASSERT_NO_THROW(TQueue<int> q);
}

TEST(TQueue, create_empty_queue)
{
	TQueue<int> q;
	ASSERT_TRUE(q.IsEmpty());
}

TEST(TQueue, can_push_if_ok)
{
	TQueue<int> q;
	ASSERT_NO_THROW(q.Put(3));
}

TEST(TQueue, can_get_elem)
{
	TQueue<int> q;
	q.Put(4);
	ASSERT_EQ(4, q.Get());
}

TEST(TQueue, cant_get_if_empty)
{
	TQueue<int> q;
	ASSERT_ANY_THROW(q.Get());
}
