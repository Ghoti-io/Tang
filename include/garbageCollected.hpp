/**
 * @file
 * Declare the Tang::GarbageCollected class.
 */

namespace Tang {
  class GarbageCollected;
}

#ifndef TANG_GARBAGECOLLECTED_HPP
#define TANG_GARBAGECOLLECTED_HPP

#include <functional>
#include "singletonObjectPool.hpp"
#include "computedExpression.hpp"
#include "error.hpp"

namespace Tang {
  /**
   * A container that acts as a resource-counting garbage collector for the
   * specified type.
   *
   * Uses the \ref SingletonObjectPool to created and recycle object memory.
   * The container is not thread-safe.
   */
  class GarbageCollected {
  public:
    /**
     * Creates a garbage-collected object of the specified type.
     *
     * @param variable The arguments to pass to the constructor of the
     *   specified type.
     * @return A GarbageCollected object.
     */
    template<class T, typename... Args>
    static GarbageCollected make(Args... args) {
      GarbageCollected gc{};
      auto temp = SingletonObjectPool<T>::getInstance().get();
      gc.ref = new(temp) T{args...};
      gc.count = new size_t{1};
      gc.recycle = [temp](){
        SingletonObjectPool<T>::getInstance().recycle(temp);
      };
      return gc;
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
      this->recycle = other.recycle;
    }

    /**
     * Move Constructor.
     *
     * @param The other GarbageCollected object to move.
     */
    GarbageCollected(GarbageCollected && other) {
      // Move the other item's attributes.
      this->ref = other.ref;
      this->count = other.count;
      ++*this->count;
      this->recycle = std::move(other.recycle);
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
      this->recycle = other.recycle;

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
      this->recycle = std::move(other.recycle);

      return *this;
    }

    /**
     * Destructor.  Clean up the tracked object, if appropriate.
     */
    ~GarbageCollected() {
      if (--*this->count == 0) {
        if (this->ref) {
          this->recycle();
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
    ComputedExpression* operator->() const {
      return this->ref;
    }

    /**
     * Access the tracked object.
     *
     * @return A reference to the tracked object.
     */
    ComputedExpression& operator*() const {
      return *this->ref;
    }

    /**
     * Compare the GarbageCollected tracked object with a supplied value.
     *
     * @param val The value to compare the tracked object against.
     * @return True if they are equal, false otherwise.
     */
    bool operator==(const int & val) const;

    /**
     * Compare the GarbageCollected tracked object with a supplied value.
     *
     * @param val The value to compare the tracked object against.
     * @return True if they are equal, false otherwise.
     */
    bool operator==(const double & val) const;

    /**
     * Compare the GarbageCollected tracked object with a supplied value.
     *
     * @param val The value to compare the tracked object against.
     * @return True if they are equal, false otherwise.
     */
    bool operator==(const Error & val) const;

    /**
     * Add friendly output.
     *
     * @param out The output stream.
     * @param gc The GarbageCollected value.
     * @return The output stream.
     */
    friend std::ostream & operator<<(std::ostream & out, const GarbageCollected & gc);

    /**
     * Perform an addition between two GarbageCollected values.
     *
     * @param rhs The right hand side operand.
     * @return The result of the operation.
     */
    GarbageCollected operator+(const GarbageCollected & rhs) const;

    /**
     * Perform a subtraction between two GarbageCollected values.
     *
     * @param rhs The right hand side operand.
     * @return The result of the operation.
     */
    GarbageCollected operator-(const GarbageCollected & rhs) const;

    /**
     * Perform a multiplication between two GarbageCollected values.
     *
     * @param rhs The right hand side operand.
     * @return The result of the operation.
     */
    GarbageCollected operator*(const GarbageCollected & rhs) const;

    /**
     * Perform a division between two GarbageCollected values.
     *
     * @param rhs The right hand side operand.
     * @return The result of the operation.
     */
    GarbageCollected operator/(const GarbageCollected & rhs) const;

    /**
     * Perform a modulo between two GarbageCollected values.
     *
     * @param rhs The right hand side operand.
     * @return The result of the operation.
     */
    GarbageCollected operator%(const GarbageCollected & rhs) const;

    /**
     * Perform a negation on the  GarbageCollected value.
     *
     * @return The result of the operation.
     */
    GarbageCollected operator-() const;

  protected:
    /**
     * Constructs a garbage-collected object of the specified type.  It is
     * private so that a GarbageCollected object can only be created using the
     * \ref GarbageCollected::make() function.
     *
     * @param variable The arguments to pass to the constructor of the
     *   specified type.
     */
    GarbageCollected() : count{nullptr}, ref{nullptr}, recycle{} {}

    /**
     * The count of references to the tracked object.
     */
    size_t * count;

    /**
     * A reference to the tracked object.
     */
    ComputedExpression* ref;

    /**
     * A cleanup function to recycle the object.
     */
    std::function<void(void)> recycle;
  };
}

#endif // TANG_GARBAGECOLLECTED_HPP

