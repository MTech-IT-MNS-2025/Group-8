"use client";

import { useState, useEffect, useRef } from "react";
import "./home.css";

export default function Home() {
    const [cwrapFn, setCwrapFn] = useState(null); // the wrapped function (if available)
    const moduleRef = useRef(null); // keep Module object for fallback
    const [p, setP] = useState("");
    const [g, setG] = useState("");
    const [x, setX] = useState("");
    const [result, setResult] = useState(null); // { K , y , a }

    // simple random generator (numbers only)
    function randomInZp(pNum) {
        const pn = Number(pNum);
        return Math.floor(Math.random() * (pn - 2)) + 2; // [2 .. p-1]
    }

    useEffect(() => {
        (async () => {
            try {
                const modImport = await import(/* webpackIgnore: true */ "/myprog.js");
                const createModule = modImport.default || modImport;
                const Module = await createModule();
                moduleRef.current = Module;
                console.log("MODULE LOADED?", Module);

                // try to create cwrap for the exported function name you expect
                // try without underscore first, fallback to _modexp if needed
                let fn = null;
                try {
                    fn = Module.cwrap("modexp", "number", ["number", "number", "number"]);
                } catch (e) {
                    try {
                        fn = Module.cwrap("_modexp", "number", ["number", "number", "number"]);
                    } catch (ee) {
                        fn = null;
                    }
                }
                setCwrapFn(() => fn);
            } catch (err) {
                console.error("Failed to load myprog.js / wasm", err);
            }
        })();
    }, []);

    const handleCalculate = async () => {
        // guards
        if (!moduleRef.current) {
            alert("WASM module not loaded yet");
            return;
        }
        if (!p || !g) {
            alert("Enter p and g");
            return;
        }

        const P = Number(p);
        const G = Number(g);

        const a = randomInZp(P);

        // Attempt 1: fast path using cwrap (works when module was compiled without WASM_BIGINT)
        if (cwrapFn) {
            try {
                const xVal = cwrapFn(G, a, P);
                setX(xVal);
                await sendToServerAndShow(xVal, a);
                return;
            } catch (err) {
                console.warn("cwrap call failed, will try fallback (BigInt) path:", err);
                // fallthrough to fallback
            }
        }

        // Fallback: call raw Module._modexp with BigInt args (works if wasm was compiled with WASM_BIGINT)
        try {
            const Module = moduleRef.current;
            // prefer _modexp export name (it exists in your build)
            const raw = Module._modexp || Module._modexp || Module["_modexp"] || Module._modexp;
            if (typeof raw === "function") {
                // call with BigInt arguments and convert returned BigInt to Number for small primes
                const xBig = raw(BigInt(G), BigInt(a), BigInt(P));
                // if xBig is a BigInt, convert to Number; otherwise use as-is
                const xVal = typeof xBig === "bigint" ? Number(xBig) : xBig;
                setX(xVal);
                await sendToServerAndShow(xVal, a);
                return;
            } else {
                throw new Error("raw _modexp not found on Module");
            }
        } catch (err) {
            console.error("Both cwrap and fallback BigInt calls failed:", err);
            alert("WASM call failed. See console for details.");
        }
    };

    // helper: send to server and display result
    async function sendToServerAndShow(xVal, a) {
        try {
            const res = await fetch("/api/myprog", {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({
                    g: Number(g),
                    p: Number(p),
                    x: xVal,
                }),
            });
            const data = await res.json(); // expects { K , y }
            setResult({
                a: a,
                y: data.y,
                K: data.K,
            });
        } catch (err) {
            console.error("Server call failed", err);
            alert("Server call failed. See console.");
        }
    }

    return (
        <div className="container">
            <div className="card">
                <h2>Lab-Test</h2>

                <input
                    type="number"
                    value={p}
                    onChange={(e) => setP(e.target.value)}
                    placeholder="Enter p"
                    className="input"
                />

                <input
                    type="number"
                    value={g}
                    onChange={(e) => setG(e.target.value)}
                    placeholder="Enter g"
                    className="input"
                />

                <button onClick={handleCalculate} className="button">
                    Calculate
                </button>

                <div className="output">
                    {result && (
                        <>
                            <p>a (client private): {String(result.a)}</p>
                            <p>y (server public): {String(result.y)}</p>
                            <p>K (shared key): {String(result.K)}</p>
                        </>
                    )}
                </div>
            </div>
        </div>
    );
}
