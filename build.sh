set -e
CC=g++
STD=c++17
OPT=-O0
FLAGS="$OPT -g -Wall -Wextra -Werror -pedantic"
SRC="utils.cpp main.cpp"
OUT=main
LINKS="-lsfml-graphics -lsfml-window -lsfml-system"
$CC -std=$STD $WARNING $OPT -o $OUT $SRC $LINKS
