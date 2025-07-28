const sym1 = Symbol("sym");
const sym2 = Symbol("sym");

console.log(sym1 === sym2);

const obj = {};

obj[sym1] = "first symbol";
obj[sym2] = "second symbol";

//console.log(obj);

for (const key in obj) {
    console.log(key);
}

console.log(Object.keys(obj));

console.log(Object.getOwnPropertySymbols(obj));
