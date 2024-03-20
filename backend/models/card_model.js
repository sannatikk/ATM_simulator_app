const db = require('../database');

const card = {
    getAllCards(callback) {
        return db.query("SELECT * FROM card", callback);
    },

    getOneCard(id, callback) {
        return db.query("SELECT * FROM card WHERE id_card=?", [id], callback);
    },

    addCard(card, callback) {
        return db.query("INSERT INTO card (id_card, pincode, is_combined) VALUES(?,?,?)", [card.id_card, card.pincode, card.is_combined], callback);
    },

    updateCard(id_card,updateCard, callback) {
        return db.query("UPDATE card SET pincode=?, is_combined=? WHERE id_card=?", [updateCard.pincode, updateCard.is_combined, id_card], callback);
    },

    deleteCard(id_card, callback) {
        return db.query("DELETE FROM card WHERE id_card=?", [id_card], callback);
    }
}

module.exports = card;