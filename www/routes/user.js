const express = require('express');
const router = express.Router();
const User = require('../models/User');
const passport = require('passport');
const LocalStrategy = require('passport-local');

// Register page
router.get('/register', (req, res) => {
  res.render('register', {user: req.user});
});

// Register logic
router.post('/register', (req, res) => {
  User.register(
    new User({
      email: req.body.email,
      username: req.body.username,
      license: req.body.license
    }), req.body.password, (err, user) => {
    if(err) {
      console.log(err);
      req.flash('error', 'A user with the given username or email already exists.');
      return res.render('register', {user: req.user});
    }
    passport.authenticate('local', {
      failureRedirect: '/register',
      failureFlash: true
    })(req, res, () => {
      req.flash('success', "Registration successful.");
      res.redirect('/');
    });
  });
});

// Login page
router.get('/login', (req, res) => {
  res.render('login', {user: req.user});
});

// Login logic
router.post('/login', passport.authenticate('local', {
  failureRedirect: '/login',
  failureFlash: true
  }), (req, res) => {
    req.flash('success', "Login successful.");
    res.redirect(req.session.returnTo || '/');
    delete req.session.returnTo;
});

// Logout logic
router.get('/logout', (req, res, next) => {
  req.logout();
  req.flash('success', "Logout successful.");
  res.redirect('/');
});

module.exports = router;