const express = require('express');
const app = express();
const mongoose = require('mongoose');
const Lens = require('./models/Lens');
const lenses = require('./json/lenses_public.json');
const {lensMap} = require('./functions/lensMap');
const passport = require('passport');
const LocalStrategy = require('passport-local');
const User = require('./models/User');
const bodyParser = require('body-parser');

// Dynamically switch between dev and live ports
const PORT = process.env.PORT || 3000;

// Setup database
mongoose.connect('mongodb://localhost/lentil') // Setup production db later

const db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error: '));

// Remove all lens models
Lens.collection.deleteMany({});
// Map json lenses object to array
const lensArray = Object.keys(lenses).map((key) => [key, lenses[key]]);

// For each lens, create a model
// Now update each model upon any changes
lensMap(lensArray);

// Setup ejs
app.set('view engine', 'ejs');
// Setup body-parser
app.use(bodyParser.urlencoded({extended: true}));
// References files from /public directory
app.use(express.static(__dirname + '/public'));

// Passport Config
app.use(require('express-session')({
  secret: 'p4ssp0rt-s3cr3t',
  resave: false,
  saveUninitialized: false,
  maxAge: 365 * 24 * 60 * 60 * 1000
}));
app.use(passport.initialize());
app.use(passport.session());
passport.use(new LocalStrategy(User.authenticate()));
passport.serializeUser(User.serializeUser());
passport.deserializeUser(User.deserializeUser());

// Require route files
const indexRoutes = require('./routes/index');
const userRoutes = require('./routes/user');

// Use route files
app.use(indexRoutes);
app.use(userRoutes);

app.listen(PORT, () => {
  console.log('The server is running on: ', PORT);
});