@echo off

REM C:\Users\artem\AppData\Local\Programs\Python\Python312\libs
set PYTHONDIR=C:\Users\artem\AppData\Local\Programs\Python\Python312
set PYBIND11DIR=%PYTHONDIR%\Lib\site-packages\pybind11\include

g++ -O3 -Wall -shared -std=c++17 -static-libgcc -static-libstdc++ ^
  -I%PYTHONDIR%\include ^
  -I%PYBIND11DIR% ^
  -L%PYTHONDIR%\libs ^
  hashing_mod.cpp -o hashing_mod.pyd -lpython312