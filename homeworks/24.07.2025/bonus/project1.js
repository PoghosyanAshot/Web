class Money {
    constructor(amount) {
        this.amount = amount;
        this.currency = "USD";
    }

    [Symbol.toPrimitive](hint) {
        switch (hint) {
            case "number":
                return this.amount;

            case "string":
                return new Intl.NumberFormat("en-US", {
                    style: "currency",
                    currency: this.currency,
                }).format(this.amount);
            

            default:
                return this.amount;
        }
    }
}

let obj = new Money(129.99);

console.log(obj + 10);

console.log(`The amount is ${obj}`);
