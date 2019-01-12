function build {
    g++ main.cpp -o basm -w -static -std=c++11
    chmod +x basm
}
