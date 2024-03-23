const db = require('../database');

const user = {
    getAllUsers(callback) {
        return db.query("SELECT * FROM user", callback);
    },

    getOneUser(id, callback) {
        return db.query("SELECT * FROM user WHERE id_user=?", [id], callback);
    },

    addUser(newUser, callback) {
        return db.query("INSERT INTO user (fname, lname) VALUES(?,?)", [newUser.fname, newUser.lname], callback);
    },

    updateUser(id_user, updateUser, callback) {
        return db.query("UPDATE user SET fname=?, lname=? WHERE id_user=?", [updateUser.fname, updateUser.lname, id_user], callback);
    },

    deleteUser(id_user, callback) {
        return db.query("DELETE FROM user WHERE id_user=?", [id_user], callback);
    }
}

module.exports = user;
