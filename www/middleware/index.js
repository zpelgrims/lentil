let middlewareObj = {};
const Lens = require('../models/Lens');

middlewareObj.isLoggedIn = (req, res, next) => {
  if(req.isAuthenticated()) {
    return next();
  }
  req.flash('error', 'You must be logged in to do that.');
  req.session.returnTo = req.path;
  res.redirect('/login')
}

middlewareObj.isValidId = (req, res, next) => {
  Lens.findById(req.params.id, (err, lens) => {
    if(err) {
      console.log('Must be a valid lens id');
      res.redirect('back');
    } else {
      return next();
    }
  });
}

middlewareObj.isCartable = (req, res, next) => {
  if(req.isAuthenticated) {
    Lens.findById(req.params.id, (err, lens) => {
      if(err) {
        console.log(err);
      } else {
        if(req.user.cart.indexOf(lens._id) > -1 || req.user.lenses.indexOf(lens._id) > -1) {
          console.log('You either already own this or have it in your cart');
          res.redirect('/');
        } else {
          return next();
        }
      }
    });
  } else {
    console.log('User not logged in');
  }
}

module.exports = middlewareObj;