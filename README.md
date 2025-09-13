# PropertyParser

A lightweight C library for parsing `.properties` files into a map containing
key-value pairs.

## Features

- Parse `.properties` files with colon-seperated key-value pairs
- Store and retrieve property values by key
- Memory-efficient implementation with cleanup functionality
- Simple API for easy integration

## Installation

### Prerequissites

- C compiler (GCC, Clang, etc.)
- CMake (3.10 or higher)

### Building from source

```bash
# Clone repository
git clone https://github.com/NahtannL/PropertyParser.git
cd PropertyParser

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run tests
make test

```

## Usage

### File Format
The `.properties` file should follow this format:

```
key1: value1
key2: value2

```