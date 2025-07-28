class Shape {
    constructor() {
        if (new.target === Shape) {
            throw new Error("Cannot instantiate");
        }
    }   

    get_area() {
        throw new Error("Cannot called");
    }
}

class Rectangle extends Shape {
    constructor(width, height) {
        super();
        this.width = width;
        this.height = height;
    }
    
    get_area() {
        console.log(this.width * this.height);
    }
}

class Circle extends Shape {
    constructor(radius) {
        super();
        this.radius = radius;
    }
    
    get_area() {
        console.log(Math.PI * this.radius);
    }
}

const o = new Circle(20);


o.get_area();
console.log(Math.PI);
