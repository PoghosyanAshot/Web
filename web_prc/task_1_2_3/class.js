class Bank_account {
    #account_holder;
    #account_number;
    #balance = 0;
    
    constructor(account_holder, account_number) {
        this.#account_holder = account_holder;
        this.#account_number = account_number;
    }

    deposit(ammount) {
        if (ammount < 0) {
            console.log("Can not do opperation");
            return;
        }

        this.#balance += ammount;
    }   

    withdrow(ammount) {
        if (this.#balance < ammount) {
            console.log("Can not do opperation");
            return;
        }

        this.#balance -= ammount;
    }

    get_balance() {
        console.log(this.#balance);
    }

    get_account_number() {
        return this.#account_number;
    }
}

class Bank {
    all_users = [];

    add_user(account) {
        if (account) {
            this.all_users.push(account);
        }
    }

    find_user(account_number) {
        for (let i = 0; i < this.all_users.length; ++i) {
            if (this.all_users[i].get_account_number() === account_number) {
                return this.all_users[i];   
            }
        }

        console.log("Can not find user");
    }

    total_balance() {
        let sum_balance = 0;

        for (let i = 0; i < this.all_users.length; ++i) {
            sum_balance += this.all_users[i]["balance"];
        }

        return balance;
    }
}

let usr1 = new Bank_account("James", 123456789);

usr1.deposit(1000);
usr1.get_balance();
usr1.withdrow(500);
usr1.get_balance();

let ameria = new Bank();
ameria.add_user(usr1);

console.log(ameria.find_user(123456789));
