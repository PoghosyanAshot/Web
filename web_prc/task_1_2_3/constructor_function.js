function Create_bank_accaount(account_holder, account_number) {
    // properties

    this.account_holder = account_holder;
    this.account_number = account_number;
    this.balance = 0;

    // methods
    
    this.deposit = function (ammount) {
        if (ammount < 0) {
            console.log("Can not do opperation");
            return;
        }

        this.balance += ammount;
    }

    this.withdrow = function (ammount) {
        if (this.balance < ammount) {
            console.log("Can not do opperation");
            return;
        }

        this.balance -= ammount;
    }

    this.get_balance = function () {
        console.log(this.balance);
    }    
}

function Create_bank(account) {
    this.all_users = [];

    this.add_user = function (account) {
        if (account) {
            this.all_users.push(account);
        }
    }

    this.find_account = function (account_number) {
        for (let i = 0; i < this.all_users.length; ++i) {
            if (this.all_users[i]["account_number"] === account_number) {
                return this.all_users[i];
            }
        }

        console.log("Can not find user");
    }

    this.get_total_balance = function () {
        let total_balance = 0;
        
        for (let i = 0; i < this.all_users.length; ++i) {
            total_balance += this.all_users[i]["balance"];
        }

        return total_balance;
    }
}
