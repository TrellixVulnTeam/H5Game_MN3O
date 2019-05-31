@echo on

if not exist build2013 mkdir build2013
cd build2013
cmake -G "Visual Studio 12 2013" ..

cd ..
pause