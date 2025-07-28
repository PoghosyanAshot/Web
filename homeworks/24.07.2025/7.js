const obj = {
    arr: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
    onlyOdd: false,

    *[Symbol.iterator]() {
        for (const item of this.arr) {
            if (this.onlyOdd && item & 1) {
                continue;
            }

            yield item;            
        }
    }
}

for (const item of obj) {
    console.log(item);
}

obj.onlyOdd = true;

for (const item of obj) {
    console.log(item);
}
