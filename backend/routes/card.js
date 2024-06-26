const express = require('express');
const router = express.Router();
const card = require('../models/card_model');

router.get('/', function (request, response) {
    card.getAllCards(function (err, result) {
        if (err) {
            console.log(err)
            response.send(err);
        }
        else {
            console.log(result)
            response.json(result);
        }
    });
});

router.get('/:id', function (request, response) {
    card.getOneCard(request.params.id, function (err, result) {
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            console.log(result);
            response.json(result[0]);
        }
    });
});

router.post('/', function (request, response) {
    card.addCard(request.body, function (err, result) {
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});


router.put('/:id', function (request, response) {
    card.updateCard(request.params.id, request.body, function (err, result) {
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
    card.deleteCard(request.params.id, function (err, result) {
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            console.log(result);
            response.json(result);
        }
    });
})
module.exports = router;