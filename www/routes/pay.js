const express = require('express');
const router = express.Router();
const keys = require('../config/keys');
const Lens = require('../models/Lens');
const middleware = require('../middleware');

// Setup stripe 
const stripe = require('stripe')(keys.stripe.privkey);

// User buy page
router.get('/buy', middleware.isLoggedIn, (req, res) => {
    let amount;
    // Modify the pricing here
    req.user.license == 'individual' ? amount = 1000
      : amount = 4000
    res.render('buy', {pubkey: keys.stripe.pubkey, amount: amount, page: 'buy', user: req.user});
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
    // Move items from cart to lenses array
    req.user.cart.forEach((item) => {
      req.user.lenses.push(item);
    });
    // Empty cart
    req.user.cart = [];
    // Save user model
    req.user.save();
    req.flash('success', "Lens successfully purchased.");
    res.redirect('/');
  });
});

module.exports = router;