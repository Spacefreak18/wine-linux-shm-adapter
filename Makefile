all: assets/shmwrapper1.exe assets/shmwrapper2.bin assets/shmwrapper3.exe assets/shmwrapperwintest.exe

CC=gcc
WINECC=i686-w64-mingw32-gcc
CFLAGS=-Wall -Os -g

assets/shmwrapperwintest.exe: shmwrapperwintest.c
	$(WINECC) $< $(CFLAGS) -mconsole -o $@

assets/shmwrapper3.exe: shmwrapper3.c
	$(WINECC) $< $(CFLAGS) -mconsole -o $@

assets/shmwrapper2.bin: shmwrapper2.c
	$(CC) $< $(CFLAGS) -o $@

assets/shmwrapper1.exe: shmwrapper1.c
	$(WINECC) $< $(CFLAGS) -mconsole -o $@

clean:
	rm -f assets/shmwrapper1.exe assets/shmwrapper2.bin assets/shmwrapper3.exe assets/shmwrapperwintest.exe

# vim: syntax=make ts=4 sw=4 sts=4 sr noet
