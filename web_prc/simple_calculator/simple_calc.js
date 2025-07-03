class Calculator {
    #operand_1;
    #operand_2;

    set(operand_1, operand_2) {
        if (typeof operand_1 !== "number" || typeof operand_2 !== "number") {
            throw new Error("Invalid number!");
        }

        this.#operand_1 = operand_1;
        this.#operand_2 = operand_2;
    }

    add() {
        if (this.#operand_1 === undefined) {
            console.log("Can not do operation operand 1 is not initialized");
            return;
        }

        if (this.#operand_2 === undefined) {
            console.log("Can not do operation operand 2 is not initialized");
            return;
        }

        return this.#operand_1 + this.#operand_2;
    }

    sub() {
        if (this.#operand_1 === undefined) {
            console.log("Can not do operation operand 1 is not initialized");
            return;
        }

        if (this.#operand_2 === undefined) {
            console.log("Can not do operation operand 2 is not initialized");
            return;
        }

        return this.#operand_1 - this.#operand_2;
    }

    mul() {
        if (this.#operand_1 === undefined) {
            console.log("Can not do operation operand 1 is not initialized");
            return;
        }

        if (this.#operand_2 === undefined) {
            console.log("Can not do operation operand 2 is not initialized");
            return;
        }

        return this.#operand_1 * this.#operand_2;
    }

    div() {
        if (this.#operand_1 === undefined) {
            console.log("Can not do operation operand 1 is not initialized");
            return;
        }

        if (this.#operand_2 === undefined) {
            console.log("Can not do operation operand 2 is not initialized");
            return;
        }

        if (this.#operand_2 === 0) {
            console.log("Can not do operation operand 2 is zero");   
            return;
        }

        return this.#operand_1 / this.#operand_2;
    }

    modulo() {
        if (this.#operand_1 === undefined) {
            console.log("Can not do operation operand 1 is not initialized");
            return;
        }

        if (this.#operand_2 === undefined) {
            console.log("Can not do operation operand 2 is not initialized");
            return;
        }

        if (this.#operand_2 === 0) {
            console.log("Can not do operation operand 2 is zero");   
            return;
        }

        return this.#operand_1 % this.#operand_2;
    }
}
