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
      req.flash('error', "This lens doesn't seem to exist.")
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
          req.flash('error', "It looks like you either own this lens already or it's already in your cart.");
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