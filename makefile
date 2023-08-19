CC:=gcc
CFLAGS:=-fanalyzer -Wall -Wextra -Wanalyzer-too-complex
BIN:=./bin
SRC:=.

STATIC_LIB:=$(BIN)/libmds.a
OBJS:=$(BIN)/mlib_varr.o $(BIN)/mlib_buffer.o
HEADERS:=$(BIN)/mlib_varr.h $(BIN)/mlib_buffer.h
RM:=del

default: static_lib

static_lib: copy_headers $(STATIC_LIB)

copy_headers: $(HEADERS)

$(BIN)/%.h: $(SRC)/%.h
ifeq ($(OS),Windows_NT)
	copy $(subst /,\,$<) $(subst /,\,$@)
else
	copy $< $@
endif


$(BIN)/%.o: $(SRC)/%.c
	$(CC) -fPIC $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJS)
	ar rcs $(STATIC_LIB) $(OBJS)

clean: clean_objs clean_headers clean_lib

clean_objs:
	$(RM) $(subst /,\,$(OBJS))

clean_headers:
	$(RM) $(subst /,\,$(HEADERS))

clean_lib:
	$(RM) $(subst /,\,$(STATIC_LIB))

.PHONY: default static_lib copy_headers clean clean_objs clean_headers clean_lib
