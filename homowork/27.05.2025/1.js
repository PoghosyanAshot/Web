function len(str) {
    let count = 0;

    while (str[count++]);

    return --count;
}

let str = "Hello world";

console.log(len(str));
