const db = require('../database');

const useraccount = {

    // note: these queries are used only to modify user-account ownership aka who owns which bank account, not to modify users or accounts themselves!
    // note: both desired id_user and id_account need to ALREADY EXIST in user and bankaccount tables for any of these to work, as you cannot give ownership to something or someone that does not exist

    getAllUserAccounts(callback){
        return db.query("SELECT * FROM user_account", callback);
    },

    getOneUserAccount(id, callback){
        return db.query("SELECT * FROM user_account WHERE id_useraccount = ?", [id], callback);
    },

    addUserAccount(newUserAccount, callback){
        return db.query("INSERT INTO user_account (id_user, id_account) VALUES (?, ?)", [newUserAccount.id_user, newUserAccount.id_account], callback);
    },
    
    updateUserAccount(id, updateUserAccount, callback){
        return db.query("UPDATE user_account SET id_user = ?, id_account = ? WHERE id_useraccount = ?", [updateUserAccount.id_user, updateUserAccount.id_account, id], callback);
    },

    deleteUserAccount(id, callback){
        return db.query("DELETE FROM user_account WHERE id_useraccount = ?", [id], callback);
    }
}

module.exports = useraccount;