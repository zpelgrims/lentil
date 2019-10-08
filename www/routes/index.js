const express = require('express');
const router = express.Router();
const Lens = require('../models/Lens');
const sortBy = require('sort-by');
const middleware = require('../middleware');

// Index Page
router.get('/', (req, res) => {
  Lens.find({}, (err, lenses) => {
    if (err) {
      console.log(err);
    } else {
      // Create array of companies for filter options
      let companies = [];
      for (let i = 0; i < lenses.length; i++) {
        if (companies.indexOf(lenses[i].company) > -1) {
        } else {
          companies.push(lenses[i].company);
        }
      }

      // Sort by year
      if (req.query.filter == 'year') {
        lenses.sort(sortBy('year'));
      } else if (req.query.filter == 'focal') {
        lenses.sort(sortBy('fstop'));
      }

      // Display lenses based on company filter query
      if (req.query.company) {
        let lensArray = [];
        lenses.forEach(lens => {
          if (req.query.company == 'all') {
            lensArray.push(lens);
          } else if (req.query.company.constructor === Array) {
            req.query.company.forEach(company => {
              if (lens.company == company) {
                lensArray.push(lens);
              }
            });
          } else {
            if (lens.company == req.query.company) {
              lensArray.push(lens);
            }
          }
        });
        return res.render('index', {
          lenses: lensArray,
          user: req.user,
          companies: companies,
          page: 'lenses',
          query: req.query
        });
      }

      res.render('index', {
        lenses: lenses,
        user: req.user,
        companies: companies,
        page: 'lenses',
        query: req.query
      });
    }
  });
});

// Features Page
router.get('/features', (req, res) => {
  res.render('features', { page: 'features', user: req.user });
});

// Gallery Page
router.get('/gallery', (req, res) => {
  res.render('gallery', { page: 'gallery', user: req.user });
});

// Tutorials Page
router.get('/tutorials', (req, res) => {
  res.render('tutorials', { page: 'tutorials', user: req.user });
});

// Download Page
router.get('/download', middleware.isOwner, (req, res) => {
  res.render('download', { page: 'download', user: req.user });
});

module.exports = router;
