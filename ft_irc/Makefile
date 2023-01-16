NAME 		:= CanIRC
SRCS 		:= 	main.cpp \
				CanChannel.cpp \
				CanClient.cpp \
				Operation.cpp \
				CanServer.cpp \
				Utility.cpp
				
INCLUDES_DIR := ./include

INCLUDES	:= 	$(INCLUDES_DIR)/CanChannel.hpp \
				$(INCLUDES_DIR)/CanClient.hpp \
				$(INCLUDES_DIR)/Operation.hpp \
				$(INCLUDES_DIR)/CanServer.hpp \
				$(INCLUDES_DIR)/Utility.hpp

CXX 		:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98
RM			:= rm -f

OBJS 		:= $(SRCS:.cpp=.o)

$(NAME)		:	$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o			: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# make commands
.PHONY		:	all
all			:	$(NAME)

.PHONY		:	clean
clean		:
	$(RM) $(OBJS)

.PHONY		:	fclean
fclean		:	clean
	$(RM) $(NAME)

.PHONY		:	re
re			:
	$(MAKE) fclean
	$(MAKE) all