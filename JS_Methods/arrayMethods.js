// JS Array basic methods

// method toString

Array.prototype.myToString = function() {
    let res = "";

    for (let i = 0; i < this.length; ++i) {
        res += this[i];
        if (i < this.length - 1) {
            res += ",";
        }
    }

    return res;
}

// method at

Array.prototype.myAt = function (index) {
    if (index >= this.length) {
        return undefined;
    }

    if (index === undefined) {
        return this[0];
    }

    return this[index];
}

// method join

Array.prototype.myJoin = function (delimetr) {
    if (delimetr === undefined) {
        delimetr = ",";
    }

    let res = "";

    for (let i = 0; i < this.length; ++i) {
        res += this[i];

        if (i < this.length - 1) {
            res += delimetr;
        }
    }

    return res;
}

// method pop

Array.prototype.myPop = function () {
    let returnValue = this[this.length - 1];

    this[this.length - 1] = undefined;
    this.length -= 1;

    return res;
}

// method push

Array.prototype.myPush = function () {
    for (let i = 0; i < arguments.length; ++i) {
        this[this.length] = arguments[i];
    }

    return this.length;
}

// method shift

Array.prototype.myShift = function () {
    let returnValue = this[0];

    for (let i = 0;  i < this.length - 1;  ++i) {
        let tmp = this[i];
        this[i] = this[i + 1];
        this[i + 1] = tmp;
    }

    this[this.length - 1] = undefined;
    this.length -= 1;

    return returnValue;
}

// method unshift

Array.prototype.myUnshift = function () {
    for (let i = this.length - 1; i >= 0; --i) {
        this[i + arguments.length] = this[i];
    }

    for (let i = 0; i < arguments.length; ++i) {
        this[i] = arguments[i];
    }

    return this.length;
}

// method delete

Array.prototype.myDelete = function (index) {
    this[index] = undefined;

    return;
}

// method concat

Array.prototype.myConcat = function () {
    let res = [];
    let index = 0;

    for (let i = 0; i < this.length; ++i) {
        res[index++] = this[i];
    }

    for (let i = 0; i < arguments.length; ++i) {
        if (Array.isArray(arguments[i])) {
            for (let j = 0; j < arguments[i].length; ++j) {
                res[index++] = arguments[i][j];            
            }
        } else {
            res[index++] = arguments[i];
        }
    }

    return res;
}

// method copyWithin

Array.prototype.myCopyWithin = function (target, start, end) {
    if (arguments.length === 0 || arguments.length === 1) {
        return this;
    }
    
    target = target >> 0;
    start = start >> 0;
    end = end === undefined ? this.length : end >> 0;

    target = target < 0 ? Math.max(this.length + target, 0) : Math.min(target, this.length);
    start = start < 0 ? Math.max(this.length + start, 0) : Math.min(start, this.length);
    end = end < 0 ? Math.max(this.length + end, 0) : Math.min(end, this.length);

    let count = Math.min(end - start, this.length - target);
    let direction = 1;

    if (start < target && target < start + count) {
        direction = -1;
        start += count - 1;
        target += count -1;
    }

    while (count-- > 0) {
        if (start in this) {
            this[target] = this[start];
        } else {
            delete this[target];
        }

        start += direction;
        target += direction;
    }

    return this;
}

// method flat

Array.prototype.myFlat = function (depth) {
    if (depth === undefined) {
        depth = 1;
    }

    let res = [];

    for (let i = 0; i < this.length; ++i) {
        if (!(i in this)) {
            continue;
        }

        const element = this[i];
        
        if (Array.isArray(element) && depth > 0) {
            res.push(...Array.prototype.myFlat.call(element, depth - 1));
        } else {
            res.push(element);
        }
    }

    return res;
}

// method slice

Array.prototype.mySlice = function (start, end) {
    if (start === undefined) {
        start = 0;
    }

    if (start < 0) {
        start = Math.max(this.length + start, 0);
    }

    if (start >= this.length) {
        return [];
    }

    if (end === undefined || end >= this.length) {
        end = this.length;
    }

    if (end < 0) {
        end = Math.max(this.length + end, 0);
    }

    let res = [];

    for (let i = start; i < end; ++i) {
        res.push(this[i]);
    }

    return res;
}

