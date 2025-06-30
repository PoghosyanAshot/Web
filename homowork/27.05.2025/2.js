let str = "Hello world";

function toApper(str) {
    let res = "";

    for (let i = 0; i < str.length; ++i) {
        let char = str.charCodeAt(i);

        char = char >= 97 && char <= 122 ? char - 32 : char;

        res += String.fromCharCode(char);
    }

    return res;
}

console.log(toApper(str));
