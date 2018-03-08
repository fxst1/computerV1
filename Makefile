CC=g++
FILEEXT = cc
INC = -I ./inc/ -I .
FLAGS=-Wall -Wextra -g
OBJDIR := ./obj/
SRC := $(filter %.$(FILEEXT), $(shell find src -type f))
OBJ = $(addprefix $(OBJDIR),$(SRC:.$(FILEEXT)=.o))
NAME = computer

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(LIB)

$(OBJDIR)%.o: %.$(FILEEXT)
		@mkdir -p $(@D)
		$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
		@rm -vrf $(OBJDIR)

fclean:
		@rm -vf $(NAME)
		@rm -vrf $(OBJDIR)

re: fclean all
