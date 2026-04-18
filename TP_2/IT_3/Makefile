CC      = gcc
CFLAGS  = -g3 -O0

all: gini_api_c

gini_api_c: gini_api.c gini_calc.c
	$(CC) $(CFLAGS) gini_api.c gini_calc.c -lcurl -o gini_api_c

clean:
	rm -f gini_api_c