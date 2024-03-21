const db = require('../database');

// bankaccount JS object for queries in database table bank_account

const bankaccount = {

    getAllAccounts(callback){
        return db.query("SELECT * FROM bank_account", callback);
    },

    getOneAccount(id, callback){
        return db.query("SELECT * FROM bank_account WHERE id_account = ?", [id], callback);
    },

    addAccount(newAccount, callback){
        return db.query("INSERT INTO bank_account (id_account, balance, credit_limit) VALUES (?, ?, ?)", [newAccount.id_account, newAccount.balance, newAccount.credit_limit], callback);
    },

    updateAccount(id, updateAccount, callback){
        return db.query("UPDATE bank_account SET id_account = ?, balance = ?, credit_limit = ? WHERE id_account = ?", [updateAccount.id_account, updateAccount.balance, updateAccount.credit_limit, id], callback);
    },

    deleteAccount(id, callback){
        return db.query("DELETE FROM bank_account WHERE id_account = ?", [id], callback);
    }
}

module.exports = bankaccount;