"use client";
import React, { useEffect, useState } from "react";
import "./home.css"

export default function Rc4Page() {
    const [encryptFunc, setEncryptFunc] = useState(null);
    const [decryptFunc, setDecryptFunc] = useState(null);

    const [key, setKey] = useState("");
    const [text, setText] = useState("");
    const [result, setResult] = useState("");

    useEffect(() => {
        (async () => {
            try {
                const modImport = await import(/* webpackIgnore: true */ "/rc4.js");
                const createModule = modImport.default || modImport;
                const Module = await createModule();
                setEncryptFunc(() => Module.cwrap("encrypt", "string", ["string", "string"]));
                setDecryptFunc(() => Module.cwrap("decrypt", "string", ["string", "string"]));
            } catch (err) {
                console.error("Failed to load rc4.js / rc4.wasm", err);
            }
        })();
    }, []);

    const encrypt = () => {
        if (!encryptFunc || !key || !text) return;
        setResult(encryptFunc(text, key));
    };

    const decrypt = () => {
        if (!decryptFunc || !key || !text) return;
        setResult(decryptFunc(text, key));
    };

    return (
        <div >
            <div>
                <h2>RC4 (WASM)</h2>
                <div>
                    <input
                        placeholder="Key"
                        value={key}
                        onChange={(e) => setKey(e.target.value)}

                    />
                </div>
                <div>

                    <textarea
                        placeholder="Plaintext/Ciphertext(hex)"
                        value={text}
                        onChange={(e) => setText(e.target.value)}
                        rows={4}
                        cols={20}
                    />
                </div>
                <div className="button-group">
                    <button onClick={encrypt} disabled={!encryptFunc}>Encrypt</button>
                    <button onClick={decrypt} disabled={!decryptFunc}>Decrypt</button>
                </div>

                <div >
                    <textarea value={result}
                        readOnly
                        placeholder="Your Result"
                        rows={4}
                        cols={20}
                    ></textarea>

                </div>
            </div>
        </div>
    );
}
