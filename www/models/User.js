const mongoose = require('mongoose');

const userSchema = new mongoose.Schema({
  email: {
    type: String, 
    unique: true,
    trim: true
  }, 
  password: {
    type: String
  }
});

const User = mongoose.model('User', userSchema);
module.exports = User;