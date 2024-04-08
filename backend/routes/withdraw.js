const express = require('express');
const router = express.Router();
const bankaccount = require('../models/bankaccount_model');

router.post('/', function(request, response){
    bankaccount.withdrawMoney(request.body, function(err, result){
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

module.exports = router;