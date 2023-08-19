#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mlib_varr.h"


varr *new_varr(size_t init_size) {
    varr *varr_ptr = (varr *) malloc(sizeof(varr));

    varr_ptr->marker_index = 0;

    // size must be at least one
    varr_ptr->alloc_size = init_size > 0 ? init_size : 1;
    varr_ptr->access = (uintptr_t *) calloc(varr_ptr->alloc_size, sizeof(uintptr_t));

    return varr_ptr;
}

varr *copy_varr(varr *arr) {
    if (arr == NULL) return NULL;

    varr *copied_varr_ptr = (varr *) malloc(sizeof(varr));
    copied_varr_ptr->marker_index = arr->marker_index;
    copied_varr_ptr->alloc_size = copied_varr_ptr->marker_index > 0 ? copied_varr_ptr->marker_index : 1;

    // allocate at least one element
    copied_varr_ptr->access = calloc(copied_varr_ptr->alloc_size, sizeof(uintptr_t));

    memcpy(copied_varr_ptr->access, arr->access, copied_varr_ptr->marker_index);

    return copied_varr_ptr;
}

void varr_resize(varr *arr, size_t new_size) {
    if (arr == NULL) return;
    if (new_size == 0) return;
    if (arr->alloc_size == new_size) return;

    // move marker to end of the list, so that its not out of bounds
    if (new_size < arr->marker_index) arr->marker_index = new_size;

    // reallocate the space
    arr->access = (uintptr_t *) realloc(arr->access, new_size * sizeof(uintptr_t)); // access is now new_acc
    arr->alloc_size = new_size;
}

void varr_shrink_to_fit(varr *arr) {
    if (arr == NULL) return;

    varr_resize(arr, arr->marker_index);
}

void varr_push(varr *arr, uintptr_t new_elem) {
    if (arr == NULL) return;

    // if arr is full
    if (arr->alloc_size == arr->marker_index)
        varr_resize(arr, arr->alloc_size * 2);

    arr->access[arr->marker_index] = new_elem; // first free index gets new element
    arr->marker_index++; // above operation means first free index is now +=1
}

bool varr_get(varr *arr, size_t index, uintptr_t *elem) {
    if (arr == NULL) return false;

    // if requested index is out of bounds
    if (arr->marker_index <= index) return false;

    *elem = arr->access[index];
    return true;
}

bool varr_pop(varr *arr, uintptr_t *elem) {
    if (arr == NULL) return false;
    if (arr->marker_index == 0) return false;

    arr->marker_index--;
    return varr_get(arr, arr->marker_index, elem);
}

uintptr_t varr_dget(varr *arr, size_t index) {
    uintptr_t ret_elem;

    if (!varr_get(arr, index, &ret_elem))
        return 0;

    return ret_elem;
}

uintptr_t varr_dpop(varr *arr) {
    uintptr_t ret_elem;

    if (!varr_pop(arr, &ret_elem))
        return 0;

    return ret_elem;
}

void varr_merge_inpl(varr *arr1, varr *arr2) {
    if (arr1 == NULL || arr2 == NULL) return;

    if ((arr1->alloc_size - arr1->marker_index) < arr2->marker_index)
        varr_resize(arr1, arr1->marker_index + arr2->marker_index);

    memcpy(arr1->access + arr1->marker_index, arr2->access, arr2->marker_index * sizeof(uintptr_t));
    arr1->marker_index += arr2->marker_index;
}

varr *varr_concat(varr *arr1, varr *arr2) {
    if (arr1 == NULL || arr2 == NULL) return NULL;

    varr *concat_arr = copy_varr(arr1);
    varr_merge_inpl(concat_arr, arr2);
    return concat_arr;
}

bool varr_check_sane(varr *arr) {
    if (arr == NULL) return false;
    if (arr->alloc_size < arr->marker_index) return false;
    if (arr->alloc_size == 0) return false;
    if (arr->access == NULL) return false;

    return true;
}

void varr_destroy(varr *arr) {
    if (arr == NULL) return;

    free(arr->access);
    free(arr);
}
