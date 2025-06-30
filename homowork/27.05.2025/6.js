let src = "Learning JavaScript";
let search = "Java";

function strstr(src, search) {
    for (let i = 0; i < src.length - search.length; ++i) {
        let match = true;
        
        for (let j = 0; j < search.length; ++j) {
            if (src[i + j] !== search[j]) {
                match = false;
                break;
            }
        }

        if (match) return true;;
    }

    return false;
}

console.log(strstr(src, search));
