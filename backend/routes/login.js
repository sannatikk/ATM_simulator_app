const express = require('express');
const router = express.Router();
const login = require('../models/login_model');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');
dotenv.config();

router.post('/', function (request, response) {
    if (request.body.id_card && request.body.pincode) {                                                 //Check that needed forms are filled
        login.userLogin(request.body.id_card, function (err, result) {
            if (err) {
                console.log(err);
                response.json(err.errno);
            }
            else {
                if (result.length > 0) {
                    bcrypt.compare(request.body.pincode, result[0].pincode, function (err, compareResult) {   //Compare pincode from body to pincode from db
                        if (compareResult) {
                            console.log("Login Success");
                            const token = genToken({ id_card: request.body.id_card });
                            response.send(token);
                        }
                        else {
                            console.log("Wrong pincode");
                            response.send(false);
                        }
                    });
                }
                else {
                    console.log("Wrong ID or pincode");
                    response.send(false);
                }
            }
        });
    }
    else {
        console.log("Insert Card and pincode");
        response.send(false);
    }
});

function genToken(value) {
    return jwt.sign(value, process.env.MY_TOKEN, { expiresIn: '3600s' });
}

module.exports = router;