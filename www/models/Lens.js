const mongoose = require('mongoose');
const lenses = require('../json/lenses_public.json');

const lensSchema = new mongoose.Schema({
  commercial: Boolean,
  company: String,
  focal_length_mm_patent: Number,
  focal_length_mm_raytraced: Number,
  fstop: Number,
  notes: String,
  patent_number: String,
  polynomial_optics: Array,
  prime: Boolean,
  product_name: String,
  production_ready: Boolean,
  year: Number,
  image: String
});

const Lens = mongoose.model('Lens', lensSchema);
module.exports = Lens;