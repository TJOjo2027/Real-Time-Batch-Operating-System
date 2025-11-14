#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>
#include <cassert>

using namespace std;

/*************************
 * INSERT YOUR CODE HERE *
 *************************/

/**
 * ArrayHeap
 *
 * This function creates the ArrayHeap object that will be used
 * in the driver in order to store the data and act as a priority
 * queue to call upon the highest priority data the quickest.
 *
 * Parameters:
*   NONE
 *
 * Return value: creates a new object of type ArrayHeap
 */
template <typename T>
ArrayHeap<T>::ArrayHeap() {
    capacity = 10;
    numItems = 0;
    data = new T[capacity];
    heapAndFreeStack = new int[capacity];

    // populate with indexes
    for (int i = 0; i < capacity; i++) {
        heapAndFreeStack[i] = i;
    }
}

/**
 * ArrayHeap (copy constructor)
 *
 * This function implements the copy constructor for the ArrayHeap
 * class. The function handles allocation of new "copied" data from
 * one object, to another
 *
 * Parameters:
*   h: the ArrayHeap instruction because copied from.
 *
 * Return value: no return, but alters the memory of the object to be exactly
 * like the parameter object.
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h) {
    capacity = h.capacity;
    numItems = h.numItems;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];

    for (int i = 0; i < capacity; i++) {
        data[i] = h.data[i];
    }

    for (int i = 0; i < capacity; i++) {
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
    }
}

/**
 * ~ArrayHeap
 *
 * This function handles the destruction of the dynamically allocated
 * data being used in the ArrayHeap objects
 *
 * Parameters:
*   NONE
 *
 * Return value: nothing, but handles the memory of the object
 * when it goes out of scope.
 */
template <typename T>
ArrayHeap<T>::~ArrayHeap() {
    delete[] data;
    data = nullptr;
    delete[] heapAndFreeStack;
    heapAndFreeStack = nullptr;
    numItems = 0;
    capacity = 0;
}

/**
 * getMinItem
 *
 * This function returns the minimum item from the ArrayHeap,
 * which in reality is the object in data that has the index of
 * heapAndFreeStack[0].
 *
 * Parameters:
*   NONE
 *
 * Return value: the data of templated type (Process in this
 * case) that is of highest priority in the ArrayHeap.
 */
template <typename T>
T const &ArrayHeap<T>::getMinItem() const {
    assert((numItems > 0) && "ArrayHeap is empty");
    return data[heapAndFreeStack[0]];

}

/**
 * getNumItems
 *
 * This function is a getter for the ArrayHeap class that
 * returns the data member of number of items in the ArrayHeap.
 *
 * Parameters:
*   NONE
 *
 * Return value: an int containing the number of items in the
 * ArrayHeap.
 */
template <typename T>
int ArrayHeap<T>::getNumItems() const {
    return numItems;
}

/**
 * bubbleUp
 *
 * This function performs the bubbleUp process, which starts at
 * an index and balances the heap according to the heap properties
 * from a lower lever going up.
 *
 * Parameters:
*   ndx: the index used to start the bubble up process
 *
 * Return value: nothing, but re-balances a heap after an insert.
 */
template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx) {
    while (ndx > 0) {
        int parentIndex = (ndx - 1) / 2;

        if (data[heapAndFreeStack[ndx]] <
            data[heapAndFreeStack[parentIndex]]) {

            swap(heapAndFreeStack[ndx],
                heapAndFreeStack[parentIndex]);

            ndx = parentIndex;
        }
        // case where we achieve heap property
        else {
            break;
        }
    }
}

/**
 * bubbleDown
 *
 * This function performs the bubble down operation, where
 * an object that is of lower priority is a parent to an object
 * of higher priority. This breaks the heap rules, and due to this
 * a bubble down must occur where the lower priority item moves to
 * where it actually belongs on the heap.
 *
 * Parameters:
*   ndx: the index where the bubble down will begin.
 *
 * Return value: nothing, but "re-balances" the heap after a
 * remove, where a lower priority object needs to be moved down.
 */
