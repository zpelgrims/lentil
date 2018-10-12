let middlewareObj = {};
const Lens = require('../models/Lens');

middlewareObj.isLoggedIn = (req, res, next) => {
  if(req.isAuthenticated()) {
    return next();
  }
  console.log('User not logged in');
  req.flash('error', 'You must be logged in to do that.');
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

module.exports = middlewareObj;