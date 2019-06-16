const lenses = require('./json/lenses_public.json');
const { lensMap } = require('./functions/lensMap');
const mongoose = require('mongoose');
const keys = require('./config/keys');

// Connect to database
mongoose.connect(keys.db);

// Map json lenses object to array
const lensArray = Object.keys(lenses).map(key => [key, lenses[key]]);

// Update or add each lens model
lensMap(lensArray);