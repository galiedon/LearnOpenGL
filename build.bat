
echo off
set build_path=Build
set install_path="Binaries\Debug"

cmake -S . -B %build_path%

@REM ��һ�����ɵ�ʱ�����Ϊû��glad������
cmake --build %build_path%

@REM �ڶ��λ��ڵ�һ�����ɵĻ����ϼ�����
cmake --build %build_path%

cmake --install %build_path% --prefix %install_path% --config Debug