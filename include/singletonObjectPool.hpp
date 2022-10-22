/**
 * @file
 */

#ifndef TANG_SINGLETONOBJECTPOOL_HPP
#define TANG_SINGLETONOBJECTPOOL_HPP

#include <mutex>
#include <iostream>
using namespace std;
/**
 * The threshold size to use when allocating blocks of data, measured in the
 * number of instances of the object type.
 */
#define GROW 1024

namespace Tang {
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
      if (this->recycledOpen) {
        T* tmp = this->recycled[--this->recycledOpen];
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
      T* newBlock = (T*)malloc(sizeof(T) * GROW);
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

      // Verify that there is room in the current recycled block.
      if (this->recycledOpen == this->recycledSize) {
        // Make room for more recycled.
        T** newRecycled = (T**)realloc(this->recycled, sizeof(T*) * (this->recycledSize + GROW));
        if (!newRecycled) {
          // The realloc() failed.
          this->lock.unlock();
          throw std::bad_alloc();
        }

        // The realloc() succeeded.
        this->recycled = newRecycled;
        this->recycledSize += GROW;
      }

      // Recycle the pointer.
      this->recycled[this->recycledOpen++] = obj;
      this->lock.unlock();
    }

    /**
     * Destructor.
     */
    ~SingletonObjectPool() {
      for (int i = 0; i <= this->currentAllocation; ++i) {
        free (this->allocations[i]);
      }
      free (this->recycled);
    }

  private:
    /**
     * The constructor, hidden from being directly called.
     */
    SingletonObjectPool() : allocations{nullptr}, recycled{nullptr}, currentAllocation{-1}, currentIndex{GROW}, recycledSize{0}, recycledOpen{0} {}

    /**
     * The copy constructor, hidden from being called.
     */
    SingletonObjectPool(const SingletonObjectPool & other) {}

    /**
     * C-array of allocated blocks, each block contains `GROW` objects.
     */
    T** allocations;

    /**
     * C-array of recycled pointers to objects.
     */
    T** recycled;

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
     * Size of the `recycled` array.
     */
    size_t recycledSize;

    /**
     * Index into the `recycled` array of the first open slot.  If
     * `recycledOpen` == `recycledSize`, then `recycled` needs to grow.
     */
    size_t recycledOpen;

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

