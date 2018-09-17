const express = require('express');
const router = express.Router();
const User = require('../models/User');

// Register page
router.get('/register', (req, res) => {
  res.render('register');
});

// Register logic
router.post('/register', (req, res) => {
  // Handle registration here
  res.redirect('/');
});

// Login page
router.get('/login', (req, res) => {
  res.render('login');
});

// Login logic
router.post('/login', (req, res) => {
  // Handle logic here
  res.redirect('/');
});

module.exports = router;