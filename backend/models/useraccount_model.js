const db = require('../database');

const useraccount = {

    getAllUserAccounts(callback){
        return db.query("SELECT * FROM user_account", callback);
    },

    getOneUserAccount(id, callback){
        return db.query("SELECT * FROM user_account WHERE id_useraccount = ?", [id], callback);
    },

    // addUserAccount(){},
    // updateUserAccount(){},
    // deleteUserAccount(){}
}

module.exports = useraccount;