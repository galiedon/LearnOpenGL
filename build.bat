cmake .

@REM 第一次生成的时候会因为没有glad而报错
cmake --build .

@REM 第二次会在第一次生成的基础上继续。
cmake --build .

cmake --install . --prefix "Debug" --config Debug