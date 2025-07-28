const arr = [1, 2, 3];

const obj = {
    0: "hello",
    1: "world",
    length: 2,
}

console.log(arr.concat(obj));

obj[Symbol.isConcatSpreadable] = true;

console.log(arr.concat(obj));

const arr2 = [4, 5, 6];

arr2[Symbol.isConcatSpreadable] = false;

console.log(arr.concat(arr2));

