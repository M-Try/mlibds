# Basic resizable/variable size array type (`mlib_varr.h`)

## Defines

### Types

- `varr`

### Functions

- `new_varr`
- `copy_varr`
- `varr_resize`
- `varr_shrink_to_fit`
- `varr_push`
- `varr_get`
- `varr_pop`
- `varr_dget`
- `varr_dpop`
- `varr_merge_inpl`
- `varr_concat`
- `varr_check_sane`
- `varr_destroy`

---

### `varr`

Resizable array type. You should always use new_varr to create a new variable size array. This type resembles a stack and can be used as such by using the `varr_push` and `varr_pop` functions. Internally, the variable array will keep track of the index of the topmost element (thus making this type stack-like) and every element up to that is considered in-bounds or valid, while every element beyond that is considered out-of-bounds or invalid.

To avoid memory leaks, the `varr_destroy` function should always be used to delete a resizable array.

### `new_varr`

> `varr new_varr(size_t init_size)`

Creates a new variable size array and allocates enough memory for at least 1 or `init_size` elements.

### `copy_varr`

> `varr *copy_varr(varr *arr)`

Returns a pointer to a new varr, which contains a copy of the contents of `arr`.

### `varr_resize`

> `void varr_resize(varr *arr, size_t new_size)`

Resizes the variable size array given by `*arr` to new_size. Be aware: If the new size is smaller than the current size all leftover elements will be lost.

### `varr_shrink_to_fit`

> `void varr_shrink_to_fit(varr *arr)`

Reduce the allocated size of the array to fit exactly as much elements as it currently holds (unless that number is 0). This is useful when trying to keep a low memory footprint.

### `varr_push`

> `void varr_push(varr *arr, uintptr_t new_elem)`

Appends `new_elem` to the variable array. If the underlying memory allocated for the varray isnt large enough to hold an additional element, it will automatically double the size of the allocated memory.

### `varr_get`

> `bool varr_get(varr *arr, size_t index, uintptr_t *elem)`

Retreives the element at `index` from `arr` and writes it to `*elem`. If `index` is out-of-bounds, returns `false` to indicate failure. Otherwise returns `true` for success.

### `varr_pop`

> `signed int varr_pop(varr *arr, uintptr_t *elem)`

Pops the top-most element from the array and writes it to `*elem`. If the array is empty (ie. no element can be popped), it will return -1 to indicate failure. Otherwise returns 0 for success.

### `varr_dget`

> `uintptr_t varr_dget(varr *arr, size_t index)`

"Directly get" the element at `index`. If `index` is out-of-bounds, it will return `NULL` instead.

### `varr_dpop`

> `uintptr_t varr_dpop(varr *arr)`

"Directly pop" the top-most element. If the array is empty, it will return `NULL` instead.

### `varr_merge_inpl`

> `void varr_merge_inpl(varr *arr1, varr *arr2)`

Appends the contents of `arr2` to `arr1`.

### `varr_concat`

> `varr *varr_concat(varr *arr1, varr *arr2)`

Concatenates the two arrays `arr1` and `arr2` and returns a pointer to the resulting array. Will return a null pointer upon failure (ie. `arr1` or `arr2` == NULL).

### `varr_check_sane`

> `bool varr_check_sane(varr *arr)`

Performs simple sanity checks on the array. If any of them fail, `false` is returned. Otherwise returns `true`.

### `varr_destroy`

> `void varr_destroy(varr *arr)`

Safely dispose of a variable size array. It will deallocate the memory associated with the resizable array. Not doing so will result in memory leaks if the reference to the variable array falls out of scope.
