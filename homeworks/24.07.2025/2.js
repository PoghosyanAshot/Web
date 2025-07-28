const sym1 = Symbol.for("sym");
const sym2 = Symbol.for("sym");

console.log(sym1 === sym2);

console.log(Symbol.keyFor(sym1));

const sym3 = Symbol("sym");
const sym4 = Symbol("sym");

console.log(sym3 === sym4);

