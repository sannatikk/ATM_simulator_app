const db = require('../database');

const transaction = {
    getAllTransactions(callback){
        return db.query("SELECT * FROM transaction_log",callback);
    },
    getOneTransaction(id, callback){
        return db.query("SELECT * FROM transaction_log WHERE id_transaction=?",[id],callback);
    },
    addTransaction(transaction,callback){
        return db.query("INSERT INTO transaction_log(id_account, transaction_type, transaction_amount, transaction_time) VALUES(?,?,?,?)",[transaction.id_account, transaction.transaction_type, transaction.transaction_amount, transaction.transaction_time],callback);
    },
    updateTransaction(id_transaction, updateTransaction,callback){
        return db.query("UPDATE transaction_log SET id_account=?, transaction_type=?, transaction_amount=?, transaction_time=? WHERE id_transaction=?",[updateTransaction.id_account, updateTransaction.transaction_type, updateTransaction.transaction_amount, updateTransaction.transaction_time, id_transaction],callback);
    },
    deleteTransaction(id_transaction,callback){
        return db.query("DELETE FROM transaction_log WHERE id_transaction=?",[id_transaction],callback);
    },
    getAccountTransactions(id_account, callback){
        return db.query("SELECT * FROM transaction_log WHERE id_account=?", [id_account], callback);
    }
}

module.exports = transaction;