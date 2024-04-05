const express = require('express');
const router = express.Router();
const transaction = require('../models/transaction_model');

router.get('/:id', function(request, response){
    transaction.getAccountTransactions(request.params.id, function(err, result){
        if(err) {
            console.log(err);
            response.send(err);
        }
        else {
            console.log(result);
            response.json(result);
        }
    });
});

module.exports = router;