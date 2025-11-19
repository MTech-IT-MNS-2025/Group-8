# Diffie–Hellman Key Exchange (WebAssembly + JavaScript + Node.js)

🚀 This project implements a complete Diffie–Hellman Shared Secret Key Exchange using:

- C (modular exponentiation)
- WebAssembly (WASM) compiled via Emscripten
- Frontend (HTML + JavaScript)
- Backend (Node.js + Express)

WASM handles all expensive modular exponentiation operations such as:
- \( x = g^a \mod p \)
- \( y = g^b \mod p \)
- \( K = x^b \mod p \)

## 📁 Project Structure

my-wasm-project/

├── public/

│ ├── index.html 

│ ├── modexp.js 

│ └── modexp.wasm

├── src/

│ └── myprog.c

├── server/

│ └── server.js 

└── package.json


## 🔧 Requirements

- Node.js installed
- Emscripten SDK (emsdk) installed
- PowerShell / VS Code Terminal

## ⚙️ Installing & Activating Emscripten (Windows)

Install or clone emsdk in:  
`E:\my-wasm-project\emsdk`


- Activate the environment:
- cd E:\my-wasm-project\emsdk
- .\emsdk_env.bat
*Note: You MUST run this command every time before using emcc.*


## 🔨 Step 1: Compile C → WebAssembly
cd E:\my-wasm-project\emsdk

cd E:\my-wasm-project\emsdk

cd E:\my-wasm-project\src

emcc myprog.c -Os -s WASM=1 -s

EXPORTED_FUNCTIONS='["_modexp"]' -s 

EXPORTED_RUNTIME_METHODS='["ccall"]' -o ../public/modexp.js

This generates `modexp.js` and `modexp.wasm` inside the `public/` folder.

## 🌐 Step 2: Start the Backend Server

cd E:\my-wasm-project

node server/server.js 

The server will be available at: `http://localhost:5000`

## 🖥️ Step 3: Run Frontend

Serve the `public` folder:


npx serve public -p 3000

Open your browser at: [http://localhost:3000](http://localhost:3000)

## 🔑 What Happens Internally?

- Client enters \( p \) and \( g \)
- Generates random \( a \)
- Computes \( x = g^a \mod p \) using WASM
- Sends `{ g, p, x }` to server

- Server generates random \( b \)
- Computes \( y = g^b \mod p \) using WASM
- Computes shared key \( K = x^b \mod p \) using WASM
- Sends `{ y, K }` back to client

- Client displays values:
  - \( a \) = client secret
  - \( x = g^a \mod p \)
  - \( y = g^b \mod p \)
  - \( K \) = shared secret key



### Summary

This project demonstrates:

- Using WebAssembly for heavy mathematical operations
- JavaScript + WASM integration
- Client–Server cryptographic communication for Diffie–Hellman secure key generation

---

📎 Reference UI & Link :  
[Reference UI Document](https://drive.google.com/file/d/1HM7LyQzQA7kcNplRCubC5giV4j-HByQn/view)


