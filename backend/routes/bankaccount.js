const express = require('express');
const router = express.Router();
const bankaccount = require('../models/bankaccount_model');

router.get('/', function(request, response){
    bankaccount.getAllAccounts(function(err, result){
        if (err) {
            console.log("Virhe tilien haussa: " +err);
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

router.get('/:id', function(request, response){
    bankaccount.getOneAccount(request.params.id, function(err, result){
        if (err) {
            console.log("Virhe tilin haussa: " +err);
            response.send(err);
        }
        else {
            response.json(result[0]);
        }
    });
});

router.post('/', function(request, response){
    bankaccount.addAccount(request.body, function(err, result){
        if (err) {
            console.log("Virhe tilin lisäämisessä: " +err);
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.put('/:id', function(request, response){
    bankaccount.updateAccount(request.params.id, request.body, function(err, result){
        if (err) {
            console.log("Virhe päivittäessä tiliä: " +err);
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:id', function(request, response){
    bankaccount.deleteAccount(request.params.id, function(err, result){
        if (err) {
            console.log("Virhe poistaessa tiliä: " +err);
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

module.exports = router;