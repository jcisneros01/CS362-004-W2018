CFLAGS = -Wall -std=c99 -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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

randomtestadventurer.out: randomtestadventurer.c dominion.c rngs.c
	echo "Result for running Adventurer Random Tests:" > randomtestadventurer.out
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.c rngs.c $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov randomtestadventurer.c >> randomtestadventurer.out
	echo "Adventurer stats" >> randomtestadventurer.out
	gcov -abcfu dominion.c | sed -n '/adventurerEffects/{n;p; n;p; n;p;}' >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1.out:  randomtestcard1.c dominion.c rngs.c
	echo "Result for running Smithy Random Tests:" > randomtestcard1.out
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.c $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov randomtestcard1.c >> randomtestcard1.out
	echo "Smithy stats" >> randomtestcard1.out
	gcov -abcfu dominion.c | sed -n '/smithyEffects/{n;p; n;p; n;p;}' >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out:  randomtestcard2.c dominion.c rngs.c
	echo "Result for running Village Random Tests:" > randomtestcard2.out
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.c $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov randomtestcard2.c >> randomtestcard2.out
	echo "Village stats" >> randomtestcard2.out
	gcov -abcfu dominion.c | sed -n '/villageEffects/{n;p; n;p; n;p;}' >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom randomtestcard1 randomtestadventurer randomtestcard2 player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -rf *.dSYM
