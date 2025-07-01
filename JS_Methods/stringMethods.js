// JS String basic methods
// method charAt

String.prototype.myCharAt = function (index = 0) {
    if (index < 0 || index >= this.length) {
        return "";
    }

    if (typeof index !== "number") {
        index = 0;
    }
    
    return this[index];
}

// method slice

String.prototype.mySlice = function (beginIndex = 0, endIndex = this.length) {
    if (beginIndex >= this.length) {
        return "";
    }

    if (typeof endIndex !== "number") {
        return "";
    }

    if (typeof beginIndex !== "number") {
        beginIndex = 0;
    }

    if (beginIndex < 0) {
        beginIndex = Math.max(beginIndex + this.length, 0);
    }

    if (endIndex > this.length) {
        endIndex = this.length;
    }

    if (endIndex < 0) {
        endIndex = Math.max(endIndex + this.length, 0);
    }

    let res = "";

    for (let i = beginIndex; i < endIndex; ++i) {
        res += this[i];
    }

    return res;
}

// method substring

String.prototype.mySubstring = function (indexA = 0, indexB = this.length) {
    if (typeof indexA !== "number" || indexA < 0) {
        indexA = 0;
    }

    if (typeof indexB !== "number" || indexB < 0) {
        indexB = 0;
    }

    if (indexA === indexB) {
        return "";
    }

    if (indexA > indexB) {
        let tmp = indexA;
        indexA = indexB;
        indexB = tmp;
    }

    if (indexA >= this.length) {
        return "";
    }

    if (indexB > this.length) {
        indexB = this.length;   
    }

    let res = "";

    for (let i = indexA; i < indexB; ++i) {
        res += this[i];
    }

    return res;
}

// method toUpperCase

String.prototype.myToUpperCase = function () {
    let res = "";

    for (let i = 0; i < this.length; ++i) {
        let char = str.charCodeAt(i);

        res += char >= 97 && char <= 122 ? String.fromCharCode(char - 32) : String.fromCharCode(char);
    }

    return res;
}

// method toLowerCase

String.prototype.myToLowerCase = function () {
    let res = "";

    for (let i = 0; i < this.length; ++i) {
        let char = str.charCodeAt(i);

        res += char >= 65 && char <= 90 ? String.fromCharCode(char + 32) : String.fromCharCode(char);
    }

    return res;
}

// method concat

String.prototype.myConcat = function (...strings) {
    let res = "";

    for (let i = 0; i < this.length; ++i) {
        res += this[i];
    }
    
    for (let i = 0; i < strings.length; ++i) {
        res += strings[i];
    }

    return res;
}

// method trim

String.prototype.myTrim = function () {
    let start = 0;
    let end = this.length - 1;
    let res = "";

    while (this[start] === " " || this[start] === '\t') ++start;

    while (this[end] === " " || this[end] === '\t') --end;

    for (let i = start; i <= end; ++i) {
        res += this[i];
    }

    return res;
}

// method trimRight

String.prototype.myTrimRight = function () {
    let end = this.length - 1;
    let res = "";

    while (this[end] === " " || this[end] === '\t') --end;

    for (let i = 0; i <= end; ++i) {
        res += this[i];
    }

    return res;
}

// method padStart

String.prototype.myPadStart = function (targetLength, padStart = ' ') {
    let res = "";
    
    if (!targetLength || typeof targetLength !== "number" || targetLength < 0) {
        for (let i = 0; i < this.length; ++i) {
            res += this[i];
        }

        return res;
    }

    let flag = 0;

    for (let i = 0; i < targetLength - this.length; ++i) {
        for (let j = 0; j < padStart.length; ++j) {
            if (res.length >= targetLength - this.length) {
                flag = 1;
                break;
            }

            res += padStart[j];
        }

        if (flag) {
            break;
        }
    }

    for (let i = 0; i < this.length; ++i) {
        res += this[i];
    }
    return res;
}

// method padEnd

String.prototype.myPadEnd = function (targetLength, padStart = ' ') {
    let res = "";
    
    if (!targetLength || targetLength < 0 || typeof targetLength !== "number") {
        for (let i = 0; i < this.length; ++i) {
            res += this[i];
        }

        return res;
    }

    for (let i = 0; i < targetLength; ++i) {
        if (i < this.length) {
            res += this[i];
            continue;
        }

        res += padStart;
    }

    return res;
}

// method repeat

String.prototype.myRepeat = function (count) {
    if (count === Infinity || count < 0) {
        throw new Error("Invalid count");
    }

    if (count === 0) {
        return ""
    }
    
    count = count >> 0;

    let res = "";
    
    for (let i = 0; i < count; ++i) {
        res += this;    
    }

    return res;
}

