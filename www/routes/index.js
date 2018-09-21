const express = require('express');
const router = express.Router();
const Lens = require('../models/Lens');
const sortBy = require('sort-by');

// Index Page
router.get('/', (req, res) => {
  Lens.find({}, (err, lenses) => {
    if(err) {
      console.log(err);
    } else {
      if(req.query.filter == 'company') {
        lenses.sort(sortBy('company'));
      } else if(req.query.filter == 'product') {
        lenses.sort(sortBy('product_name'));
      } else if(req.query.filter == 'year') {
        lenses.sort(sortBy('year'));
      }
      res.render('index', {lenses: lenses, user: req.user});
    }
  });
});

module.exports = router;