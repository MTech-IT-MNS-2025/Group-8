import express from "express";
import cors from "cors";
import createModule from "./modexp.js";

const app = express();
app.use(cors());
app.use(express.json());

const Module = await createModule();
const modexp = Module._modexp;

function randZp(p) {
  return Math.floor(Math.random() * (p - 2)) + 2;
}

app.post("/dh", (req, res) => {
  const { g, p, x } = req.body;

  const b = randZp(p);

  const y = modexp(BigInt(g), BigInt(b), BigInt(p));
  const K = modexp(BigInt(x), BigInt(b), BigInt(p));

  res.json({
    y: y.toString(),
    K: K.toString(),
    b
  });
});

app.listen(3000, () =>
  console.log("Server running on http://localhost:3000")
);
