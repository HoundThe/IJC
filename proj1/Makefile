# Makefile
# Řešení IJC-DU1, 20.3.2019
# Autor: xhajek48 (Karel Hajek), FIT VUT
# Přeloženo: gcc 8.2.1


# promenne
LC_ALL=cs._CZ.utf8
COMPILER=gcc
FLAGS= -O2 -std=c11 -Wall -pedantic -Wextra

all:steg-decode primes primes-i

run: primes primes-i
	time ./primes
	time ./primes-i

steg-decode: steg-decode.o error.o ppm.o eratosthenes.o bit_array.o
	$(COMPILER) $(FLAGS) steg-decode.o error.o ppm.o eratosthenes.o bit_array.o -o steg-decode -lm
primes: primes.o error.o eratosthenes.o bit_array.o
	$(COMPILER) $(FLAGS) primes.o error.o bit_array.o eratosthenes.o -o primes -lm
primes-i: primes-i.o error.o eratosthenes-i.o bit_array-i.o
	$(COMPILER) $(FLAGS) primes-i.o error.o bit_array-i.o eratosthenes-i.o -o primes-i -lm

##########################
#	PRIMES
##########################

primes.o: primes.c
	$(COMPILER) $(FLAGS) -c primes.c -o primes.o

eratosthenes.o: eratosthenes.c
	$(COMPILER) $(FLAGS) -c eratosthenes.c -o eratosthenes.o

bit_array.o: bit_array.c
	$(COMPILER) $(FLAGS) -c bit_array.c -o bit_array.o

bit_array-i.o: bit_array.c
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c bit_array.c -o bit_array-i.o 

primes-i.o: primes.c
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

eratosthenes-i.o: eratosthenes.c
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o

##########################
#	STEG
##########################

error.o: error.c
	$(COMPILER) $(FLAGS) -c error.c -o error.o 

ppm.o: ppm.c
	$(COMPILER) $(FLAGS) -c ppm.c -o ppm.o

steg-decode.o: steg-decode.c
	$(COMPILER) $(FLAGS) -c steg-decode.c -o steg-decode.o


clean: clear

clear:
	rm *.o primes steg-decode primes-i
