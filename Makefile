CC = c++ 
NAME = IRC
SRC =	src/main.cpp	\
		src/Channel.cpp	\
		src/Client.cpp \
		src/Server.cpp	\
		src/parsing.cpp	\
		src/commands/join.cpp \
		src/commands/part.cpp \
		src/commands/pass.cpp \
		src/commands/privmsg.cpp \
		src/commands/user.cpp  \
		src/commands/invite.cpp	\
		src/commands/kick.cpp	\
		src/commands/topic.cpp	\
		src/commands/mode.cpp \
		src/commands/nick.cpp	\
		src/commands/help.cpp
HEADER =	inc/IRC.hpp \
			inc/Client.hpp \
			inc/Server.hpp	\
			inc/Channel.hpp

OBJ=$(SRC:.cpp=.o)
CFLAGS = -Werror -Wall -Wextra -g3 -std=c++98
INC = -I inc/

GREEN=\033[0;92m
YELLOW=\033[0;33m
RED=\033[0;31m
END=\033[0m

all : $(NAME)

%.o : %.cpp $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

re : fclean all

clean :
	rm -rf $(OBJ)

run : all _capy
	valgrind ./$(NAME) 2000 oui

fclean : clean
	@rm -rf $(NAME)

.PHONY : clean re fclean all

_capy :
	clear
	@echo	"$(GREEN)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo	" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣶⠛⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⡀⠀⠀⠀⠀⠀$(YELLOW)⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⡀⠀⠀⠀⠀$(GREEN)⠀⠀⠀"
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣄⣼⡦⠴⠒⠒⠶⣤⣀⠀⣾⢧⡋⡇⠀⠀⠀⠀⠀$(YELLOW) ⠀⠀⡤⣚⡍⠀⠀⠀⠀⢩⣓⢤⠀⠀$(GREEN)⠀⠀⠀"
	@echo	"⠀⠀⠀⠀⠀⠀⠀⣀⡤⠶⠚⠉⠁⠀⠀⠀⠀⠀⠀⠀⠈⣿⣷⣋⡿⠃⠀⠀⠀⠀⠀$(YELLOW) ⢀⣞⣼⣿⣿⣆⠀⠀⣰⣿⣿⣧⣳⡀$(GREEN)⠀⠀⠀"
	@echo	"⠀⠀⠀⢀⡤⠖⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀$(YELLOW)⢀⣶⣶⣦ $(GREEN)⠈⠻⠻⣆⠀⠀⠀ ⠀$(YELLOW)⠀⢸⢸⣿⣿⣿⣟⣴⣦⣻⣿⣿⣿⡇⡇$(GREEN)⠀⠀⠀"
	@echo	"⢀⡠⠞⠃⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀$(YELLOW)⠘⣿$(RED)⣿$(YELLOW)⣿⡇$(GREEN)⠀⡀⠙⣇⠀ ⠀⠀⠀$(YELLOW)⠀⢸⠀⠀⠀⠀⠈⣻⣟⠁⠀⠀⠀⠀⡇$(GREEN)⠀⠀⠀"
	@echo	"⡞⠁⠀⠀⠀⠀⢀⡴⠃⠀⠀⠀⠀⠀⠀⠀⠀$(YELLOW)⠀⠛⠛⠟⠀$(GREEN)⠀⠙⠀⠸⣆⠀⠀⠀⠀$(YELLOW)⠀⠈⢧⠀⠀⢀⣾⣿⣿⣷⡀⠀⠀⡼⠁$(GREEN)⠀⠀⠀"
	@echo	"⡿⣤⡀⠀⢀⡴⠋⠀⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠘⣆⠀⠀⠀$(YELLOW)⠀⠀⠀⠓⢤⣺⠿⠿⠿⠿⣗⡤⠞⠁⠀$(GREEN)⠀⠀⠀"
	@echo	"⡇⠀⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠳⣄⠀⠀⡀⠀⠈⢳⡀⠀$(YELLOW)⠀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠁⠀⠀⠀⠀$(GREEN)⠀⠀⠀"
	@echo	"⢹⡀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠙⢦⡀⠀⠙⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo	"⠘⣇⠀⠘⣆⠀⠀⠀⠀⠀⠀⠀⢀⣴⠞⠀⠹⠆⠀⠀⠈⢳⠀⠀⠀⠀⠀⠁⠀⠀⠀⠉⠳⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo	"⠀⠘⢦⣤⣹⣄⣀⣀⣀⣠⣤⠴⠊⠀⠀⠀⠀⠀⠀⠀⠀⠈⠃⠀⠀⠀⠀⠲⣤⡀⠀⠀⠀⠀⠈⠙⠲⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo	"⠀⠀⠀⠀⠀⠀⠙⠲⢤⡀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⢰⡄⠀⠀⠀⠀⠁⠀⠀⠀⠀⠈⠑⠢⣄⡙⠷⣄⠀⠀⠀⠀⠀⠀ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠀⡀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠈⠀⠀⠈⠳⣄⠀⠀⠀⠀ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⣻⠀⠀⢳⠀⠀⠀⠘⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠢⡀⠀⠑⢄⠙⢆⠀⠀⠀ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠈⠂⠀⠀⠀⠀⢠⣿⠀⠀⠀⠀⠀⠀⢀⣤⠴⠚⠃⠀⠀⠘⢢⡀⠀⠀⠉⠀⠀⠈⠧⠘⢧⠀⠀ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⡇⠀⠀⠀⠀⠀⠀⠀⠘⠋⠀⠀⠀⠀⠀⣴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠙⢦⡀⠀⢦⠀⠀⠀⠀⠈⣇⠀ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢹⠀⢰⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠈⢳⡀⠀⠀⠀⠸⡆ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠘⠷⠀⠀⠀⠀⠀⢠⠀⠀⠀⠠⡏⠀⠀⢠⠀⠀⠀⠀⠀⢠⡀⠀⠀⠀⡀⠀⠀⠷⠀⢸⡄⠀⢳ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠀⠀⠀⡄⠀⠀⢸⡇⠀⠀⢸⣧⠀⠀⠈⢣⠀⠀⠀⠀⢀⣳⠀⠀⠀⢹⡄⠀⠀⠀⠈⠁⠀⢸ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⡄⠀⠀⠀⣷⠀⠀⠘⠃⠀⠀⢀⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠸⢳⡀⢀⡀⠀⢠⠀⢸ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣄⠀⠀⢻⡇⠀⠀⠀⠀⠀⣸⠉⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⠐⣧⠀⠸⠀⡼ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣦⡀⣸⣷⠀⠀⠀⠀⠀⡇⠀⠈⠳⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⢸⠇ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣖⡿⣿⡟⣻⣿⣷⡄⠀⠀⢾⣁⡀⠀⠀⣨⡷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠏⠀ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⠷⠿⣿⣥⠟⠀⣹⣾⠦⡿⡾⠇⠉⢻⣟⣀⣀⡬⠟⠲⢤⣀⣀⣀⣀⠀⠀⠀⠀⢀⣀⡴⠋⠀⠀ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠋⠁⢰⣿⡽⢛⡧⢠⡇⠀⠀⠀⠉⠉⠙⠓⠒⠒⠚⠉⠁⠀⠉⠑⠒⠒⠉⠉⠁⠀⠀⠀⠀ "
	@echo	"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠒⣿⣤⠞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ "
	@echo ""
	@echo	"----------$(RED)I$(GREEN)nsane$(RED)R$(GREEN)adioactive$(RED)C$(GREEN)apybara SERVER READY----------$(END)"
	@echo ""



