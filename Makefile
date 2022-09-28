CC= gcc

FLAGS= -lncurses

ALL = game

%.o: %.c
	$(CC) -c $<

game: le_canyon_de_la_mort.o menu.o score.o
	$(CC) $^ -o $@ $(FLAGS)

clean:
	rm -f *.o
	
clear:
	rm -f $(ALL)
