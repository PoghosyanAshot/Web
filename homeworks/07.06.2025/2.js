function deep_copy(obj) {
    if (obj === null || typeof obj != "object") {
        return obj;
    }

    const clone = Array.isArray(obj) ? [] : {};

    for (const key in obj) {
        if (Object.prototype.hasOwnProperty.call(obj, key)) {
            clone[key] = deep_copy(obj[key]);
        }
    }

    return clone;
}
