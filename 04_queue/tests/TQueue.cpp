#include "gtest/gtest.h"
#include "TQueue.h"

TEST(TQueue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int> q(3));
}

TEST(TQueue, cant_create_queue_with_zero_len)
{
	ASSERT_ANY_THROW(TQueue<int> q(0));
}


TEST(TQueue, create_empty_queue)
{
	TQueue<int> q(3);
	ASSERT_TRUE(q.IsEmpty());
}

TEST(TQueue, can_push_if_ok)
{
	TQueue<int> q(3);
	ASSERT_NO_THROW(q.Put(3));
}

TEST(TQueue, can_get_elem)
{
	TQueue<int> q(2);
	q.Put(4);
	ASSERT_EQ(4, q.Get());
}

TEST(TQueue, cant_get_if_empty)
{
	TQueue<int> q(1);
	ASSERT_ANY_THROW(q.Get());
}
