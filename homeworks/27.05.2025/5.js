let array1 = [1, 2];
let array2 = [3, 4];

function merge(array1, array2) {
    let res = [];

    for (let i = 0; i < array1.length + array2.length; ++i) {
        if (i < array1.length) {
            res.push(array1[i]);
            continue;
        }

        res.push(array2[i - array1.length]);
    }
    
    return res;
}

console.log(merge(array1, array2));
