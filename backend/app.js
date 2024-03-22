var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');

var cardRouter = require('./routes/card');
var bankaccountRouter = require('./routes/bankaccount');
var transactionRouter = require('./routes/transaction');
var useraccountRouter = require('./routes/useraccount');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/card', cardRouter);
app.use('/bankaccount', bankaccountRouter);
app.use('/transaction', transactionRouter);
app.use('/useraccount', useraccountRouter);

module.exports = app;