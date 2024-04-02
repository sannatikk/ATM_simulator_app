const db = require('../database');
const bcrypt = require('bcryptjs');

const card = {
    getAllCards(callback) {
        return db.query("SELECT * FROM card", callback);
    },

    getOneCard(id, callback) {
        return db.query("SELECT * FROM card WHERE id_card=?", [id], callback);
    },

    addCard(newCard, callback) {
        bcrypt.hash(newCard.pincode, 10, function (err, hashedPassword) {
            return db.query("INSERT INTO card (id_card, pincode, is_combined) VALUES(?,?,?)", [newCard.id_card, hashedPassword, newCard.is_combined], callback);
        });
    },

    updateCard(id_card, updateCard, callback) {
        bcrypt.hash(updateCard.pincode, 10, function (err, hashedPassword) {
            return db.query("UPDATE card SET pincode=?, is_combined=?, is_locked=? WHERE id_card=?", [hashedPassword, updateCard.is_combined, updateCard.is_locked, id_card], callback);
        });
    },

    deleteCard(id_card, callback) {
        return db.query("DELETE FROM card WHERE id_card=?", [id_card], callback);
    }
}

module.exports = card;