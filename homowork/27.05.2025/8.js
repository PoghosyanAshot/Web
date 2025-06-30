let arr = [50, 75, 100];

function sumOfElementsInArray(arr) {
    let sum = arr[0];

    for (let i = 1; i < arr.length; ++i) {
        sum += arr[i];
    }

    return sum;
}

console.log(sumOfElementsInArray(arr));
