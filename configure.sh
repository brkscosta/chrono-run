#!/bin/bash

show_help() {
  echo "Usage: $(basename "$0") [OPTION] [BUILD_TYPE]"
  echo
  echo "Options:"
  echo "  -h, --help        Show this help message and exit"
  echo "  --deleteBuild     Delete the existing build folder before building"
  echo
  echo "Build types:"
  echo "  Release           Build the project in Release mode"
  echo "  Debug             Build the project in Debug mode (default)"
}

if [[ $1 == "-h" || $1 == "--help" ]]; then
  show_help
  exit 0
fi

install_pip() {
  if ! command -v pip &> /dev/null; then
    echo "WARNING: pip not found. Attempting to install pip..."
    sudo apt-get update && sudo apt-get install -y python3-pip
  fi
}

check_and_delete_build_folder() {
  if [ -d "build" ]; then
    echo "Deleting existing build folder..."
    rm -rf build || { echo "Failed to delete build folder"; exit 1; }
  fi
}

install_conan() {
  if ! command -v conan &> /dev/null; then
    echo "Conan not found. Installing..."
    pip install conan==2.8.1 || { echo "Failed to install Conan"; exit 1; }
  fi
}

create_default_profile() {
  if ! conan profile list | grep -q 'default'; then
    echo "Creating default profile..."
    conan profile detect || { echo "Failed to create default profile"; exit 1; }
  fi
}

source_env_file() {
  if [ -f ".env" ]; then
    source .env
  fi
}

install_dependencies() {
  conan install . --build=missing -of build -s build_type=$1 -s compiler.cppstd=20 || { echo "Failed to install dependencies"; return 1; }
}

build_project() {
  local build_type=$1
  local cmake_build_type
  local has_gtest=$3

  if [[ $build_type == "Release" ]]; then
    cmake_build_type="Release"
  elif [[ $build_type == "Debug" ]]; then
    cmake_build_type="Debug"
  else
    echo "Invalid build type. Please specify either 'Release' or 'Debug'."
    return 1
  fi

  cmake -B build -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DHAS_GTEST=$has_gtest -DCMAKE_BUILD_TYPE=$cmake_build_type || { echo "Failed to configure CMake project"; return 1; }
}

print_compilation_result() {
  if [ $? -eq 0 ]; then
    echo -e "\e[32mConfiguration successful.\e[0m"
  else
    echo -e "\e[31mFailed to configure project.\e[0m"
  fi
}

# Process options
delete_build_folder=false

while [[ $# -gt 0 ]]; do
  case $1 in
    --deleteBuild)
      delete_build_folder=true
      shift
      ;;
    --gtest)
      has_gtest=ON
      shift
      ;;
    Release|Debug)
      build_type=$1
      shift
      ;;
    *)
      echo "Invalid option: $1"
      show_help
      exit 1
      ;;
  esac
done

# Default build type if not set
build_type=${build_type:-Debug}
has_gtest=${has_gtest:-OFF}

install_pip
install_conan
create_default_profile
source_env_file

if [ "$delete_build_folder" = true ]; then
  check_and_delete_build_folder
fi

install_dependencies $build_type
build_project $build_type $has_gtest
print_compilation_result
