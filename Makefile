# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/10 14:28:55 by trobicho          #+#    #+#              #
#    Updated: 2019/08/16 01:56:28 by trobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	g++
CXXFLAGS	=	-std=c++14 -g #-Wall -Wextra
NAME		=	libgen.a

SRCS_PATH	=	./
HDRS_PATH	=	./
OBJS_PATH	=	./obj

INCS_FLAGS	=	-I../my_lib_cpp
LIBS_FLAGS	=	-L../my_lib_cpp -ltrl

SRCS_NAME	=	Genetic.cpp \
				People_net.cpp \
				Learning_environment_net.cpp \

HDRS_NAME	=	libgen.h \
				Genetic.h \
				People_net.h \
				Learning_environment_net.h \


OBJS_NAME	=	$(SRCS_NAME:.cpp=.o)

SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
HDRS = $(addprefix $(HDRS_PATH)/, $(HDRS_NAME))
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME))

#********************************************#
#                                            #
#                  TEST                      #
#                                            #
#********************************************#

TEST_NAME	=	test
TEST_SRCS	=	main_test_simple.cpp \
				Genetic_net_basic_mlp.cpp \
				Genetic_neat.cpp \
				People_basic_mlp.cpp \
				People_neat.cpp \
				./net_environment/Snake_copy_test.cpp
TEST_HDRS	=	Genetic_net_basic_mlp.h \
				Genetic_neat.h \
				People_basic_mlp.h \
				People_neat.h \
				./net_environment/Snake_copy_test.h

TEST_INCS_FLAGS	= $(INCS_FLAGS) -I./ -I../neuralNet -I./net_environment
TEST_LIBS_FLAGS	= $(LIBS_FLAGS) -L../neuralNet -lneuralNet

all: $(NAME)

test: $(NAME) $(TEST_SRCS) Makefile
	$(CC) $(CXXFLAGS) $(TEST_INCS_FLAGS) $(TEST_SRCS) $(NAME) -o $(TEST_NAME) $(TEST_LIBS_FLAGS)

#********************************************#
#                                            #
#                TEST END                    #
#                                            #
#********************************************#

$(NAME): logo $(OBJS) Makefile
	ar src $(NAME) $(OBJS)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.cpp $(HDRS) Makefile
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[38;2;0;255;0m[cc]\033[0m: $< -> $@"
	@printf "\e[1A"
	@$(CC) $(CXXFLAGS) -I $(HDRS_PATH) -c $< -o $@
	@printf "\e[0K"

clean:
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

logo:
	@echo ""
	@echo "\033[38;2;255;255;255mATCGCTGACT    GAATTGACAC  GAGG     ATC"
	@echo "\033[38;2;255;210;210mGTG           GTC         CGGAG    CTA"
	@echo "\033[38;2;255;168;168mATC           ATC         GGC GA   CAT"
	@echo "\033[38;2;255;126;126mCTC  TCCGTGA  CTATCGTA    TAG  CT  AAG"
	@echo   "\033[38;2;255;84;84mATG    ATT    ATA         AGT   TA GTG"
	@echo   "\033[38;2;255;42;42mGGT    TAT    TTA         GTA    AGTCT"
	@echo     "\033[38;2;255;0;0mAATGTGAATT    GTGGAGAACT  CTC     GCTC"
	@echo "\033[0m"

.PHONY: all clean fclean re logo test
