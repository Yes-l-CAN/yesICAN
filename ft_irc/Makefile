NAME 		:= CanIRC
SRCS 		:= 	main.cpp \
				CanChannel.cpp \
				CanClient.cpp \
				CanCommand.cpp \
				CanServer.cpp 
				
INCLUDES	:= CanChannel.hpp \
				CanClient.hpp \
				CanCommand.hpp \
				CanServer.hpp 

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