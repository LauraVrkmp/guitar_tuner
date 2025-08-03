# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lveerkam <lveerkam@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/08/02 19:18:29 by lveerkam      #+#    #+#                  #
#    Updated: 2025/08/02 21:06:40 by lveerkam      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC_LINUX = cc
CC_WIN = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS_LINUX = -g -fsanitize=address

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS_LINUX = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/linux/%.o, $(SRCS))
OBJS_WIN = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/windows/%.o, $(SRCS))

INCLUDE_LINUX = -Iinclude
INCLUDE_WIN = -Ilib/raylib-windows/raylib-5.5_win64_mingw-w64/include
LDFLAGS_LINUX = -L$(LIB_DIR)/raylib_linux -lraylib -lGL -lrt -lX11 -ldl -lpthread -lm
LDFLAGS_WIN = -L$(LIB_DIR)/raylib-windows/raylib-5.5_win64_mingw-w64/lib -lraylib -lopengl32 -lgdi32 -lwinmm
NAME = tuner

all: linux windows

linux: $(OBJS_LINUX) | $(BIN_DIR)
	$(CC_LINUX) $(CFLAGS) $(CFLAGS_LINUX) $(OBJS_LINUX) -o $(BIN_DIR)/$(NAME) $(LDFLAGS_LINUX)

windows: $(OBJS_WIN) | $(BIN_DIR)
	$(CC_WIN) $(CFLAGS) $(INCLUDE_WIN) $(OBJS_WIN) -o $(BIN_DIR)/$(NAME).exe $(LDFLAGS_WIN)

$(OBJ_DIR)/linux/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/linux
	$(CC_LINUX) $(CFLAGS) $(CFLAGS_LINUX) $(INCLUDE_LINUX) -c $< -o $@

$(OBJ_DIR)/windows/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/windows
	$(CC_WIN) $(CFLAGS) $(INCLUDE_WIN) -c $< -o $@

$(OBJ_DIR)/linux:
	mkdir -p $@

$(OBJ_DIR)/windows:
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all linux windows clean fclean re