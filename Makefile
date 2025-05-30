CC = gcc
CFLAGS = -Wall -Wextra -Iincs

SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

TARGET = $(BUILD_DIR)/program

all: folders $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

folders:
	mkdir $(OBJ_DIR) 2>NUL
	mkdir $(BUILD_DIR) 2>NUL

clean:
	if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

run:
	$(TARGET)

.PHONY: all clean run folders
.PRECIOUS: $(OBJ_DIR)/%.o
