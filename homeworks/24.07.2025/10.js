function* flat(arr) {
    for (const item of arr) {
        if (Array.isArray(item)) {
            yield* flat(item);
        } else {
            yield item;
        }
    }
}

const arr = [1, [2, [3, 4], 5], 6];

for (const item of flat(arr)) {
    console.log(item);
}
