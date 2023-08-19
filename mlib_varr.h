#pragma once

#ifndef MLIB_VARR_H
#define MLIB_VARR_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    uintptr_t *access; // uintptr_t, just cast it to whatever type you need
    size_t alloc_size; // alloc_size in n of elements, not n of bytes
    size_t marker_index; // the first free index, size_t is suitable for indexing
} varr;


// creates a varr of size init_size or at least 1 and returns a pointer to it
varr *new_varr(size_t init_size);

// copies the varr and returns a pointer to the copy
varr *copy_varr(varr *arr);

// resize varr arr to hold up to new_size amount of elements
void varr_resize(varr *arr, size_t new_size);

// shrink the array to fit the current amount of elements exactly
void varr_shrink_to_fit(varr *arr);

// push an element to arr
void varr_push(varr *arr, uintptr_t new_elem);

/* from arr, get the element at index and put its value in elem
    returns true on success, false if requested index is out of bounds
*/
bool varr_get(varr *arr, size_t index, uintptr_t *elem);

/* pop the top-most element from arr and copy the content to elem
    returns 0 on success, -1 if arr is already empty
*/
bool varr_pop(varr *arr, uintptr_t *elem);

/* from arr, directly get element at index
    returns 0 if element couldnt be found (ie. index is "out of bounds")
*/
uintptr_t varr_dget(varr *arr, size_t index);

/* from arr, directly pop top-most element
    returns 0 if arr is already empty
*/
uintptr_t varr_dpop(varr *arr);

// merges arr2 into arr1 in-place by appending it to arr1
void varr_merge_inpl(varr *arr1, varr *arr2);

// concatenates the two varrs passed and returns a pointer to the new, concatenated varr
varr *varr_concat(varr *arr1, varr *arr2);

// check if the varr is sane
bool varr_check_sane(varr *arr);

// safely destroy arr
void varr_destroy(varr *arr);

#endif
