

```markdown
# Lab Test – Diffie-Hellman Key Exchange (Cryptography)
```
## Clone the Repository
```bash
git clone https://github.com/MTech-IT-MNS-2025/Group-8.git
```
Then navigate to your folder:
```bash
cd Group-8/Lab_Test_MNS2025027
```


---

## Platform Used
- macOS (MacBook Air)

## Software / Tools Used
- Node.js (for server-side handling)
- Next.js (for frontend + API routes)
- React (frontend UI)
- Emscripten (to compile C code to WebAssembly)
- WebAssembly (generated `.wasm` file used in browser)

## Commands to Run the Code
1. Install dependencies (since `node_modules` is not uploaded):
   ```bash
   npm install
   ```
2. Start the Next.js development server:
   ```bash
   npm run dev
   ```
   The frontend form will be available at `http://localhost:3000`.

3. Workflow:
   - User enters values of `p` and `g`.
   - Client generates random `a` and computes `x = g^a mod p` using the WebAssembly version of `myProg.c`.
   - Client sends `<g, p, x>` to the server.
   - Server generates random `b`, computes `y = g^b mod p` and `K = x^b mod p` using the same WebAssembly function.
   - Server responds with `<K, y>`.
   - Client displays `<K, y, a>` on the frontend.

## MD5 Digest Command Used During Lab Test
On macOS:
```bash
md5 test.zip
```

---

### Notes
- The `.wasm` and `.js` files generated from `myProg.c` are already included in the `public/` folder.
- **Therefore, anyone cloning the repo does NOT need to recompile the C file.** The project runs directly with the provided `.wasm` and `.js`.
- If recompilation is needed, the original C file (`myProg.c`) is included and can be recompiled using Emscripten:

  ```bash
  emcc myProg.c \
    -sEXPORTED_FUNCTIONS='["_modexp"]' \
    -sEXPORTED_RUNTIME_METHODS='["cwrap"]' \
    -sMODULARIZE=1 \
    -sEXPORT_ES6=1 \
    -o myprog.js
  ```

  *(Replace `modexp` with your actual function name if different.)*

---

## Folder Structure Overview

```
TEST/
├── app/
│   ├── home.css          # Styling for frontend
│   ├── layout.js         # Layout component
│   └── page.js           # Main frontend page
├── pages/
│   └── api/
│       └── myprog.js     # Server-side API handler
├── public/
│   ├── myprog.c          # Original C source file
│   ├── myprog.js         # JS glue code from Emscripten
│   └── myprog.wasm       # Compiled WebAssembly binary
├── .gitignore
├── jsconfig.json
├── next.config.mjs
├── package.json
├── pnpm-lock.yaml
└── README.md             # This file
```

---
