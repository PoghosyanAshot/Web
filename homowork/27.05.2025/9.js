let src = "Learning JavaScript";
let search = "Java";

function strstr(src, search) {
    let index = 0;

    for (let i = 0; i < src.length; ++i) {
        if (src[i] === search[index]) {
            let tmp = i + 1;
            ++index;

            while (src[tmp] === search[index]) {
                ++tmp;
                ++index;
            }

            if (!search[index]) {
                return true;
            }
        }
    }

    return false;
}

console.log(strstr(src, search));
