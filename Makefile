APP			=	webserv

SRC_DIR		= ./src
BIN_DIR		= ./bin
INC_DIR		= ./inc
OBJ_DIR		= ./obj 

CPP_FLAGS	= -std=c++98 -Wall -Wextra -Werror

SRC			=	main.cpp

SRCS		= $(patsubst %.cpp, ${SRC_DIR}/.cpp, ${SRC})
OBJS		= $(patsubst %.cpp, ${OBJ_DIR}/%.o, ${SRC})
DEPS		= $(patsubst %.cpp, ${OBJ_DIR}/%.d, ${SRC})

all:	${BIN_DIR}/${APP}

${PROJ_DIRS}:
	@mkdir -p ${OBJ_DIR}
	@mkdir -p ${BIN_DIR}

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -rf ${BIN_DIR}

re: fclean all

-include ${DEPS}

.PHONY: all clean fclean re