

Important References:

https://gbdev.io/pandocs/

https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html

https://archive.org/details/GameBoyProgManVer1.1/page/n85/mode/2up

https://github.com/rockytriton/LLD_gbemu/raw/main/docs/The%20Cycle-Accurate%20Game%20Boy%20Docs.pdf

https://github.com/rockytriton/LLD_gbemu/raw/main/docs/gbctr.pdf


NOTE: Designed to run on Linux, but you can build on Windows with MSYS2 and mingw-w64

Windows Environment Setup:

1. Install MSYS2:  https://www.msys2.org/

2. Follow instructions 1 through 7 on the MSYS2 page.

3. pacman -S cmake

4. pacman -S mingw64/mingw-w64-x86_64-SDL2 mingw64/mingw-w64-x86_64-SDL2_mixer mingw64/mingw-w64-x86_64-SDL2_image mingw64/mingw-w64-x86_64-SDL2_ttf mingw64/mingw-w64-x86_64-SDL2_net

5. pacman -S mingw-w64-x86_64-check

After above steps you should be able to build from Windows using MSYS2 just like in the videos.


