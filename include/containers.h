#pragma once
#include <stdint.h>
#include <assert.h>
#include <memory>

template <typename T>
struct Array {
    uint32_t capacity = 0;
    uint32_t count = 0;
    T *data = NULL;

    T &operator[](uint32_t index);

    T* begin();
    T* end();

    ~Array();
};

template <typename T>
void array_add(Array<T> *array, T item);

template <typename T>
void array_remove(Array<T> *array, T item);

template <typename T>
void array_remove(Array<T> *array, int index);



/*******************
    IMPLEMENTATION
********************/

template <typename T>
void array_add(Array<T> *array, T item) {
    // check if there is memory available for 1 more item
    // if not, reallocate the memory block
    if (array->count + 1 > array->capacity) {
        uint32_t new_capacity; 
        T *new_data; 

        if (array->capacity == 0) {
            new_capacity = 64; // start capacity at 64
            new_data = (T*)malloc(sizeof(T) * new_capacity);
            assert(new_data);
            memcpy(new_data, array->data, sizeof(T) * array->count);
        } else {
            new_capacity = array->capacity * 2;
            new_data = (T*)realloc(array->data, sizeof(T) * new_capacity);
            assert(new_data);
        }

        array->data = new_data;
        new_data = NULL;
        array->capacity = new_capacity;
    }

    // add item to array
    array->data[array->count] = item;
    array->count++;
}

//template <typename T>
//void array_remove(Array<T> *array, T item) {
    //// find element in array
    //for (int i=0; i<array->count; i++) {
        //if (array->data[] )
    //}
//}

//template <typename T>
//void array_remove(Array<T> *array, int index) {
    //array->data[index] = array->data[array->count - 1];
    //array->count--;
//}


template <typename T> 
inline T &Array<T>::operator[](uint32_t index) {
    return data[index];
}

template <typename T>
Array<T>::~Array<T>() {
    if (capacity > 0) {
        free(data);
    }
}


template <typename T>
inline T* Array<T>::begin() { return data; }

template <typename T>
inline T* Array<T>::end() { return data + count; }

