CC = gcc

ifeq ($(DEBUG), 1)
    CFLAGS = -Wall -Wextra -g -O0
else
    CFLAGS = -Wall -Wextra -O2
endif

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

TARGET = $(BIN_DIR)/main
all: $(TARGET)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS)) 
DEPS = $(OBJS:.o=.d)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MD

$(TARGET) : $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

-include $(DEPS)