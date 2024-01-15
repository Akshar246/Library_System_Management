# Compiler and compiler options
CXX	=	g++
CXXFLAGS	=	-std=c++11 -Wall

# Executable name
EXECUTABLE	=	coursework1

# Source files and object filesx
SRCS	=	coursework1.cpp member.cpp staff.cpp book.cpp library.cpp test_member.cpp test_staff.cpp test_book.cpp test_library.cpp
OBJS	=	$(SRCS:.cpp=.o)

# Targets and rules
all:	$(EXECUTABLE)

$(EXECUTABLE):	$(OBJS)
	$(CXX)	$(CXXFLAGS)	-o	$@	$^

%.o:	%.cpp
	$(CXX)	$(CXXFLAGS)	-c	-o	$@	$<
# Clean up intermediate and executable files
clean:
	rm	-f	$(OBJS)	$(EXECUTABLE)