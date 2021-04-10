Hi, there are two versions of this game:
1. Assignment Version (no bosses)
2. Bosses Version

To run (currently): clang++ *.cpp GameObject/*.cpp GameObject/bosses/*.cpp Math/*.cpp Manager/*.cpp -Wno-deprecated-declarations -framework GLUT -framework OpenGL -framework Carbon -std=c++14  -o main