const express = require('express');
const router = express.Router();
const keys = require('../config/keys');
const Lens = require('../models/Lens');
const middleware = require('../middleware');
const build = require('../functions/build');

// Setup stripe 
const stripe = require('stripe')(keys.stripe.privkey);

// User cart page
router.get('/cart', middleware.isLoggedIn, (req, res) => {
  Lens.find({}, (err, lenses) => {
    if(err) {
      console.log(err);
    } else {
      let lensArray = [];
      req.user.cart.forEach((item) => {
        lenses.forEach((lens) => {
          if(item.toString() == lens._id.toString()) {
            lensArray.push(lens);
          }
        });
      });
      let amount;
      req.user.license == 'individual' ? amount = 1000 * req.user.cart.length 
        : amount = 4000 * req.user.cart.length;
      res.render('cart', {lenses: lensArray, pubkey: keys.stripe.pubkey, amount: amount, page: 'cart', user: req.user});
    }
  });
});

// Remove cart item logic
router.get('/cart/:id/delete', (req, res) => {
  Lens.findById(req.params.id, (err, lens) => {
    if(err) {
      console.log(err);
      req.flash('error', "Oops. Something went wrong.");
    } else {
      let i = req.user.cart.indexOf(lens._id);
      console.log(i);
      if(i > -1) {
        req.user.cart.splice(i, 1);
        req.user.save();
      }
      req.flash('success', "Lens successfully removed from your cart.");
      res.redirect('back');
    }
  });
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