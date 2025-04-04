#!/bin/bash

mkdir -p ../reports
rm -f ../reports/overflow_log.txt

echo "🔧 Compiling test cases..."
gcc -fno-stack-protector -g -lncurses -o safe ../test/test_safe.c ../src/stumpy.c ../src/utils.c
gcc -fno-stack-protector -g -lncurses -o overflow ../test/test_overflow.c ../src/stumpy.c ../src/utils.c

echo -e "\n✅ Running safe test:"
./safe

echo -e "\n🚨 Running overflow test:"
./overflow

echo -e "\n📝 Overflow Log Contents:"
cat ../reports/overflow_log.txt