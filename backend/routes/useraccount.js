const express = require('express');
const router = express.Router();
const useraccount = require('../models/useraccount_model');

router.get('/', function(request, response){
    useraccount.getAllUserAccounts(function(err,result){
        if (err) {
            console.log("Error retrieving user_accounts: " +err);
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
            console.log("Error retrieving user_account row: " +err);
            response.send(err);
        }
        else {
            response.json(result[0]);
        }
    })
});

router.post('/', function(request, response){
    useraccount.addUserAccount(request.body, function(err, result){
        if (err) {
            console.log("Error adding user_account row: " +err);
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.put('/:id', function(request, response){
    useraccount.updateUserAccount(request.params.id, request.body, function(err, result){
        if (err) {
            console.log("Error updating user_account row: " +err);
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:id', function(request, response){
    useraccount.deleteUserAccount(request.params.id, function(err, result){
        if (err) {
            console.log("Error deleting user_account row: " +err);
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

module.exports = router;