// method splice

Array.prototype.mySplice = function (start, deleteCount, ...itemN) {
    if (arguments.length === 0) {
        return [];
    }

    if (start < 0) {
        start = Math.max(start + this.length, 0);
    }

    if (typeof start !== "number") {
        start = 0;
    }
    
    if (deleteCount === undefined || deleteCount > this.length) {
        deleteCount = this.length - start;
    }

    if (typeof deleteCount !== "number") {
        deleteCount = 0;
    }

    if (deleteCount < 0) {
        deleteCount = 0;
    }

    let res = [];
    let count = deleteCount;
    
    for (let i = start; i < this.length && count; ++i, --count) {
        res.push(this[i]);
    }


    for (let i = start + deleteCount; i < this.length; ++i) {
        this[i - deleteCount] = this[i];
    }
    
    this.length -= deleteCount;

    for (let i = this.length - 1; i >= start; --i) {
        this[i + itemN.length] = this[i];
    }

    for (let i = 0; i < itemN.length; ++i) {
        this[start++] = itemN[i];
    }

    return res;
}

// method toSpliced

Array.prototype.myToSpliced = function (start, skipCount, ...itemN) {
    let res = []
    
    if (arguments.length === 0) {
        for (let i = 0; i < this.length; ++i) {
            res.push(this[i]);
        }

        return res;
    }
    
    if (skipCount === undefined) {
        return [];
    }

    if (typeof start !== "number") {
        start = 0;
    }

    if (start < 0) {
        start = Math.max(this.length + start, 0);
    }

    if (typeof skipCount !== "number") {
        skipCount = 0;
    }

    for (let i = 0; i < this.length; ++i) {
        if (i >= start && skipCount) {
            --skipCount;
            continue;
        }

        res.push(this[i]);
    }

    for (let i = res.length - 1; i < res.length && i >= start; --i) {
        res[i + itemN.length] = res[i];
    }

    for (let i = 0; i < itemN.length; ++i) {
        res[start++] = itemN[i];
    }

    return res;
}

// JS Array search methods

// method indexOf

Array.prototype.myIndexOf = function (searchElement, fromIndex) {
    if (fromIndex === undefined) {
        fromIndex = 0;
    }

    if (fromIndex < 0) {
        fromIndex = Math.max(this.length + fromIndex, 0);
    }

    if (fromIndex >= this.length) {
        return -1;
    }

    for (let i = fromIndex; i < this.length; ++i) {
        if (this[i] === searchElement) {
            return i;
        }
    }

    return -1;
}

// method lastIndexOf

Array.prototype.myLastIndexOf = function (searchElement, fromIndex) {
    if (fromIndex === undefined || fromIndex >= this.length) {
        fromIndex = this.length - 1;
    }

    if (fromIndex < 0) {
        fromIndex = Math.max(fromIndex + this.length, 0);
    }

    for (let i = fromIndex; i >= 0; --i) {
        if (this[i] === searchElement) {
            return i;
        }
    }

    return -1;
}

// method includes

Array.prototype.myIncludes = function (searchElement, fromIndex) {
    if (fromIndex === undefined) {
        fromIndex = 0;
    }

    if (fromIndex >= this.length) {
        return false;
    }

    if (fromIndex < 0) {
        fromIndex = Math.max(fromIndex + this.length, 0);
    }

    for (let i = fromIndex; i < this.length; ++i) {
        if (isNaN(searchElement) && isNaN(this[i])) {
            return true;
        }
        
        if (this[i] === searchElement) {
            return true;
        }
    }

    return false;
}

// method find

Array.prototype.myFind = function (callback) {
    for (let i = 0; i < this.length; ++i) {
        if (callback(this[i])) {
            return this[i];
        }
    }

    return undefined;
}

// method findIndex

Array.prototype.myFindIndex = function (callback) {
    for (let i = 0; i < this.length; ++i) {
        if (callback(this[i])) {
            return i;
        }
    }

    return -1;
}

