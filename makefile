CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = ./src
BUILD_DIR = ./build
TARGET = $(BUILD_DIR)/chess_program

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/chess/*.c) $(wildcard $(SRC_DIR)/misc/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

# could not for the love of god get this to work on windows in another way
clean:
	clean.bat