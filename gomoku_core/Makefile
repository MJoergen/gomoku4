NAME	=	gomoku
SRC	=	main.cpp gomoku.cpp IA_alphabeta.cpp Move.cpp IA_negamax.cpp
OBJ	=	$(SRC:.cpp=.o)
CC 	=	g++
CFLAGS	=	-O3 -W -Wall -Werror -ansi -march=i386 -mtune=i386 -I ./
RM	=	rm -Rf
DATE	=	`date '+%m-%d-%y_%Hh%M'`

all:		$(SRC) $(NAME)
$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $@
.cpp.o	:
		$(CC) -c $(CFLAGS) $< -o $@
clean :
		$(RM) *.core *~ *.o \#* .\#* */*~ */\#*
fclean :	clean
		$(RM) $(NAME)
re	:	fclean all
tgz	:
		tar czvf ../$(NAME)_$(DATE).tgz *
