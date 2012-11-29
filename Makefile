CC = gcc
CFLAGS = -Wall
FUSE = `pkg-config fuse --cflags --libs`

PFS_OBJ = pfs.o
PFS_TARGET = pfs

all: $(PFS_TARGET)

$(PFS_TARGET) : CFLAGS += $(FUSE)
$(PFS_TARGET) : $(PFS_OBJ)
	$(CC) $(CFLAGS) -o $(PFS_TARGET) $(PFS_OBJ)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PFS_OBJ) $(PFS_TARGET)
