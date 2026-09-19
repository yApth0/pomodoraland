taskkill /f /im arena.exe
cmake -G "MinGW Makefiles" -B build
cmake --build build --config Debug
