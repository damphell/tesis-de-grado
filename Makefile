INCLUDE = include
CFLAGS  = -g -DDEBUG -Wall -I$(INCLUDE) -L$(INCLUDE) -I/usr/include/mysql -DBIG_JOINS=1 -fno-strict-aliasing -g
LIBS    = -lmodreparto -L/usr/lib/x85_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -ldl -lncurses
O_MAIN  = programa_test.o
O_LIBS  = libmodreparto.a
BIN     = programa_usalib

CC      = gcc

all: $(BIN)

$(BIN): $(O_MAIN) $(INCLUDE)/$(O_LIBS)
	$(CC) -o $(BIN) $(CFLAGS) $(O_MAIN) $(LIBS)

$(O_MAIN): programa_test.c
	$(CC) -c programa_test.c

$(INCLUDE)/$(O_LIBS): $(INCLUDE)/libmodreparto.a($(INCLUDE)/reparto.o $(INCLUDE)/recup.o $(INCLUDE)/rep_secreto.o $(INCLUDE)/connectDB.o)
#$(O_LIBS): $(INCLUDE)/librepblue.a($(INCLUDE)/repblue.o)

clean:
	rm $(BIN) $(O_MAIN) $(INCLUDE)/$(O_LIBS)
-I/usr/include/mysql -DBIG_JOINS=1 -fno-strict-aliasing -g
