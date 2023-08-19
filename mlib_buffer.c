#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "mlib_buffer.h"

void buf_allocm(buffer *target, size_t size) {
    if (target->acc == NULL) {
        target->acc = malloc(size);
    }
    else {
        target->acc = realloc(target->acc, size);
    }

    target->len = size;
}

bool storef_buf(char *filename, buffer *target) {
    int fd = open(filename, O_WRONLY | O_CREAT);
    if (fd == -1)
        return false;

    if (write(fd, target->acc, target->len) == -1)
        return false;

    close(fd);
    return true;
}

bool retrvf_buf(char *filename, buffer *target) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return false;

    if (read(fd, target->acc, target->len) == -1)
        return false;

    close(fd);
    return true;
}


// you gotta be tripping if you think this is pushable to the master branch. redo this
buffer loadf_buf(char *filename) {
    int fd;
    buffer b;
    struct stat s;

    b.acc = NULL;

    fd = open(filename, O_RDONLY); //error unchecked

    fstat(fd, &s); //error unchecked

    buf_allocm(&b, s.st_size);

    if (read(fd, b.acc, b.len) == -1)
        return (buffer) {.acc = NULL, .len = 0};

    close(fd);
    return b;
}
