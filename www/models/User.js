const mongoose = require('mongoose');
const passportLocalMongoose = require('passport-local-mongoose');

const userSchema = new mongoose.Schema({
  email: {
    type: String, 
    unique: true,
    trim: true
  }, 
  username: {
    type: String,
    unique: true
  },
  password: {
    type: String
  }
});

userSchema.plugin(passportLocalMongoose);

const User = mongoose.model('User', userSchema);
module.exports = User;