template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx) {
    int leftChild = (2 * ndx) + 1;
    int rightChild = (2 * ndx) + 2;
    // used to check and assign new location
    int currentIndex = ndx;

    while (leftChild < numItems) {
        // check right child to see if it's smaller than the current
        if ((rightChild < numItems) &&
            data[heapAndFreeStack[rightChild]] < data[heapAndFreeStack[currentIndex]]) {
            currentIndex = rightChild;
        }

        // check left child to see if it's smaller than the current
        if ((leftChild < numItems) &&
            data[heapAndFreeStack[leftChild]] < data[heapAndFreeStack[currentIndex]]) {
            currentIndex = leftChild;
        }

        // if current doesn't raise any flags, there are either no children
        // or logic is done
        if (currentIndex == ndx) {
            break;
        }

        // swap the orientations of the heapAndFreeStack
        swap(heapAndFreeStack[ndx], heapAndFreeStack[currentIndex]);

        // move a layer down in the "tree"
        ndx = currentIndex;

        // prepare for next loop w/ new ndx
        leftChild = (2 * ndx) + 1;
        rightChild = (2 * ndx) + 2;
        currentIndex = ndx;
    }
}

/**
 * insert
 *
 * This function inserts an item into the ArrayHeap. Contained inside
 * the function are operations to ensure that the heap maintains it properties
 * after the insert is done.
 *
 * Parameters:
*   item: the data of templated type T, (in this case Process) that
*   will be inserted into the ArrayHeap
 *
 * Return value: nothing, but inserts data into the ArrayHeap, growing
 * it.
 */
template <typename T>
void ArrayHeap<T>::insert(T const &item) {
    if (numItems == capacity) {
        doubleCapacity();
    }

    // go to the nearest free index
    int newDataIndex = heapAndFreeStack[numItems];
    data[newDataIndex] = item;

    // bubbles up from right most leaf
    bubbleUp(numItems);
    numItems++;
}

/**
 * removeMinItem
 *
 * This function removes the highest priority item from "data memory".
 * This is done by swapping the "root" with the right most "leaf" and
 * decrementing the number of items in the ArrayHeap, essentially
 * simulating the deletion of that item.
 *
 * Parameters:
*   NONE
 *
 * Return value: nothing, but essentially removes the highest
 * priority item from the ArrayHeap.
 */
template <typename T>
void ArrayHeap<T>::removeMinItem() {
    assert(numItems > 0 && "ArrayHeap is empty");

    // swap the root index with the right most child
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems - 1]);
    numItems--;

    // bubble down from root
    bubbleDown(0);
}

/**
 * doubleCapacity
 *
 * This function doubles the capacity of the memory, which is
 * actually the data (holds the processes) and the
 * HeapAndFreeStack (holding the indexes of the objects in data).
 *
 * Parameters:
*   NONE
 *
 * Return value: nothing, but expands the ArrayHeap so that more
 * data can be contained.
 */
template <typename T>
void ArrayHeap<T>::doubleCapacity() {
    int newCapacity = capacity * 2;

    T *newData = new T[newCapacity];
    int *newHeapAndFreeStack = new int[newCapacity];

    // load data
    for (int i = 0; i < capacity; i++) {
        newData[i] = data[i];
    }

    // load H&FS data
    for (int i = 0; i < newCapacity; i++) {
        if (i < numItems) {
            newHeapAndFreeStack[i] = heapAndFreeStack[i];
        }
        // load the new indexes
        else {
            newHeapAndFreeStack[i] = i;
        }
    }

    delete[] data;
    delete[] heapAndFreeStack;

    // set all the protected elements to their new values
    data = newData;
    heapAndFreeStack = newHeapAndFreeStack;
    capacity = newCapacity;

}

/**
 * operator=
 *
 * This function overloads the assignment operator so that calling
 * it on another ArrayHeap object can properly assign one object with
 * another object's values.
 *
 * Parameters:
*   ah: the ArrayHeap object being used to assign data.
 *
 * Return value: returns an ArrayHeap of templated type that now holds
 * the correct data of the object that it was assigned to.
 */
template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah) {
    if (this != &ah) {
        delete[] data;
        delete[] heapAndFreeStack;

        capacity = ah.capacity;
        numItems = ah.numItems;

        data = new T[capacity];
        heapAndFreeStack = new int[capacity];

        for (int i = 0; i < capacity; i++) {
            data[i] = ah.data[i];
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
        }
    }
    return *this;
}

#endif
