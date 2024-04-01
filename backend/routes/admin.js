const express = require('express');
const router = express.Router();
const bankaccount = require('../models/bankaccount_model'); 

router.get('/', function(request, response){
    bankaccount.getAdminInfo(function(err, result){
        if (err){
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