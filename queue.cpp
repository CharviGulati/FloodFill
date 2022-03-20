/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template<class T>
void Queue<T>::enqueue(T const &newItem) {
    stack_1.push(newItem);
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
template<class T>
T Queue<T>::dequeue() {
    //  if s2 is empty, then move everything from s1 to s2
    if (stack_2.isEmpty()) {
        while (!stack_1.isEmpty())
            stack_2.push(stack_1.pop());
    }
    // if s2 is NOT empty, then return everything from queue
    return stack_2.pop();

}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template<class T>
void Queue<T>::add(const T &theItem) {
    enqueue(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template<class T>
T Queue<T>::remove() {
    return dequeue();
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike dequeue(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template<class T>
T Queue<T>::peek() {
    if (stack_2.isEmpty()) {
        while (!stack_1.isEmpty())
            stack_2.push(stack_1.pop());
    }
    return stack_2.peek();
}

/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template<class T>
bool Queue<T>::isEmpty() const {
    return stack_2.isEmpty() && stack_1.isEmpty();
}
