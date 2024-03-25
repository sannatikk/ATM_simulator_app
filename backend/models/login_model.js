db = require('../database');
const bcrypt = require('bcryptjs');

const userLogin = {
    userLogin(userID, callback) {
        return db.query("SELECT pincode FROM card WHERE id_card=?", [userID], callback);
    }
}

module.exports = userLogin;