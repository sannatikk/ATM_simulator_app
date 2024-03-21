const express = require('express');
const router = express.Router();
const useraccount = require('../models/useraccount_model');

router.get('/', function(request, response){
    useraccount.getAllUserAccounts(function(err,result){
        if (err) {
            console.log("Virhe hakiessa tietoja: " +err);
            response.send(err);
        }
        else {
            response.json(result)
        }
    });
});

router.get('/:id',function(request, response){
    useraccount.getOneUserAccount(request.params.id, function(err, result){
        if(err){
            console.log("Virhe hakiessa tietoja: " +err);
            response.send(err);
        }
        else {
            response.json(result[0]);
        }
    })
});

// tarviiko tosiaan lisätä post ja put näille, toimiiko se edes? 
// router.post();
// router.put();

module.exports = router;