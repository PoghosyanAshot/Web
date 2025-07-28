class Product {
    constructor(name, price, description) {
        if (new.target === Product) {
            throw new Error("Abstract class");
        }

        this.name = name;
        this.price = price;
        this.description = description;
    }

    get_detailes() {
        if (this.constructor === Product) {
            throw new Error("Abstract method");
        }

        console.log(this.name);
        console.log(this.price);
        console.log(this.description);
    }
}

class ElectronicProduct extends Product {
    constructor(name, price, description, warrantyPeriod, brand) {
        super(name, price, description);
        
        this.warrantyPeriod = warrantyPeriod;
        this.brand = brand;
    }

    get_detailes() {
        super.get_detailes();
        
        console.log(this.warrantyPeriod);
        console.log(this.brand);
    }
}

class ClothingProduct extends Product {
    constructor(name, price, description, size, material, gender) {
        super(name, price, description);

        this.size = size;
        this.material = material;
        this.gender = gender;
    }    
}
