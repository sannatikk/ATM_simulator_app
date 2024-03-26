var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var cardRouter = require('./routes/card');
var bankaccountRouter = require('./routes/bankaccount');
var cardAccountRouter = require('./routes/cardaccount');
var transactionRouter = require('./routes/transaction');
var useraccountRouter = require('./routes/useraccount');
var userRouter = require('./routes/user');
var balanceRouter = require('./routes/balance');
var creditlimitRouter = require('./routes/creditlimit');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/card', cardRouter);
app.use('/bankaccount', bankaccountRouter);
app.use('/cardaccount', cardAccountRouter);
app.use('/transaction', transactionRouter);
app.use('/useraccount', useraccountRouter);
app.use('/user', userRouter);
app.use('/balance', balanceRouter);
app.use('/creditlimit', creditlimitRouter);

module.exports = app;