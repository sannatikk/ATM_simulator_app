const express = require('express');
const router = express.Router();
const cardaccount = require('../models/cardaccount_model');

router.get('/:id', function (request, response) {
    cardaccount.getAccountsInCard(request.params.id, function (err, result) {
        if (err) {
            console.log(err);
            response.send(err);
        }
        else {
            if (result.length === 1) {
                console.log(result[0]);
                response.json(result[0]);
            }
            else {
                console.log(result);
                response.json(result);
            }
        }
    });
});

module.exports = router;