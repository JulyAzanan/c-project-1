projet: main.c lists.o plate.o AI.o
	gcc -Wall -o projet $^

test_plate: plate.o lists.o
	gcc -Wall -o plate $^	

lists.o: lists.c lists.h
	gcc -Wall -c $<

plate.o: plate.c plate.h lists.h
	gcc -Wall -c $<

AI.o: AI.c lists.h plate.h
	gcc -Wall -c $<