class Assign_objects {
    static serial_number = 1;
    #object_serial_number;

    constructor() {
        this.#object_serial_number = Assign_objects.serial_number++;
    }

    static get_count_of_instances() {
        return Assign_objects.serial_number - 1;
    }

    get_serial_number() {
        return this.#object_serial_number;
    }
}
