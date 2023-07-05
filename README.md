# API 관련 문서

## API 관련 정보

- [[BODY 중 type 값 의미]](/doc/type.md#type의-의미)
- [[BODY 중 id 값 의미]](/doc/type.md#id의-의미)
- [[BODY 중 value 값 의미]](/doc/type.md#value의-의미)
 
```
METHOD: POST
BODY TYPE: JSON
HTTP API PATH /serial 
BODY Example:
{"type":3, "id":1,"value":1023}
```

# 어떻게 빌드 합니까?

## Windows

```shell
# 파워쉘(관리자 권한)기준 입니다.

$ Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
$ choco install git cmake
$ git clone --recursive https://github.com/Piorosen/SSvJoy-PC
$ git clone https://github.com/microsoft/vcpkg
$ .\vcpkg\bootstrap-vcpkg.bat
$ .\vcpkg\vcpkg.exe install --triplet=x64-windows drogon cxxopts spdlog
$ .\vcpkg\vcpkg.exe integrate install
$ cd SSvJoy-PC
$ mkdir build
$ cd build
$ cmake .. -G "Visual Studio 17 2022" -T host=x86 -A x64 --build --config Release --target ALL_BUILD
```

## Linux(ubuntu)

```shell
$ sudo apt install git cmake make
$ git clone --recursive https://github.com/Piorosen/SSvJoy-PC
$ git clone https://github.com/microsoft/vcpkg
$ ./vcpkg/bootstrap-vcpkg.sh
$ ./vcpkg/vcpkg install --triplet=x64-linux drogon cxxopts spdlog
$ ./vcpkg/vcpkg integrate install
$ cd SSvJoy-PC && mkdir build && cd build && cmake .. -D$(pwd)/../../vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake
$ make -j$(nproc)
```


