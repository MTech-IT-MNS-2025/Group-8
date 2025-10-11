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
g++ alice.cpp -o alice -lOQS

```
 > This links your code with the liboqs library, which seems required from the use of OQSKEM functions in your code.
>  Prepare for execution:
Make sure required header files and libraries (oqs/oqs.h, liboqs) are installed, and any input files (ciphertext.bin from Bob) are available in the working directory.
#### Run the executable
```bash
./alice
# This will execute your compiled program.
```
>Generate a keypair (saves alicepk.bin and alicesk.bin)
Wait for ciphertext.bin from Bob
Attempt to decapsulate and output the shared secret if successful.
>
### To run your C++ program in the file "bob.cpp"
#### Requirements
The file alicepk.bin (Alice's public key) must already exist in the working directory, created by first running alice.cpp first.
>The liboqs development package must be installed, ensuring all header files are accessible.

### Compile the Program
```bash
g++ bob.cpp -o bob -lOQS

```
> This command compiles the code and links with liboqs, which is required for the quantum-safe cryptography functions present in the code.

### Run the Program
```bash
./bob
```
> This command will perform the following:
 Reads Alice's public key from alicepk.bin
 Generates ciphertext and shared secret
 Saves ciphertext in ciphertext.bin for Alice to use .
