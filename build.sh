#!/bin/bash
i686-w64-mingw32-g++ main.cpp -o bin/basm-windows32.exe -static -static-libgcc -static-libstdc++ -m32
i686-w64-mingw32-g++ main.cpp -o bin/basm-windows64.exe -static -static-libgcc -static-libstdc++
g++ main.cpp -o bin/basm-linux32 -static -static-libgcc -static-libstdc++ -m32
g++ main.cpp -o bin/basm-linux64 -static -static-libgcc -static-libstdc++ 
