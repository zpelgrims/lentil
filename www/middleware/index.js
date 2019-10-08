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

middlewareObj.isOwner = (req, res, next) => {
  if(req.isAuthenticated() && req.user.owner) {
    return next();
  }
  req.flash('error', 'You must be an owner to do that.');
  req.session.returnTo = req.path;
}

middlewareObj.isNotOwner = (req, res, next) => {
  if(!req.isAuthenticated() || !req.user.owner) {
    return next();
  }
  req.flash('error', "It seems you've already purchased...");
  req.session.returnTo = req.path;
}

module.exports = middlewareObj;