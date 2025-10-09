all:
	gcc main.c TADs/*.c -o pronto_socorro

clean:
	del pronto_socorro.exe 2>nul || rm -f pronto_socorro


