CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = ./src
BUILD_DIR = ./build
TARGET = $(BUILD_DIR)/chess_program

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/chess/*.c) $(wildcard $(SRC_DIR)/misc/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

create:
	mkdir build/
test:
	echo $(shell pwd)

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -r $(BUILD_DIR)

# could not for the love of god get this to work on windows in another way
clean-win:
	clean.bat
