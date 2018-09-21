const express = require('express');
const router = express.Router();
const keys = require('../keys');

// Setup stripe 
const stripe = require('stripe')(keys.stripe.privkey);

// Stripe payment form
router.get('/:id/pay', (req, res) => {
  res.render('pay.ejs', {pubkey: keys.stripe.pubkey});
});

// Payment processing logic
router.post('/charge', (req, res) => {
  let amount = 500;

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
  .then(charge => res.render("charge.ejs"));
});

module.exports = router;