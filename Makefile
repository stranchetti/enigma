CC= g++
CFLAGS= -c -Wall -g
LFLAGS= -Wall -g
UTFLAGS= -pthread
SOURCE= src
TEST= test

.PHONY: clean

enigma: wheel.o ref.o stecker.o enigma.o
	$(CC) $(LFLAGS) -o $@ $^

enigma.o: $(SOURCE)/enigma.cpp
	$(CC) $(CFLAGS) $^

ref.o: $(SOURCE)/ref.cpp
	$(CC) $(CFLAGS) $^

wheel.o: $(SOURCE)/wheel.cpp
	$(CC) $(CFLAGS) $^

stecker.o: $(SOURCE)/stecker.cpp
	$(CC) $(CFLAGS) $^

UTFramework.o: $(TEST)/UTFramework.cpp
	$(CC) $(UTFLAGS) $(CFLAGS) $^

ref_test: UTFramework.o ref.o $(TEST)/ref_test.cpp
	$(CC) $(LFLAGS) $(UTFLAGS) -o $@ $^

wheel_test: UTFramework.o wheel.o $(TEST)/wheel_test.cpp
	$(CC) $(LFLAGS) $(UTFLAGS) -o $@ $^

stecker_test: UTFramework.o stecker.o $(TEST)/stecker_test.cpp
	$(CC) $(LFLAGS) $(UTFLAGS) -o $@ $^

etest.o: $(SOURCE)/enigma.cpp
	$(CC) $(CFLAGS) -D TESTING -o $@ $^

enigma_test: UTFramework.o ref.o wheel.o stecker.o etest.o $(TEST)/enigma_test.cpp
	$(CC) $(LFLAGS) $(UTFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f *~
	rm -f enigma
	rm -f *_test
