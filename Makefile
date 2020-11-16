CC := g++
CFLAGS := -pthread -O3 -std=c++14

.PHONY: all clean
all: obj prodcon

obj:
	@mkdir obj

prodcon: obj/main.o obj/Producer.o obj/Consumer.o obj/tands.o obj/Summary.o
	$(CC) $(CFLAGS) obj/main.o obj/Producer.o obj/Consumer.o obj/tands.o obj/Summary.o -o prodcon

obj/Consumer.o: src/Consumer.cpp include/Consumer.h include/Summary.h include/sharedVariables.h include/tands.h
	$(CC) $(CFLAGS) src/Consumer.cpp -c -o obj/Consumer.o 

obj/Producer.o: src/Producer.cpp include/Producer.h include/Consumer.h include/Summary.h include/sharedVariables.h include/tands.h
	$(CC) $(CFLAGS) src/Producer.cpp -c -o obj/Producer.o

obj/tands.o: src/tands.cpp include/tands.h
	$(CC) $(CFLAGS) src/tands.cpp -c -o obj/tands.o

obj/Summary.o: src/Summary.cpp include/Summary.h include/sharedVariables.h
	$(CC) $(CFLAGS) src/Summary.cpp -c -o obj/Summary.o

obj/main.o: src/main.cpp include/includes.h include/Producer.h include/Summary.h include/sharedVariables.h include/Consumer.h include/tands.h
	$(CC) $(CFLAGS) src/main.cpp -c -o obj/main.o 

clean:
	@rm -rf obj/
	@rm -f prodcon

#https://www.math.colostate.edu/~yzhou/computer/writemakefile.html