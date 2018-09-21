const express = require('express');
const router = express.Router();
const keys = require('../keys');
const Lens = require('../models/Lens');

// Setup stripe 
const stripe = require('stripe')(keys.stripe.privkey);

// Stripe payment form
router.get('/:id/pay', (req, res) => {
  Lens.findById(req.params.id, (err, lens) => {
    if(err) {
      console.log(err);
    } else {
      res.render('pay.ejs', {pubkey: keys.stripe.pubkey, lens: lens});
    }
  });
});

// Payment processing logic
router.post('/:id/charge', (req, res) => {
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
  .then(() => {
    Lens.findById(req.params.id, (err, lens) => {
      if(err) {
        console.log(err);
      } else {
        if(req.user) {
          if(req.user.lenses.indexOf(lens._id) == -1) {
            req.user.lenses.push(lens._id);
            req.user.save();
          }
        }
      }
      res.redirect('/');
    });
  });
});

module.exports = router;