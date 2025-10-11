# Running Programs with liboqs on Linux

This guide explains the steps to install **liboqs** and run your C programs that use quantum-safe cryptography.

---

## Steps to Run the Programs

### Step 1: Update System
```bash
sudo apt update
sudo apt upgrade -y
```

---

### Step 2: Install Required Build Tools
```bash
sudo apt install -y build-essential gcc g++ make cmake git ninja-build
```

---

### Step 3: Clone and Build liboqs
```bash
# Go to a folder where you want liboqs
cd ~
git clone https://github.com/open-quantum-safe/liboqs.git
cd liboqs

# Create build directory
mkdir build && cd build

# Configure build with CMake and Ninja
cmake -GNinja -DCMAKE_INSTALL_PREFIX=/usr/local ..
ninja

# Install the library
sudo ninja install
```

---

### Step 4: Compile Programs
#### Task 1: List Supported Algorithms
```bash
gcc list_algorithms.c -loqs -lcrypto -ldl -o list_algorithms
./list_algorithms
```

> `-loqs` links liboqs, `-lcrypto` links OpenSSL (required by liboqs), and `-ldl` links the dynamic loader library.

 ### To run your C++ program in the file "alice.cpp"

#### Compile the program

```bash
g++ alice.cpp -o alice

# This will compile the code and create an executable named "alice".
```
#### Run the executable
```bash
./alice
# This will execute your compiled program.
```
