let arr = ["hello", 10, 20, 30];

function sumOfNumbersInArray(arr) {
    let sum = 0;

    for (let i = 0; i < arr.length; ++i) {
        if (typeof arr[i] === "number") {
            sum += arr[i];    
        }
    }

    return sum;
}

console.log(sumOfNumbersInArray(arr));
