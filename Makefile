projet: main.c lists.o plate.o AI.o myrandom.o
	gcc -Wall -Wextra -o projet $^

lists.o: lists.c lists.h
	gcc -Wall -c $<

plate.o: plate.c plate.h lists.h
	gcc -Wall -c $<

AI.o: AI.c AI.h lists.h plate.h myrandom.h
	gcc -Wall -c $<

myrandom.o: myrandom.c myrandom.h
	gcc -Wall -c $<