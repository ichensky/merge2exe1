gcc evil.c -o evil.exe
gcc real.c -o real.exe
#
echo "const unsigned char evil[] = {" > evil.h
cat evil.exe | hexdump -v -e '"0x" 1/1 "%02X" ","' | sed s/,$// >> evil.h
echo "};" >> evil.h
#
#
echo "const unsigned char real[] = {" > real.h
cat real.exe | hexdump -v -e '"0x" 1/1 "%02X" ","' | sed s/,$// >> real.h
echo "};" >> real.h
#
gcc main.c -o a.exe
