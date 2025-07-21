let str = "hello world";

function reverse(str) {
    let res = "";
    
    for (let i = str.length - 1; i >= 0; --i) {
        res += str[i];
    }

    return res;
}

console.log(reverse(str));

console.log(str.split("").reverse().join(""));
