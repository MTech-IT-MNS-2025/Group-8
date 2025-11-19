// pages/api/myprog.js
// Minimal, robust handler — DOES NOT LOAD WASM ON THE SERVER.
// Uses a fast JS modular exponentiation so API never returns HTML 500 pages.

export default async function handler(req, res) {
    try {
        if (req.method !== "POST") {
            return res.status(405).json({ error: "Method not allowed" });
        }

        const { g, p, x } = req.body;
        if (g === undefined || p === undefined || x === undefined) {
            return res.status(400).json({ error: "Missing g, p or x in request body" });
        }

        const G = Number(g);
        const P = Number(p);
        const X = Number(x);

        if (!Number.isInteger(G) || !Number.isInteger(P) || !Number.isInteger(X)) {
            return res.status(400).json({ error: "g, p, x must be integers" });
        }

        if (P <= 2) {
            return res.status(400).json({ error: "p must be > 2" });
        }

        // fast modular exponentiation (numbers; safe for small p used in lab)
        function modPow(base, exponent, mod) {
            base = ((base % mod) + mod) % mod;
            let result = 1;
            while (exponent > 0) {
                if (exponent & 1) result = (result * base) % mod;
                base = (base * base) % mod;
                exponent = exponent >> 1;
            }
            return result;
        }

        // simple server private b in [2..p-1]
        const b = Math.floor(Math.random() * (P - 2)) + 2;

        // compute y = g^b mod p and K = x^b mod p (JS)
        const y = modPow(G, b, P);
        const K = modPow(X, b, P);

        // return plain numbers (JSON)
        return res.status(200).json({ K: Number(K), y: Number(y) });

    } catch (err) {
        console.error("API handler unexpected error:", err);
        return res.status(500).json({ error: "Internal server error", details: String(err) });
    }
}
