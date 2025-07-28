const obj = {
    inner_array: ["hello", "world"],

    [Symbol.iterator]() {
        const items = this.inner_array;
        let index = items.length - 1;
        
        return {
            next() {
                if (index >= 0) {
                    return {
                        value: items[index--],
                        done: false,
                    }
                }

                return {
                    value: undefined,
                    done: true,
                }
            }
        }
    }
}

for (const item of obj) {
    console.log(item);
}

console.log([...obj]);
