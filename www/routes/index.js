const express = require('express');
const router = express.Router();
const Lens = require('../models/Lens');
const sortBy = require('sort-by');
const middleware = require('../middleware');

// Index Page
router.get('/', (req, res) => {
  Lens.find({}, (err, lenses) => {
    if(err) {
      console.log(err);
    } else {
      // Sort by year
      if(req.query.filter == 'year') {
        lenses.sort(sortBy('year'));
      } else if (req.query.filter == 'focal') {
        lenses.sort(sortBy('fstop'));
      }

      // Create array of companies for filter options
      let companies = [];
      for(let i = 0; i < lenses.length; i++) {
        if(companies.indexOf(lenses[i].company) > -1) {
        } else {
          companies.push(lenses[i].company);
        }
      }

      // Display lenses based on company filter query
      if(req.query.company) {
        let lensArray = [];
        lenses.forEach((lens) => {
          if(req.query.company == 'all') {
            lensArray.push(lens);
          } else if(req.query.company.constructor === Array) {
            req.query.company.forEach((company) => {
              if(lens.company == company) {
                lensArray.push(lens);
              }
            });
          } else {
            if(lens.company == req.query.company) {
              lensArray.push(lens);
            }
          }
        });
        return res.render('index', {lenses: lensArray, user: req.user, companies: companies, page: 'lenses', query: req.query});
      }

      res.render('index', {lenses: lenses, user: req.user, companies: companies, page: 'lenses', query: req.query});
    }
  });
});

router.get('/:id/add', middleware.isLoggedIn, middleware.isCartable, (req, res) => {
  Lens.findById(req.params.id, (err, lens) => {
    if(err) {
      console.log(err);
    } else {
      req.user.cart.push(lens._id);
      req.user.save();
    }
    req.flash('success', "Lens successfully added to cart.");
    res.redirect('back');
  });
});

module.exports = router;