CC      = gcc
CFLAGS  = -g3 -fPIC -O0
LDFLAGS = -shared

all: libgini.so

gini_calc.o: gini_calc.S
	$(CC) $(CFLAGS) -c gini_calc.S -o gini_calc.o

libgini.so: gini_calc.c gini_calc.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o libgini.so gini_calc.c gini_calc.o

clean:
	rm -f gini_calc.o libgini.so