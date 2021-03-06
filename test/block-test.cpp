#include <gtest/gtest.h>

#include <concrete/arena.hpp>
#include <concrete/block.hpp>

using namespace concrete;

namespace {

TEST(block, size)
{
#ifdef CONCRETE_BLOCK_MAGIC
	EXPECT_EQ(8, sizeof (Block));
#else
	EXPECT_EQ(4, sizeof (Block));
#endif
}

TEST(arena, alloc_min)
{
	Arena arena;

	BlockId id = arena.alloc(sizeof (Block));
	Block *ptr = arena.pointer(id);
	EXPECT_TRUE(ptr);
	EXPECT_EQ(ptr->block_size(), sizeof (Block));
	// leak the block
}

TEST(arena, alloc_big)
{
	Arena arena;

	Block *ptr = arena.pointer(arena.alloc(131072));
	EXPECT_TRUE(ptr);
	EXPECT_EQ(ptr->block_size(), 131072);
	arena.free(ptr);
}

TEST(arena, alloc_odd_multi)
{
	Arena arena;

	for (int pass = 0; pass < 2; pass++) {
		BlockId block[10];

		for (int i = 0; i < 10; i++) {
			int size = sizeof (Block) + i * 4 + (((i + pass) & 1) ? 1 : 3);
			block[i] = arena.alloc(size);
			Block *ptr = arena.pointer(block[i]);
			EXPECT_TRUE(ptr);
			EXPECT_EQ(uintptr_t(ptr) & 3, 0);
			EXPECT_EQ(ptr->block_size(), size);

			for (int prev = 0; prev < i; prev++)
				EXPECT_NE(block[i], block[prev]);
		}

		for (int i = 3; i < 10; i++) // leak the first 3
			arena.free(arena.pointer(block[i]));
	}
}

} // namespace
