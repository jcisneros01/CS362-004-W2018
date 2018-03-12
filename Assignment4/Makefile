CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o 
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

runadventure: randomtestadventurer 
	./randomtestadventurer &> randomtestadventurerresult.out
	gcov dominion.c >> randomtestadventurerresult.out
	cat dominion.c.gcov >> randomtestadventurerresult.out


randomtestadventurer2: randTest_adventurerCard.c dominion.o rngs.o 
	gcc -o randTest_adventurerCard -g  randTest_adventurerCard.c dominion.o rngs.o $(CFLAGS)
runadventure2: randTest_adventurerCard 
	./randTest_adventurerCard &> randTest_adventurerCard.out
	gcov dominion.c >> randTest_adventurerCard.out
	cat dominion.c.gcov >> randTest_adventurerCard.out

clean:
	rm -f *.o *.exe randTest_adventurerCard randomtestadventurer test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out

