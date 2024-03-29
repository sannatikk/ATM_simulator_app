var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');

var indexRouter = require('./routes/index');
var cardRouter = require('./routes/card');
var bankaccountRouter = require('./routes/bankaccount');
var cardAccountRouter = require('./routes/cardaccount');
var transactionRouter = require('./routes/transaction');
var useraccountRouter = require('./routes/useraccount');
var userRouter = require('./routes/user');

var balanceRouter = require('./routes/balance');
var creditlimitRouter = require('./routes/creditlimit');
var withdrawRouter = require('./routes/withdraw');

var adminRouter = require('./routes/admin');

var loginRouter = require('./routes/login');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

//Unsecured routes

app.use('/', indexRouter);
app.use('/login', loginRouter);

//app.use(authenticateToken);

//Secured routes

app.use('/card', cardRouter);
app.use('/bankaccount', bankaccountRouter);
app.use('/cardaccount', cardAccountRouter);
app.use('/transaction', transactionRouter);
app.use('/useraccount', useraccountRouter);
app.use('/user', userRouter);
app.use('/balance', balanceRouter);
app.use('/creditlimit', creditlimitRouter);
app.use('/withdraw', withdrawRouter);
app.use('/admin', adminRouter);

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];

    console.log("token = " + token);
    if (token == null) return res.sendStatus(401);

    jwt.verify(token, process.env.MY_TOKEN, function (err, user) {

        if (err) return res.sendStatus(403);

        req.user = user;

        next()
    })
}

module.exports = app;