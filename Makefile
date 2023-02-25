OS := $(shell uname)
CXX := c++
DEFINES := -D HOSTNAME=\"$(shell hostname)\"
INCLUDES := -I include
CXXFLAGS = $(DEFINES) $(INCLUDES) -Wall -Wextra -Werror
OUTDIR := .build
NAME := ircserv

ifneq ($(OS), Linux)
CXXFLAGS += --std=c++98
endif

SRC := main.cpp\
Server.cpp\
Client.cpp\
utils.cpp\
parseMessage.cpp\
validation.cpp\
replies.cpp\
Dispatcher.cpp\
Channel.cpp\
commands/PASS.cpp\
commands/NICK.cpp\
commands/USER.cpp\
commands/PART.cpp\
commands/TOPIC.cpp\
commands/INVITE.cpp\
commands/NAMES.cpp\
commands/LIST.cpp\
commands/KICK.cpp\
commands/JOIN.cpp\
commands/PONG.cpp\
commands/QUIT.cpp\
commands/PRIVMSG.cpp\
commands/NOTICE.cpp\
commands/MODE.cpp\

MSRC :=

BSRC :=

OBJ := $(addprefix $(OUTDIR)/, $(SRC:.cpp=.o))
MOBJ := $(addprefix $(OUTDIR)/, $(MSRC:.cpp=.o))
BOBJ := $(addprefix $(OUTDIR)/, $(BSRC:.cpp=.o))

DEP := $(addprefix $(OUTDIR)/, $(SRC:.cpp=.d) $(MSRC:.cpp=.d) $(BSRC:.cpp=.d))

.PHONY: all bonus debug re re-bonus debug-bonus clean fclean

all: $(NAME)

bonus: $(NAME)_bonus

clean:
	rm -rf $(OUTDIR)

fclean:
	rm -rf $(OUTDIR)
	rm -rf $(NAME)
	rm -rf $(NAME)_bonus

re: fclean all
re-bonus: fclean bonus

debug: CXXFLAGS += -g
debug: all
debug-bonus: CXXFLAGS += -g
debug-bonus: bonus

$(NAME): $(OBJ) $(MOBJ)
	$(CXX) -o $(NAME) $(OBJ) $(MOBJ)

$(NAME)_bonus: $(OBJ) $(BOBJ)
	$(CXX) -o $(NAME)_bonus $(OBJ) $(BOBJ)

$(OUTDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MF $(@:.o=.d) -c -o $@ $<

-include $(DEP)
