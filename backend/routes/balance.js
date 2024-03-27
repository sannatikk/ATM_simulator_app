const express = require('express');
const router = express.Router();
const bankaccount = require('../models/bankaccount_model');

router.get('/:id', function(request, response){
    bankaccount.getBalance(request.params.id, function(err, result){
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            response.json(result[0].balance);
        }
    });
});

module.exports = router;