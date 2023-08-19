#pragma once

#ifndef MLIB_BUFFER_H
#define MLIB_BUFFER_H

#include <stddef.h> // size_t
#include <stdbool.h>

typedef struct {
    char *acc;
    size_t len;
} buffer;

void buf_allocm(buffer *target, size_t size);
bool storef_buf(char *filename, buffer *target);
bool retrvf_buf(char *filename, buffer *target);
buffer loadf_buf(char *filename);

#endif
