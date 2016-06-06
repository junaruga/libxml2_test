CC = gcc

# Production
# CFLAGS = -Werror -O2
# Development
#CFLAGS = -Werror -g -O0
CFLAGS = -g -O0

LIBXML2_INC_DIR = /usr/include/libxml2
RUBY_DIR = /usr/local/ruby-2.3.1
RUBY_LIB_DIR = $(RUBY_DIR)/lib
RUBY_INC_DIR = $(RUBY_DIR)/include
NOKOGIRI_DIR = $(HOME)/git/nokogiri
NOKOGIRI_INC_DIR = $(NOKOGIRI_DIR)/ext/nokogiri
NOKOGIRI_LIB_DIR = $(NOKOGIRI_DIR)/lib/nokogiri
INCFLAGS = -I. -I$(LIBXML2_INC_DIR) -I$(RUBY_INC_DIR) -I$(NOKOGIRI_INC_DIR)
LIBFLAGS = -L$(RUBY_LIB_DIR) -L$(NOKOGIRI_LIB_DIR)

RM = rm -f
TOP = ..
BIN_DIR = $(TOP)/bin
TARGET_READ_MEMORY = $(BIN_DIR)/read_memory

.SUFFIXES: .c .o

.PHONY: all
all: $(TARGET_READ_MEMORY)

$(TARGET_READ_MEMORY): read_memory_main.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) -lxml2 -lruby -lnokogiri $^ -o $@

.c.o:
	$(CC) $(CFLAGS) $(INCFLAGS) -c $<

read_memory_main.o: read_memory_main.h

.PHONY: clean
clean:
	$(RM) *.o $(TARGET_READ_MEMORY)

.PHONY: format
format:
	find . -name "*.c" -o -name "*.h" | xargs indent -kr -nut -il0
