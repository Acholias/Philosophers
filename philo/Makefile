# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/30 15:33:08 by lumugot           #+#    #+#              #
#    Updated: 2025/06/10 23:35:53 by lumugot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ_DIR = objs

CC = cc

MAKEFLAGS += -s --no-print-directory

CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC = main.c \
		parsing/utils.c \
		parsing/convert_utils.c \
		parsing/check_arg.c \
		parsing/setup_data.c \
		src/actions.c \
		src/routine.c \
		src/check_simulation.c \
		src/launch_monitoring.c \
		src/destroy_thread.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)
	@sleep 1
	@clear
	@sleep 1
	@echo "$$BANNER"
	@echo "$$CREDIT"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)


fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


define BANNER

 ______  _     _ _                        _                     
(_____ \| |   (_) |                      | |                    
 _____) ) |__  _| | ___   ___  ___  ____ | |__  _____  ____ ___ 
|  ____/|  _ \| | |/ _ \ /___)/ _ \|  _ \|  _ \| ___ |/ ___)___)
| |     | | | | | | |_| |___ | |_| | |_| | | | | ____| |  |___ |
|_|     |_| |_|_|\_)___/(___/ \___/|  __/|_| |_|_____)_|  (___/ 
                                   |_|                          

endef
export BANNER


define CREDIT

╔════════════════════════════════════════════╗
║             💀  DEVELOPED BY  💀           ║
╠════════════════════════════════════════════╣
║      🤡   lumugot, aka Acholias   🤡       ║
╚════════════════════════════════════════════╝

endef
export CREDIT