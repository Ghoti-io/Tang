/**
 * @file
 * Declare the Tang::SingletonObjectPool class.
 */

#ifndef TANG_SINGLETONOBJECTPOOL_HPP
#define TANG_SINGLETONOBJECTPOOL_HPP

#include <mutex>
#include <iostream>

/**
 * The threshold size to use when allocating blocks of data, measured in the
 * number of instances of the object type.
 */
#define GROW 1024

namespace Tang {
  /**
   * A thread-safe, singleton object pool of the designated type.
   */
  template <class T>
  class SingletonObjectPool {
  public:
    /**
     * Get the singleton instance of the object pool.
     *
     * @return The singleton instance of the object pool.
     */
    static SingletonObjectPool<T>& getInstance() {
      static SingletonObjectPool<T> pool{};
      return pool;
    }

    /**
     * Request an uninitialized memory location from the pool for an object T.
     *
     * @return An uninitialized memory location for an object T.
     */
    T* get() {
      this->lock.lock();

      // If there is a recycled object available, return it first.
      if (this->currentRecycledAllocation != -1) {
        // Get the block of recycled pointers.
        T** recycled = (T**)&this->allocations[this->currentRecycledAllocation][GROW];

        // Get the pointer to be returned.
        T* tmp = recycled[this->currentRecycledIndex--];

        // Decrement the `currentRecycledIndex` and adjust if necessary.
        if (this->currentRecycledIndex < 0) {
          --this->currentRecycledAllocation;
          this->currentRecycledIndex = GROW - 1;
        }
        this->lock.unlock();
        return tmp;
      }

      // There wasn't a recycled object available.  Check to see if there is an
      // allocation pool memory address available.
      if (this->currentIndex < GROW) {
        // There is a memory address available at `currentIndex`.
        T* tmp = &this->allocations[this->currentAllocation][this->currentIndex++];
        this->lock.unlock();
        return tmp;
      }

      // There's not any allocation pool memory available, so we need to
      // allocate more.
      T* newBlock = (T*)malloc((sizeof(T) * GROW) + (sizeof(T*) * GROW));
      if (!newBlock) {
        // The malloc() failed.
        this->lock.unlock();
        throw std::bad_alloc();
      }
      T** newAllocation = (T**)realloc(this->allocations, sizeof(T*) * (this->currentAllocation + 2));
      if (!newAllocation) {
        // The realloc() failed. Clean up and throw an exception.
        this->lock.unlock();
        free (newBlock);
        throw std::bad_alloc();
      }

      // The allocation succeeded.  Wire up all of the pointers.
      this->allocations = newAllocation;
      ++this->currentAllocation;
      this->allocations[this->currentAllocation] = newBlock;
      this->currentIndex = 1;
      T* tmp = &this->allocations[this->currentAllocation][0];
      this->lock.unlock();
      return tmp;
    }

    /**
     * Recycle a memory location for an object T.
     *
     * @param obj The memory location to recycle.
     */
    void recycle(T* obj) {
      this->lock.lock();

      // TODO: Verify that there is room in the current recycled block.
      // ASSERT(this->currentRecycledAllocation != -1);

      if (++this->currentRecycledIndex == GROW) {
        this->currentRecycledIndex = 0;
        ++this->currentRecycledAllocation;
      }

      // Get the block of recycled pointers.
      T** recycled = (T**)&this->allocations[this->currentRecycledAllocation][GROW];
      recycled[this->currentRecycledIndex] = obj;

      this->lock.unlock();
    }

    /**
     * Destructor.
     */
    ~SingletonObjectPool() {
      // It is possible that an object pool was created (via the templated
      // get() function) but never used.  Don't free memory unless it was
      // actually allocated in the first place.
      if (this->allocations) {
        // Free all of the allocation pages.
        for (int i = 0; i <= this->currentAllocation; ++i) {
          free (this->allocations[i]);
        }
        free (this->allocations);
      }
    }

  private:
    /**
     * The constructor, hidden from being directly called.
     */
    SingletonObjectPool() : allocations{nullptr}, /*recycled{nullptr},*/ currentAllocation{-1}, currentIndex{GROW}, currentRecycledAllocation{-1}, currentRecycledIndex{GROW - 1} {}

    /**
     * The copy constructor, hidden from being called.
     */
    SingletonObjectPool(const SingletonObjectPool & other) {}

    /**
     * C-array of allocated blocks, each block contains `GROW` objects.
     */
    T** allocations;

    /**
     * Index into `allocations`, representing the current block supplying
     * non-recycled memory addresses.
     */
    int currentAllocation;

    /**
     * Current location (within the most recently allocated block) of an
     * available T*.  If currentIndex == GROW, then a new block needs to be
     * allocated.
     */
    size_t currentIndex;

    /**
     * Index into `allocations`, representing the current block tracking the
     * recycled memory addresses.
     */
    int currentRecycledAllocation;

    /**
     * Current location (within the `currentRecycledAllocation` block) of the
     * last available T*.  If currentRecycledIndex == GROW, then we must move
     * to the next currentRecycledAllocation.
     */
    int currentRecycledIndex;

    /**
     * A mutex for thread-safety.
     */
    static std::mutex lock;
  };

  template <class T>
  std::mutex SingletonObjectPool<T>::lock;
}

#undef GROW

#endif //TANG_SINGLETONOBJECTPOOL_HPP

