CC=cc
CFLAGS=-Wall -std=c17

SRC=bl.c

BIN_PATH=${SCRIPTDIR}/system/bl

all:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN_PATH)

clean:
	rm -f $(BIN_PATH)
