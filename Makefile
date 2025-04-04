SRC_DIR		:= src
OBJ_DIR		:= obj
INC_DIR		:= inc
SRC_FILES	:= $(wildcard $(SRC_DIR)/*)
INC_FILES	:= $(notdir $(wildcard $(INC_DIR/*)))
OBJ_FILES	:= $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(SRC_FILES:.c=.o))

.PHONY : all re clean fclean

all : even_odd

even_odd : $(OBJ_FILES)
	gcc $^ -o even_odd

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc -Wall -Wextra -Werror -g -O0 -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR) :
	mkdir -p $@

re : fclean all

fclean : clean
	rm -f even_odd

clean :
	rm -rf $(OBJ_DIR)
