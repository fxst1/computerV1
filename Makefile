CC=clang++
FILEEXT = cc
INC = -I ./inc/ -I .
FLAGS=-Wall -Wextra -g --std=c++1z
OBJDIR := ./obj/
SRC := $(filter %.$(FILEEXT), $(shell find src -type f))
OBJ = $(addprefix $(OBJDIR),$(SRC:.$(FILEEXT)=.o))
TARGET = computor
MACRO =

all: $(TARGET)

$(TARGET): $(OBJ)
		$(CC) $(FLAGS) $(INC) $(MACRO) -o $(TARGET) $(OBJ) $(LIB)

$(OBJDIR)%.o: %.$(FILEEXT)
		@mkdir -p $(@D)
		$(CC) $(FLAGS) $(INC) $(MACRO) -c $< -o $@

clean:
		@rm -vrf $(OBJDIR)

fclean:
		@rm -vf $(TARGET)
		@rm -vrf $(OBJDIR)

re: fclean all
