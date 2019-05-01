#// # Makefile
#// # Řešení IJC-DU2, 25.4.2019
#// # Autor: xhajek48 (Karel Hajek), FIT VUT

C=gcc -std=c99 -pedantic -Wall -Wextra -g
CPP=g++ -std=c++11 -pedantic -Wall -g

all:tail tail2 libhtab.a libhtab.so wordcount-dynamic wordcount

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(C) $^ -o $@

wordcount: wordcount.o io.o libhtab.a
	$(C) $^ -o $@
wordcount.o: wordcount.c
	$(C) -c $<
io.o: io.c io.h
	$(C) -c $<
#####################################
#### C TAIL
tail:tail.o
	$(C) tail.o -o tail
tail.o:tail.c
	$(C) -c tail.c -o tail.o
############################
######## C++ TAIL
tail2:tail2.o
	$(CPP) tail2.o -o tail2

tail2.o:tail.cc
	$(CPP) -c tail.cc -o tail2.o
###############################
############# STATIC LIBRARY 
libhtab.a: htab_begin.o htab_bucket_count.o htab_clear.o htab_end.o htab_free.o htab_hash_function.o htab_init.o htab_item_init.o htab_iterator_get_key.o htab_iterator_get_value.o htab_iterator_init.o htab_iterator_next.o htab_iterator_set_value.o htab_lookup_add.o htab_move.o htab_size.o
	ar rcs $@ $^

libhtab.so: htab_begin.o htab_bucket_count.o htab_clear.o htab_end.o htab_free.o htab_hash_function.o htab_init.o htab_item_init.o htab_iterator_get_key.o htab_iterator_get_value.o htab_iterator_init.o htab_iterator_next.o htab_iterator_set_value.o htab_lookup_add.o htab_move.o htab_size.o
	$(C) -fPIC -shared $^ -o $@

htab_begin.o: htab_begin.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_bucket_count.o: htab_bucket_count.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_clear.o: htab_clear.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_end.o: htab_end.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_free.o: htab_free.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_hash_function.o: htab_hash_function.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_init.o: htab_init.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_item_init.o: htab_item_init.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_iterator_get_key.o: htab_iterator_get_key.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_iterator_get_value.o: htab_iterator_get_value.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_iterator_init.o: htab_iterator_init.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_iterator_next.o: htab_iterator_next.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_iterator_set_value.o: htab_iterator_set_value.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_lookup_add.o: htab_lookup_add.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_move.o: htab_move.c htab.h htab_structs.h
	$(C) -fPIC -c $<

htab_size.o: htab_size.c htab.h htab_structs.h
	$(C) -fPIC -c $<


clean:
	rm *.o tail tail2 wordcount libhtab.a libhtab.so wordcount-dynamic