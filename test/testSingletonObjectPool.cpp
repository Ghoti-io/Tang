/**
 * @file
 */

#include <gtest/gtest.h>
#include <cstdint>
#include <set>
#include "singletonObjectPool.hpp"

#include <iostream>
using namespace std;

TEST(Singleton, SameForSameType) {
  class A { uint32_t foo; };
  auto & poolA = Tang::SingletonObjectPool<A>::getInstance();
  auto & poolB = Tang::SingletonObjectPool<A>::getInstance();
  EXPECT_EQ((void*)&poolA, (void*)&poolB);
}

TEST(Singleton, DifferentForDifferentTypes) {
  class A { uint32_t foo; };
  class B { uint32_t foo; };
  auto & poolA = Tang::SingletonObjectPool<A>::getInstance();
  auto & poolB = Tang::SingletonObjectPool<B>::getInstance();
  EXPECT_NE((void*)&poolA, (void*)&poolB);
}

TEST(Get, SuccessiveCallsProduceDifferentMemoryAddresses) {
  class A { uint32_t foo; };
  auto & poolA = Tang::SingletonObjectPool<A>::getInstance();
  auto objA = poolA.get();
  auto objB = poolA.get();
  EXPECT_NE(objA, objB);
}

TEST(Recycle, RecycledObjectIsReused) {
  class A { uint32_t foo; };
  auto & poolA = Tang::SingletonObjectPool<A>::getInstance();
  auto objA = poolA.get();
  poolA.recycle(objA);
  auto objB = poolA.get();
  EXPECT_EQ(objA, objB);
  auto objC = poolA.get();
  [[maybe_unused]] auto objD = poolA.get();
  poolA.recycle(objC);
  objA = poolA.get();
  EXPECT_NE(objA, objB);
  EXPECT_EQ(objA, objC);
}

TEST(Get, SuccessiveCallsAreSequential) {
  class A { uint32_t foo; };
  auto & poolA = Tang::SingletonObjectPool<A>::getInstance();
  auto objA = poolA.get();
  auto objB = poolA.get();
  EXPECT_EQ((char*)objB - (char*)objA, sizeof(A));
}

TEST(Get, KeepsGeneratingDifferentPointers) {
  class A { uint32_t foo; };
  auto & poolA = Tang::SingletonObjectPool<A>::getInstance();
  set<A*> bucket;
  for (int i = 0; i < 2000; ++i) {
    bucket.insert(poolA.get());
  }
  EXPECT_EQ(bucket.size(), 2000);
}

TEST(Recycle, WorksAfterLargeNumberOfAllocations) {
  class A { uint32_t foo; };
  auto & poolA = Tang::SingletonObjectPool<A>::getInstance();
  set<A*> bucket;
  for (int i = 0; i < 2000; ++i) {
    bucket.insert(poolA.get());
  }
  for (auto it = bucket.begin(); it != bucket.end(); ++it) {
    poolA.recycle(*it);
  }
  for (int i = 0; i < 2000; ++i) {
    bucket.insert(poolA.get());
  }
  EXPECT_EQ(bucket.size(), 2000);
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

