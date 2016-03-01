CFLAGS = -std=c99 -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

testdominion: testdominion.c dominion.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c testdominion.c rngs.c -o testdominion -lm -g

domTest:
	./testdominion &> gameResults.out
	gcov dominion.c &> testdominion.out
	cat dominion.c.gcov >> testdominion.out

adventurer:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurer.c rngs.c -o randomtestadventurer -lm -g

runAdventurer: adventurer
	./randomtestadventurer &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomcard:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard.c rngs.c -o randomtestcard -lm -g

runRandomCard: randomcard
	./randomtestcard &> randomtestcard.out
	gcov dominion.c >> randomtestcard.out
	cat dominion.c.gcov &> randomcard.out


playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

playdom2: dominion.o playdom2.c
	gcc -o playdom2 playdom2.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unit1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c -o unittest1 -lm -g

unit2:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c -o unittest2 -lm -g

unit3:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c -o unittest3 -lm -g

unit4:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c -o unittest4 -lm -g

card1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c -o cardtest1 -lm -g

card2:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c -o cardtest2 -lm -g

card3:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c -o cardtest3 -lm -g

card4:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest4.c rngs.c -o cardtest4 -lm -g

test: unit1 unit2 unit3 unit4 card1 card2 card3 card4

myTest: clean test
	./unittest1 &> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


coverage:
	make clean
	make unit1
	./unittest1
	gcov dominion.c &> coverage.out
	make clean
	make unit2
	./unittest2
	gcov dominion.c >> coverage.out
	make clean
	make unit3
	./unittest3
	gcov dominion.c >> coverage.out
	make clean
	make unit4
	./unittest4
	gcov dominion.c >> coverage.out
	make clean
	make card1
	./cardtest1
	gcov dominion.c >> coverage.out
	make clean
	make card2
	./cardtest2
	gcov dominion.c >> coverage.out
	make clean
	make card3
	./cardtest3
	gcov dominion.c >> coverage.out
	make clean
	make card4
	./cardtest4
	gcov dominion.c >> coverage.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o testdominion testDrawCard badTestDrawCard playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
