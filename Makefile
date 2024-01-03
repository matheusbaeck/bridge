# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baeck <baeck@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 10:37:38 by mamagalh@st       #+#    #+#              #
#    Updated: 2024/01/03 18:19:02 by baeck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src
LIBFT_DIR = src/libft
OBJ_DIR = .obj

TARGET_NAME = bridge.a
HEADER_FILE = $(TARGET_NAME:.=.h)

CC = cc
LIB_CC = ar rcs
MAKE = make
MKDIR = mkdir -p

FLAGS = -Wall -Wextra -Werror -c -o

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT = $(LIBFT_DIR)/libft.a

all: $(TARGET_NAME)

$(TARGET_NAME): $(LIBFT) $(OBJECTS)
	$(LIB_CC) $@ $(OBJECTS) $(HEADER_FILE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(FLAGS) $@ $<

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR) *.o *.dSYM *.out
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(TARGET_NAME) *.a
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
