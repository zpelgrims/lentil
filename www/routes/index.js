const express = require('express');
const router = express.Router();
const Lens = require('../models/Lens');

// Index Page
router.get('/', (req, res) => {
  Lens.find({}, (err, lenses) => {
    if(err) {
      console.log(err);
    } else {
      res.render('index', {lenses: lenses, user: req.user});
    }
  });
});

// Purchase logic
router.get('/:id/purchase', (req, res) => {
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
    res.redirect('back');
  });
});

module.exports = router;