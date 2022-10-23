/**
 * @file
 */

#ifndef TANG_GARBAGECOLLECTED_HPP
#define TANG_GARBAGECOLLECTED_HPP

#include "singletonObjectPool.hpp"

namespace Tang {
  /**
   * A container that acts as a resource-counting garbage collector for the
   * specified type.
   *
   * Uses the \ref SingletonObjectPool to created and recycle object memory.
   * The container is not thread-safe.
   */
  template <class T>
  class GarbageCollected {
  public:
    /**
     * Constructs a garbage-collected object of the specified type.
     *
     * @param variable The arguments to pass to the constructor of the
     *   specified type.
     */
    template<typename... Args>
    GarbageCollected(Args... args) {
      auto temp = SingletonObjectPool<T>::getInstance().get();
      this->ref = new(temp) T{args...};
      this->count = new size_t{1};
    }

    /**
     * Copy Constructor.
     *
     * @param The other GarbageCollected object to copy.
     */
    GarbageCollected(const GarbageCollected & other) {
      this->count = other.count;
      ++*this->count;
      this->ref = other.ref;
    }

    /**
     * Move Constructor.
     *
     * @param The other GarbageCollected object to move.
     */
    GarbageCollected(GarbageCollected && other) {
      // Remove references from the current object.
      this->~GarbageCollected();

      // Move the other item's attributes.
      this->ref = other.ref;
      this->count = other.count;
      ++*this->count;
    }

    /**
     * Copy Assignment.
     *
     * @param The other GarbageCollected object.
     */
    GarbageCollected & operator=(const GarbageCollected & other) {
      // Remove references from the current object.
      this->~GarbageCollected();

      // Copy the other item's attributes.
      this->ref = other.ref;
      this->count = other.count;
      ++*this->count;

      return *this;
    }

    /**
     * Move Assignment.
     *
     * @param The other GarbageCollected object.
     */
    GarbageCollected & operator=(GarbageCollected && other) {
      // Remove references from the current object.
      this->~GarbageCollected();

      // Move the other item's attributes.
      this->ref = other.ref;
      this->count = other.count;
      ++*this->count;

      return *this;
    }

    /**
     * Destructor.  Clean up the tracked object, if appropriate.
     */
    ~GarbageCollected() {
      if (--*this->count == 0) {
        if (this->ref) {
          SingletonObjectPool<T>::getInstance().recycle(this->ref);
        }
        if (this->count) {
          delete this->count;
        }
      }
    }

    /**
     * Access the tracked object as a pointer.
     *
     * @return A pointer to the tracked object.
     */
    T* operator->() const {
      return this->ref;
    }

    /**
     * Access the tracked object.
     *
     * @return A reference to the tracked object.
     */
    T& operator*() const {
      return *this->ref;
    }

  private:
    /**
     * The count of references to the tracked object.
     */
    size_t * count;

    /**
     * A reference to the tracked object.
     */
    T* ref;
  };
}

#endif // TANG_GARBAGECOLLECTED_HPP

