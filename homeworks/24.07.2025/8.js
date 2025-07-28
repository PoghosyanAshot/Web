function range(start, end, step = 1) {
    return {
        *[Symbol.iterator]() {
            if (step > 0) {
                for (let i = start; i < end; i += step) {
                    yield i;
                }
            } else if (step < 0){
                for (let i = start; i > end; i += step) {
                    yield i;
                }
            }
        }
    }
}

for (const i of range(10, 0, -1)) {
    console.log(i);
}
