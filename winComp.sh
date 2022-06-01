clear && x86_64-w64-mingw32-g++ -o pongLan.exe ./src/* \
-ISFML-2.5.1/include/ -lws2_32  \
-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread \
-LSFML-2.5.1/lib/ -Lfreetype-windows-binaries-2.11.0/release\ dll/win64/ -D SFML_STATIC \
-lsfml-window-s  -lsfml-graphics-s -lsfml-system-s  -lopengl32  -lwinmm  -lgdi32 \
-Wl,-Bstatic -lfreetype

# -l:libgdi32.a -l:libopengl32.a -l:libwinmm.a