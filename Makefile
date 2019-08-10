# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/10 14:28:55 by trobicho          #+#    #+#              #
#    Updated: 2019/08/10 20:15:36 by trobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	g++
CXXFLAGS	=	-std=c++14 -Wall -Wextra
NAME		=	libgen.a

SRCS_PATH	=	./
HDRS_PATH	=	./
OBJS_PATH	=	./obj

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
				People_basic_mlp.cpp \
				./net_environment/Test_simple.cpp
TEST_HDRS	=	Genetic_net_basic_mlp.h \
				People_basic_mlp.h \
				./net_environment/Test_simple.h

all: $(NAME)

test: $(NAME) $(TEST_SRCS) Makefile
	$(CC) $(CXXFLAGS) -I./ -I./net_environment/ $(TEST_SRCS) $(NAME) -o $(TEST_NAME)

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
