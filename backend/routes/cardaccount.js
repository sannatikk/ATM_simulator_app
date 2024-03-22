const express = require('express');
const router = express.Router();
const cardaccount = require('../models/cardaccount_model');

router.get('/', function (request, response) {
    cardaccount.getAllCardAccount(function (err, result) {
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            console.log(result);
            response.json(result);
        }
    });
});

router.get('/:id', function (request, response) {
    cardaccount.getOneCardAccount(request.params.id, function (err, result) {
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            console.log(result);
            response.json(result);
        }
    });
});

router.post('/', function (request, response) {
    cardaccount.addCardAccount(request.body, function (err, result) {
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            console.log(result);
            response.json(result);
        }
    });
});

router.put('/:id', function (request, response) {
    cardaccount.updateCardAccount(request.params.id, request.body, function (err, result) {
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            console.log(result);
            response.json(result);
        }
    });
});

router.delete('/:id', function (request, response) {
    cardaccount.deleteCardAccount(request.params.id, function (err, result) {
        if (err) {
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