CFLAGS=-c -lX11 -g
OUTPUTS=main.o bot.o window.o input.o
NAME=bot

all: $(NAME)

$(NAME): $(OUTPUTS)
	g++ $(OUTPUTS) -o $(NAME) -lX11
	
main.o: src/main.cpp
	g++ $(CFLAGS) src/main.cpp
	
bot.o: src/bot.cpp
	g++ $(CFLAGS) src/bot.cpp
	
window.o: src/window.cpp
	g++ $(CFLAGS) src/window.cpp
	
input.o: src/input.cpp
	g++ $(CFLAGS) src/input.cpp
	
clean: 
	rm -rf *.o $(NAME)