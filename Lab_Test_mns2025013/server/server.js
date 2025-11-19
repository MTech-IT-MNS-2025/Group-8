const express = require("express");
const cors = require("cors");
const app = express();
app.use(express.json());
app.use(cors());

const modexp = require("../modexp.js");

let wasmReady = false;
modexp.onRuntimeInitialized = () => { wasmReady = true; };

app.post("/dh", (req, res) => {
    if (!wasmReady) return res.json({error: "WASM loading..."});

    const { g, p, x } = req.body;

    // Step 2: random b
    const b = Math.floor(Math.random() * (p - 2)) + 2;

    // Step 3: y = g^b mod p
    const y = modexp.ccall("modexp", "number",
        ["number", "number", "number"], [g, b, p]);

    // Step 4: K = x^b mod p
    const K = modexp.ccall("modexp", "number",
        ["number", "number", "number"], [x, b, p]);

    res.json({ K, y });
});

app.listen(5000, () => console.log("Server running..."));
