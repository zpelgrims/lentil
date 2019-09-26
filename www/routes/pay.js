const express = require('express');
const router = express.Router();
const keys = require('../config/keys');
const middleware = require('../middleware');

// Setup stripe 
const stripe = require('stripe')(keys.stripe.privkey);

// User buy page
router.get('/buy', middleware.isLoggedIn, (req, res) => {
    res.render('buy', {pubkey: keys.stripe.pubkey, page: 'buy', user: req.user});
});

// Payment processing logic
router.post('/charge', middleware.isLoggedIn, (req, res) => {
  stripe.customers.create({
    email: req.body.stripeEmail,
    source: req.body.stripeToken
  })
  .then(customer =>
    stripe.charges.create({
      amount,
      description: "Sample Charge",
      currency: "usd",
      customer: customer.id
    }))
  .then(() => {
    req.user.owner = true;
    req.user.save();
    req.flash('success', "Package successfully purchased.");
    res.redirect('/');
  });
});

module.exports = router;