# Buffer Type (`mlib_buffer.h`)

## Defines

### Types

- `buffer`

### Functions

- `buf_allocm`
- `storef_buf`
- `retrvf_buf`
- `loadf_buf`

---

### `buffer`

The actual buffer type: consists of a char pointer, pointing to the actual data and a length field.

A buffer pointing to `NULL` should be considered uninitialised/invalid.

### `buf_allocm`

> `buf_allocm(buffer *target, size_t size)`

Allocates space for the target buffer, and copies all previously stored data over, when necessary.

### `storef_buf`

> `bool storef_buf(char *filename, buffer *target)`

Stores the binary contents of the target buffer into the file supplied via `filename`. Returns a boolean value indicating success (`true` = success)

### `retrvf_buf`

> `bool retrvf_buf(char *filename, buffer *target)`

Retreives and stores contents of file `filename` in `target`. The target buffer is expected to provide the length of data to be read. The required space is not allocated by the function itself, so it must first be allocated accordingly. Returns a boolean value indicating success (`true` = success)

### `loadf_buf`

> `buffer loadf_buf(char *filename)`

Reads the entire content of file `filename` into a new buffer and returns it. Returns an uninitialised buffer if any errors occur.
