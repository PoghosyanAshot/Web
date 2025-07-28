class Mlass {
    static [Symbol.hasInstance](obj) {
        return obj && obj.type === "Mlass";
    }
}

const obj = {
    type: "Mlass",
};

const obj2 = {
    type: "not Mlass",
};

console.log(obj instanceof Mlass);
console.log(obj2 instanceof Mlass);
