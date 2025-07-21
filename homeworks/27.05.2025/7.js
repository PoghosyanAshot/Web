let arr = [3, 6, 9, 12];
let target = 9;
function searchTarget(arr, target, start, end) {
 
    let mid = Math.floor(start + (end - start) / 2);
    //console.log(mid)
    if (start > end) return -1;

    if (arr[mid] === target) return mid;

    if (arr[mid] < target) return searchTarget(arr, target, mid + 1, end);

    if (arr[mid] > target) return searchTarget(arr, target, start, mid - 1);
    
}

console.log(searchTarget(arr, target, 0, arr.length - 1));
