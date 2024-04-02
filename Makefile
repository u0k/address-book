INCLUDE_DIR := ./include
SRC_DIR := ./src
BUILD_DIR := ./build

SRCS:=$(wildcard $(SRC_DIR)/*.c)
DEPS:=$(wildcard $(INCLUDE_DIR)/*.h)
_OBJ := $(shell basename -a $(SRCS:.c=.o))
OBJ := $(patsubst %, $(BUILD_DIR)/%, $(_OBJ))

CFLAGS := -Wall -g -I$(INCLUDE_DIR)

.PHONY: all
all: address_book

address_book: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)/*.o address_book 