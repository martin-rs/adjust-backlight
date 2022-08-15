CC=cc
CFLAGS=-Wall -std=c17

SRC=adjust-brightness.c

BIN_PATH=${SCRIPTDIR}/system/br

all:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN_PATH)

clean:
	rm -f $(BIN_PATH)
