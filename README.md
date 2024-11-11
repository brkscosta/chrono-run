# Chrono Run Game

## Install developement tools (Linux)

Install clangd clang-tidy clang-format and g++-9 compiler:

```bash
sudo apt install -y clang-tidy-15 clangd-15 clang-format-15 clang-format-15 g++-9
```

Create links:

```bash
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 9
```

```bash
sudo update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-15 100
```

```bash
sudo update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-15 15
```

```bash
sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-15 15
```

Install gdb for debugging:

```bash
sudo apt-get -y install gdb
```

## Configure and compile the project

There is some bash scripts to configure and build the project.

To configure the project:
```bash
./configure.sh
```
This script will install the **pip** and **Conan2** if not found on your machine. After installation it will create a conan profile and download the dependencies from [Conan Center](https://conan.io/).

To build the project:

```bash
./build.sh
```

## Run the executable

The binary is generated in the `build` folder.

```bash
./build/ChronoRun
```