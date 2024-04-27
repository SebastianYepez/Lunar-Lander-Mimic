/*
Written by Sebastian Yepez, 2024
*/

#include "priorityQ.h"
#include <cstdlib>

// destructor that deallocates heap array
template <class t1, class t2>
priorityQ<t1, t2>::~priorityQ()
{
    delete[] heapArray; // do not have to deallocate every index (think of priorityType as "int")
}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority) //insert func from class
{
    if (size == capacity - 1) { // resize
        capacity *= 2;
        priorityType * newHeapArray = new priorityType[capacity];

        // deep copy from original heap array
        for (int i = 0; i <= size; i++) {
            newHeapArray[i] = heapArray[i];
        }

        delete[] heapArray; // free up memory old array
        heapArray = newHeapArray; // heapArray points to newHeapArray (shallow copy)
    }

    heapArray[++size] = priorityType(key, priority); // insert new lander into heap array
    // ++ size means we start at index 1

    //update keyToIndex (itemToPQ) Map
    itemToPQ[key] = size;

    bubbleUp(size);
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front() // remove func from class
{
    if (size == 0) return;
    heapArray[1] = heapArray[size--]; // root gets the last element
    // decrememts size

    //update keyToIndex (itemToPQ) Map
    itemToPQ[heapArray[1].key] = 1;

    bubbleDown(1); //bubbleDown this element
}

// reassigns an element (by searching it by key, using the itemToPQ map), 
// then reassigns that element’s priority with the priority parameter, then it needs to 
// bubble up if the new priority value is smaller, or bubble down
// if the new priority value is larger
template <class t1, class t2>
void priorityQ<t1, t2>::update_element(const t1& key, const t2& priority)
{
    if(heapArray[itemToPQ[key]].priority < priority) {
        heapArray[itemToPQ[key]].priority = priority;
        bubbleDown(itemToPQ[key]);
        return;
    }
    heapArray[itemToPQ[key]].priority = priority;
    bubbleUp(itemToPQ[key]);
}

// returns the priority value of the root item
template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
    return heapArray[1].priority; // recall that our heapArray starts at index 1 for easier calcs
}

// returns the key value of the root item
template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    return heapArray[1].key;
}

// returns the priority value of the element
template <class t1, class t2>
t2 priorityQ<t1, t2>::get_element(t1 key)
{
    //itemToPQ[key] returns the index of the key in heapArray
    return heapArray[itemToPQ[key]].priority;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
    if(size == 0) return true; // because we store items and delete items from this array, 
    return false;               // when we pop all the items -> size == 0
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    while(index > 1 && heapArray[index].priority < heapArray[index/2].priority){ // if child < parent, swap
        // index == 1 -> root
        std::swap(heapArray[index], heapArray[index/2]);
        //update map
        itemToPQ[heapArray[index].key] = index; //NOTE: THEY ARE ALREADY SWAPPED IN HEAP ARRAY
        itemToPQ[heapArray[index/2].key] = index/2;
        //update index (flag)
        index /= 2;
    }
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
   //2 * index > size --> index is a leaf node
    while((2*index) <= size){
        int smallerChildIndex = 0;
        int leftChildIndex = index * 2;
        int rightChildIndex = index * 2 + 1;

        // if left child is the last element
        if(leftChildIndex == size) {
            if(heapArray[leftChildIndex].priority < heapArray[index].priority){
                    smallerChildIndex = leftChildIndex;
                    //update itemToPQ Map (swap the indexes to the according keys)
                    itemToPQ[heapArray[index].key] = smallerChildIndex;
                    itemToPQ[heapArray[smallerChildIndex].key] = index;
                    //update heapArray
                    std::swap(heapArray[index], heapArray[smallerChildIndex]);
                    //update index (flag)
                    index = smallerChildIndex;
            }
            break;
        }

        // since leftChild != last element and we know that we are within size --> right child exists
        if(heapArray[leftChildIndex].priority < heapArray[index].priority){
            smallerChildIndex = leftChildIndex;
            if((heapArray[rightChildIndex].priority < heapArray[leftChildIndex].priority)) // if right child is smaller than left
                smallerChildIndex = rightChildIndex;
        }
        else if(heapArray[rightChildIndex].priority < heapArray[index].priority) // if right child is < parent but left child isn't
            smallerChildIndex = rightChildIndex;

        // now we have the index of whichever child is smaller
        // we want this in order to maintain the min heap structure

        // however if smallerChildIndex == 0 --> neither child was smaller than parent, so we are done bubbling down
        if(smallerChildIndex == 0) break;
        //update itemToPQ Map (swap the indexes to the according keys)
        itemToPQ[heapArray[index].key] = smallerChildIndex;
        itemToPQ[heapArray[smallerChildIndex].key] = index;
        //update heapArray
        std::swap(heapArray[index], heapArray[smallerChildIndex]);
        //update index (flag)
        index = smallerChildIndex;
    }
    return;
}