let enum_colors = {
    RED: Symbol("red"),
    BLUE: Symbol("blue"),
    GREEN: Symbol("green"),
}

function get_color_name(symbol) {
    if (typeof symbol != "symbol") {
        throw new Error(`${symbol} is not a symbol`);
    }

    for (const key of Object.keys(enum_colors)) {
        if (enum_colors[key] === symbol) {
            return key;
        }
    }

    return null;
}

console.log(get_color_name(enum_colors.RED));
