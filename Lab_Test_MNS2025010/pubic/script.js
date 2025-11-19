// Function to check if p is prime
function isPrime(n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 === 0 || n % 3 === 0) return false;
    for (let i = 5; i * i <= n; i += 6) {
        if (n % i === 0 || n % (i + 2) === 0) return false;
    }
    return true;
}

// Modular exponentiation function
function modExp(a, b, p) {
    let result = 1;
    a = a % p;
    while (b > 0) {
        if (b % 2 === 1) {
            result = (result * a) % p;
        }
        b = Math.floor(b / 2);
        a = (a * a) % p;
    }
    return result;
}

function calculate() {
    const a = parseInt(document.getElementById("a").value);
    const b = parseInt(document.getElementById("b").value);
    const p = parseInt(document.getElementById("p").value);

    if (!isPrime(p)) {
        document.getElementById("result").innerText = "Error: p must be a prime number!";
        return;
    }

    const y = modExp(a, b, p);
    document.getElementById("result").innerText = `y = ${y}`;
}
