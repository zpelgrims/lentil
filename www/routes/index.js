const express = require('express');
const router = express.Router();
const Lens = require('../models/Lens');

// Index Page
router.get('/', (req, res) => {
  Lens.find({}, (err, lenses) => {
    if(err) {
      console.log(err);
    } else {
      res.render('index', {lenses: lenses});
    }
  });
});

module.exports = router;