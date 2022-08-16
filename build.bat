
echo off
set build_path=Build
set install_path="Binaries\Debug"

cmake -S . -B %build_path%

@REM 第一次生成的时候会因为没有glad而报错
cmake --build %build_path%

@REM 第二次会在第一次生成的基础上继续。
cmake --build %build_path%

cmake --install %build_path% --prefix %install_path% --config Debug