set -e
g++ -std=c++17 -Wall -Wextra -O3 -o main utils.cpp main.cpp -lsfml-graphics -lsfml-window -lsfml-system 
