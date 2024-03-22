const db = require('../database');

const cardaccount = {
    getAllCardAccount(callback) {
        return db.query("SELECT * FROM card_account", callback);
    },

    getOneCardAccount(id, callback) {
        return db.query("SELECT * FROM card_account WHERE id_card_account=?", [id], callback);
    },

    addCardAccount(newData, callback) {
        return db.query("INSERT INTO card_account (id_account, id_card) VALUES(?,?)", [newData.id_account, newData.id_card], callback);
    },

    updateCardAccount(id, updatedData, callback) {
        return db.query("UPDATE card_account SET id_account=?, id_card=? WHERE id_card_account=?", [updatedData.id_account, updatedData.id_card, id], callback);
    },

    deleteCardAccount(id, callback) {
        return db.query("DELETE FROM card_account WHERE id_card_account=?", [id], callback);
    }
}

module.exports = cardaccount;