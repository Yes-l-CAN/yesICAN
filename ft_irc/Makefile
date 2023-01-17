NAME 			:= CanIRC.out
SRCS 			:= main.cpp \
					CanChannel.cpp \
					CanClient.cpp \
					Operation.cpp \
					CanServer.cpp \
					Utility.cpp

OBJ_DIR 		:= objs/
OBJS 			:= $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

CXX 			:= c++
CXXFLAGS		:= -Iinclude -g3 -fsanitize=address #-Wall -Wextra -Werror -std=c++98 
RM				:= rm -f

$(NAME)			:	$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(OBJ_DIR)		:
	mkdir $@

$(OBJ_DIR)%.o	:	%.cpp	|	$(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@  -MMD -MF $(@:.o=.d) -MT $@ -MP

# make commands
.PHONY			:	all
all				:	$(NAME)

.PHONY			:	clean
clean			:
	$(RM) -r $(OBJ_DIR)

.PHONY			:	fclean
fclean			:	clean
	$(RM) $(NAME)

.PHONY			:	re
re				:
	$(MAKE) fclean
	$(MAKE) all

-include $(OBJS:.o=.d)
