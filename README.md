# A simple pong game in SDL2/C++

> Project "what I cannot create, I do not understand"

![Peek 2021-03-22 00-54](https://user-images.githubusercontent.com/20123683/111943876-c50e7880-8aac-11eb-849e-a98f12ca7e43.gif)

# Copy-Pasta

<https://lazyfoo.net/tutorials/SDL/index.php>

# Windows/MSVC

+ setup vcpkg -> https://github.com/microsoft/vcpkg
+ add vcpkg to PATH
+ vcpkg install sdl2 sdl2_ttf
+ add cmake option `-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`

# Windows/mingw64/MSYS2

`pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf`

