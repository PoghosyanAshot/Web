let a = 10;
let b = 20;

function sum(a, b) {
    if (typeof a !== "number" || typeof b !== "number") {
        return "Can not do instruction!";
    }

    return a + b;
}

console.log(sum(a, b));
