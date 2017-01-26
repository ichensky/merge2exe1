#!/bin/sh

function bin_to_hex {
	echo "const unsigned char $1[] = {" > $1.h
	cat $1.exe | hexdump -v -e '"0x" 1/1 "%02X" ","' | sed s/,$// >> $1.h
	echo "};" >> $1.h
}

evil=evil
real=real
app=a

gcc $evil.c -o $evil.exe
gcc $real.c -o $real.exe

bin_to_hex $evil
bin_to_hex $real

gcc main.c -o $app.exe
