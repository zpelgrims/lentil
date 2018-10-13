const express = require('express');
const router = express.Router();
const User = require('../models/User');
const passport = require('passport');
const LocalStrategy = require('passport-local');

// Register page
router.get('/register', (req, res) => {
  res.render('register');
});

// Register logic
router.post('/register', (req, res) => {
  User.register(
    new User({
      email: req.body.email,
      username: req.body.username
    }), req.body.password, (err, user) => {
    if(err) {
      console.log(err);
      return res.render('register');
    }
    passport.authenticate('local')(req, res, () => {
      console.log('Successfully registered!');
      res.redirect('/');
    });
  });
});

// Login page
router.get('/login', (req, res) => {
  res.render('login', {message: req.flash('error')});
});

// Login logic
router.post('/login', passport.authenticate('local', {
  failureRedirect: '/login'
  }), (req, res) => {
    res.redirect(req.session.returnTo || '/');
    delete req.session.returnTo;
});

// Logout logic
router.get('/logout', (req, res, next) => {
  req.logout();
  res.redirect('/');
});

module.exports = router;