// method replaceAll

String.prototype.myReplaceAll = function (pattern, replacement) {
    let res = "";
    
    if (arguments.length === 0 || typeof pattern !== "string") {
        for (let i = 0; i < this.length; ++i) {
            res += this[i];
        }

        return res;
    }

    for (let i = 0; i < this.length; ++i) {
        let j = 0;
        
        for (j; j < this.length; ++j) {
            if (this[i + j] !== pattern[j]) {
                break;
            }
        }

        if (j === pattern.length) {
            for (let k = 0; k < replacement.length; ++k) {
                res += replacement[k];
            }

            i += pattern.length - 1;
            continue;
        }


        res += this[i];
    }

    return res;
}

// method split

String.prototype.mySplit = function (separator, limit) {
    let res = [];
    let partString = "";
    
    if (arguments.length == 0) {
        res.push(this);
        return res;
    }

    if (limit < 0 || limit === undefined) {
        limit = this.length;
    }

    if (typeof limit !== "number") {
        return res;
    }

    for (let i = 0; i < this.length; ++i) {
        if (this[i] !== separator) {
            partString += this[i];
            continue;
        }

        if (limit-- > 0) {
            res.push(partString);
        }

        partString = "";
    }

    if (limit-- > 0) {
        res.push(partString);
    }

    return res;
}

// JS String search methods
// method indexOf

String.prototype.myIndexOf = function (searchValue, fromIndex = 0) {
    if (searchValue === "") {
        return fromIndex > this.length ? this.length : fromIndex;
    }

    if (fromIndex >= this.length) {
        return -1;
    }

    if (fromIndex < 0) {
        fromIndex = 0;
    }
    
    if (searchValue == undefined) {
        searchValue = "undefined";
    }

    if (Array.isArray(searchValue)) {
        return 0;
    }

    for (let i = fromIndex; i <= this.length - searchValue.length; ++i) {
        const partString = this.slice(i, i + searchValue.length);
        
        if (partString === searchValue) {
            return i;
        }
    }

    return -1;
}

// method lastIndexOf

String.prototype.myLastIndexOf = function (searchValue, fromIndex = this.length - 1) {
    if (searchValue === undefined) {
        searchValue = "undefined";
    }

    if (Array.isArray(searchValue) || searchValue === "") {
        return this.length;
    }

    if (typeof searchValue !== "string") {
        return -1;
    }

    if (fromIndex <= 0) {
        return -1;
    }

    for (let i = fromIndex; i >= 0; --i) {
        const partString = this.slice(i, i + searchValue.length);
        
        if (partString === searchValue) {
            return i;
        }
    }

    return -1;
}

// method search 

String.prototype.mySearch = function (regexp) {
    regexp = regexp instanceof RegExp ? regexp : new RegExp(regexp);

    let res = regexp.exec(this);

    return res === null ? -1 : res.index;
}

// method includes

String.prototype.myIncludes = function (searchString, position = 0) {
    if (searchString === undefined) {
        searchString = "undefined";
    }

    if (position >= this.length) {
        return false;
    }

    if (position < 0) {
        position = 0;
    }

    for (let i = position; i <= this.length - searchString.length; ++i) {
        let j = 0;

        for (j; j < searchString.length && this[i + j] === searchString[j];  ++j);

        if (!searchString[j]) {
            return true;
        }
    }

    return false;
}

// method startsWith

String.prototype. myStartsWith = function (searchString, position = 0) {
    if (searchString === undefined) {
        searchString = "undefined";
    }

    if (searchString === "") {
        return true;
    }

    if (Array.isArray(searchString)) {
        return true;
    }

    if (typeof searchString !== "string") {
        return false;
    }

    if (position < 0) {
        position = 0;
    }

    if (position >= this.length) {
        return false;
    }

    for (let i = position; i <= this.length - searchString.length; ++i) {
        let j = 0;

        for (j; j < searchString.length && this[i + j] === searchString[j]; ++j);

        if (!searchString[j]) {
            return true;
        }

        return false;
    }    
}

// method endsWith

String.prototype.myEndsWith = function (searchString, length = this.length) {
    if (searchString === undefined) {
        searchString = "undefined";
    }

    if (Array.isArray(searchString)) {
        return true;
    }

    if (typeof searchString !== "string") {
        return false;
    }

    if (length < 0 || length > this.length) {
        return false;
    }

    for (let i = length - searchString.length; i <= length; ++i) {
        j = 0;

        for (j; j < searchString.length && this[i + j] === searchString[j]; ++j);

        if (!searchString[j]) {
            return true;
        }

        return false;
    }

}
