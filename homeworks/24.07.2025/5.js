const obj = {
    0: 10,
    1: 20,
    2: 30,

    length: 3,

    [Symbol.iterator]() {
        let index = 0;

        return {
            next() {
                if (index < obj.length) {
                    return {
                        value: obj[index++],
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
