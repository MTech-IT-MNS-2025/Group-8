
# RC4 WebAssembly — Assignment 4

## Project Overview

This project implements the RC4 stream cipher in native C, compiled to WebAssembly (WASM) using Emscripten, and executed in the browser via a Next.js frontend.

## Learning Objectives

- Implement RC4 encryption/decryption in native C.
- Compile C code to WebAssembly using Emscripten.
- Expose C functions to JavaScript using `cwrap`.
- Call native C from a Next.js frontend.
- Handle text input/output between JS and WASM memory.

---

## Technologies Used

- C Language — RC4 implementation
- Emscripten — C → WASM compiler
- WebAssembly (WASM) — browser-executable binary
- Next.js (React) — frontend interface
- JavaScript — glue code and UI logic

---

## Getting Started

### 1. Clone the Repository

```bash
git clone <your-repo-url>
cd ASSIGNMENT-4
```

### 2. Install Dependencies

```bash
npm install
```

### 3. Run the Development Server

```bash
npm run dev
```

### 4. Open in Browser

Visit:

```
http://localhost:3000
```

---

## Compile Instructions (from run.txt)

If you modify rc4.c, recompile using:

```bash
emcc rc4.c \
  -sEXPORTED_FUNCTIONS='["_encrypt","_decrypt"]' \
  -sEXPORTED_RUNTIME_METHODS='["cwrap"]' \
  -sMODULARIZE=1 \
  -sEXPORT_ES6=1 \
  -o rc4.js
```

This generates:

- rc4.js → JS glue code
- rc4.wasm → WebAssembly binary

Place both files inside the /public folder.

---

## How It Works

- Encrypt: Input: plaintext + key → Output: ciphertext in hex (e.g. 39668cc2)
- Decrypt: Input: hex ciphertext + same key → Output: original plaintext

---

## UI Features

- Textbox for plaintext or ciphertext (hex)
- Textbox for key
- Encrypt button
- Decrypt button
- Result display area
```