// method findLast

Array.prototype.myFindLast = function (callback) {
    for (let i = this.length - 1; i >= 0; --i) {
        if (callback(this[i])) {
            return this[i];
        }
    }

    return undefined;
}

// method findLastIndex

Array.prototype.myFindLastIndex = function (callback) {
    for (let i = this.length - 1; i >= 0; --i) {
        if (callback(this[i])) {
            return i;
        }
    }

    return -1;
}

// JS Array iteration methods

// method forEach

Array.prototype.myForEach = function (callback) {
    for (let i = 0; i < this.length; ++i) {
        if (i in this) {
            callback(this[i]);
        }
    }

    return undefined;
}

// method map

Array.prototype.myMap = function (callback) {
    let res = [];

    for (let i = 0; i < this.length; ++i) {
        if (i in this) {
            res.push(callback(this[i]));
        }
    }

    return res;
}

// method flatMap

Array.prototype.myFlatMap = function (callback) {
    let res = [];

    for (let i = 0; i < this.length; ++i) {
        if (i in this) {
            const element = callback(this[i]);
            if (Array.isArray(element)) {
                res.push(...element);
                continue;
            }

            res.push(element);
        }
    }

    return res;
}

// method filter

Array.prototype.myFilter = function (callback) {
    let res = [];

    for (let i = 0; i < this.length; ++i) {
        if (i in this) {
            if (callback(this[i])) {
                res.push(this[i]);
            }
        }
    }

    return res;
}

// method reduce

Array.prototype.myReduce = function (callback, initalValue) {
    let acamulator = initalValue;
    let stIndex = 0;

    if (acamulator === undefined) {
        if (this.length === 0) {
            throw new Error("Error");
        }

        acamulator = this[0];
        stIndex = 1;
    }
    
    for (let i = stIndex; i < this.length; ++i) {
        acamulator = callback(acamulator, this[i]);
    }

    return acamulator;
}

// method reduceRight

Array.prototype.myReduceRight = function (callback, initialValue) {
    let acamulator = initialValue;
    let stIndex = this.length - 1;

    if (acamulator === undefined) {
        if (this.length === 0) {
            throw new Error("Error");
        }
        
        acamulator = this[this.length - 1];
        stIndex = this.length - 2;
    }

    for (let i = stIndex; i >= 0; --i) {
        acamulator = callback(acamulator, this[i]);
    }

    return acamulator;
}

// method every

Array.prototype.myEvery = function (callback) {
    for (let i = 0; i < this.length; ++i) {
        if (i in this) {
            if (!callback(this[i])) {
                return false;
            }
        }
    }

    return true;
}

// method some

Array.prototype.mySome = function (callback) {
    for (let i = 0; i < this.length; ++i) {
        if (callback(this[i])) {
            return true;
        }
    }

    return false;
}

// method from

Array.myFrom = function (arrayLike, mapfn, thisArg) {
    let res = [];
    
    for (let i = 0; i < arrayLike.length; ++i) {
        if (typeof mapfn === "function") {
            res.push(mapfn.call(thisArg, arrayLike[i]));
            continue;
        }

        res.push(arrayLike[i]);
    }

    return res;
}

// method keys

Array.prototype.myKeys = function () {
    let i = 0;
    const arr = this;

    return {
        next: function () {
            if (i < arr.length) {
                return {value: i++, done: false};
            }
            
            return {value: undefined, done: true};
        },

        [Symbol.iterator]: function () {return this}
    };
}

// method entries

Array.prototype.myEntries = function () {
    let i = 0;
    const arr = this;

    return {
        next: function () {
            if (i < arr.length) {
                return {value: [i, arr[i++]], done: false};
            }

            return {value: undefined, done: true};
        },

        [Symbol.iterator]: function () {return this}
    };
}

// method with

Array.prototype.myWith = function (index, value) {
    let res = [];
    
    for (let i = 0; i < this.length; ++i) {
        if (i === index) {
            res.push(value);
            continue;
        }

        res.push(this[i]);
    }

    return res;
}
