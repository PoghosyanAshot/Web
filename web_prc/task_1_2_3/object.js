function create_bank_accaount(account_holder, account_number) {
    return {
        // properties
        
        account_holder: account_holder,
        account_number: account_number,
        balance: 0,

        // methods

        deposit: function (ammount) {
            if (ammount < 0) {
                console.log("Can not do opperation");
                return;
            }

            this.balance += ammount;
        },

        withdrow: function (ammount) {
            if (this.balance < ammount) {
                console.log("Can not do opperation");
                return;
            }

            this.balance -= ammount;
        },

        get_balance: function () {
           console.log(this.balance);
        }
    }
}

function create_bank_class() {
    return {
        // properties
        
        all_users: [],

        // methods
        
        add_account: function (account) {
            if (account) {
                this.all_users.push(account);
            }
        },

        find_account: function (account_number) {
            for (let i = 0; i < this.all_users.length; ++i) {
                if (this.all_users[i]["account_number"] === account_number) {
                    return this.all_users[i];
                }
            }

            console.log("Can not find user");        
        },

        get_total_balance: function () {
            let sum_balance = 0;
            
            for (let i = 0; i < this.all_users.length; ++i) {
                sum_balance += this.all_users[i]["balance"];     
            }

            return sum_balance;
        }
    }
}
