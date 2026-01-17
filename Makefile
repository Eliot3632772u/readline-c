# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_login <your_login@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by your_login       #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by your_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME        = gnl_test
NAME_BONUS  = gnl_bonus

# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
BUFFER_SIZE ?= 42
BSIZE_FLAG  = -D BUFFER_SIZE=$(BUFFER_SIZE)

# Colors for output
GREEN       = \033[0;32m
BLUE        = \033[0;34m
RED         = \033[0;31m
YELLOW      = \033[0;33m
RESET       = \033[0m

# Source files
SRCS        = get_next_line.c get_next_line_utils.c
SRCS_BONUS  = get_next_line_bonus.c get_next_line_utils_bonus.c
TEST_FILE   = main.c

# Object files
OBJS        = $(SRCS:.c=.o)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)
TEST_OBJ    = $(TEST_FILE:.c=.o)

# Header files
HEADER      = get_next_line.h
HEADER_BONUS = get_next_line_bonus.h

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

# Default rule
all: $(NAME)

# Compile mandatory version
$(NAME): $(OBJS) $(TEST_OBJ)
	@echo "$(BLUE)Compiling mandatory version...$(RESET)"
	@$(CC) $(CFLAGS) $(BSIZE_FLAG) $(OBJS) $(TEST_OBJ) -o $(NAME)
	@echo "$(GREEN)✓ Mandatory version compiled successfully!$(RESET)"
	@echo "$(YELLOW)  Buffer size: $(BUFFER_SIZE)$(RESET)"
	@echo "$(YELLOW)  Run with: make run$(RESET)"

# Compile bonus version
bonus: $(OBJS_BONUS) main_bonus.o
	@echo "$(BLUE)Compiling bonus version...$(RESET)"
	@$(CC) $(CFLAGS) $(BSIZE_FLAG) $(OBJS_BONUS) main_bonus.o -o $(NAME_BONUS)
	@echo "$(GREEN)✓ Bonus version compiled successfully!$(RESET)"
	@echo "$(YELLOW)  Buffer size: $(BUFFER_SIZE)$(RESET)"
	@echo "$(YELLOW)  Run with: make run_bonus$(RESET)"

# Compile object files for mandatory
%.o: %.c $(HEADER)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(BSIZE_FLAG) -c $< -o $@

# Compile object files for bonus (with bonus header)
%_bonus.o: %_bonus.c $(HEADER_BONUS)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(BSIZE_FLAG) -c $< -o $@

# Special rule for main.c with bonus header
main_bonus.o: main.c $(HEADER_BONUS)
	@echo "$(BLUE)Compiling main.c for bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(BSIZE_FLAG) -c main.c -o main_bonus.o

# Run mandatory tests
run: $(NAME)
	@echo "$(GREEN)Running mandatory tests...$(RESET)"
	@echo "$(BLUE)═══════════════════════════════════════════════════$(RESET)"
	@./$(NAME)
	@echo "$(BLUE)═══════════════════════════════════════════════════$(RESET)"

# Run bonus tests
run_bonus: bonus
	@echo "$(GREEN)Running bonus tests...$(RESET)"
	@echo "$(BLUE)═══════════════════════════════════════════════════$(RESET)"
	@./$(NAME_BONUS)
	@echo "$(BLUE)═══════════════════════════════════════════════════$(RESET)"

# Clean object files
clean:
	@echo "$(RED)Removing object files...$(RESET)"
	@rm -f $(OBJS) $(OBJS_BONUS) $(TEST_OBJ) main_bonus.o
	@rm -f test*.txt  # Remove test files created by main.c
	@echo "$(GREEN)✓ Object files removed$(RESET)"

# Clean everything
fclean: clean
	@echo "$(RED)Removing executables...$(RESET)"
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(GREEN)✓ Clean complete$(RESET)"

# Rebuild everything
re: fclean all

# Rebuild bonus
re_bonus: fclean bonus

# Help message
help:
	@echo "$(BLUE)════════════════════════════════════════════════════$(RESET)"
	@echo "$(GREEN)  GET_NEXT_LINE - Available Commands$(RESET)"
	@echo "$(BLUE)════════════════════════════════════════════════════$(RESET)"
	@echo ""
	@echo "$(YELLOW)Basic Commands:$(RESET)"
	@echo "  make              - Compile mandatory version"
	@echo "  make bonus        - Compile bonus version"
	@echo "  make run          - Compile and run mandatory tests"
	@echo "  make run_bonus    - Compile and run bonus tests"
	@echo ""
	@echo "$(YELLOW)Cleaning:$(RESET)"
	@echo "  make clean        - Remove object files"
	@echo "  make fclean       - Remove object files and executables"
	@echo "  make re           - Rebuild mandatory version"
	@echo "  make re_bonus     - Rebuild bonus version"
	@echo ""
	@echo "$(YELLOW)Buffer Size:$(RESET)"
	@echo "  make BUFFER_SIZE=1 run        - Test with small buffer"
	@echo "  make BUFFER_SIZE=9999 run     - Test with large buffer"
	@echo "  make BUFFER_SIZE=42 bonus     - Default buffer (42)"
	@echo ""
	@echo "$(YELLOW)Examples:$(RESET)"
	@echo "  make                          - Compile mandatory"
	@echo "  make run                      - Run mandatory tests"
	@echo "  make BUFFER_SIZE=1 run_bonus  - Run bonus with BUFFER_SIZE=1"
	@echo ""
	@echo "$(BLUE)════════════════════════════════════════════════════$(RESET)"

# Test with different buffer sizes
test_buffers:
	@echo "$(GREEN)Testing with different buffer sizes...$(RESET)"
	@echo ""
	@echo "$(YELLOW)Testing BUFFER_SIZE=1$(RESET)"
	@make fclean > /dev/null 2>&1
	@make BUFFER_SIZE=1 run
	@echo ""
	@echo "$(YELLOW)Testing BUFFER_SIZE=42$(RESET)"
	@make fclean > /dev/null 2>&1
	@make BUFFER_SIZE=42 run
	@echo ""
	@echo "$(YELLOW)Testing BUFFER_SIZE=9999$(RESET)"
	@make fclean > /dev/null 2>&1
	@make BUFFER_SIZE=9999 run

# Phony targets
.PHONY: all bonus clean fclean re re_bonus run run_bonus help test_buffers