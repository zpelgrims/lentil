const Lens = require('../models/Lens');

function lensMap(lensArray) {
  for(var i = 0; i < lensArray.length; i++) {
    Lens.collection.findOneAndUpdate({
      company: lensArray[i][1].company,
      product_name: lensArray[i][1]['product-name']
    }, {$set: {
      commercial: lensArray[i][1].commercial,
      company: lensArray[i][1].company,
      focal_length_mm_patent:  lensArray[i][1]['focal-length-mm-patent'],
      focal_length_mm_raytraced: lensArray[i][1]['focal-length-mm-raytraced'],
      fstop: lensArray[i][1].fstop,
      notes: lensArray[i][1].notes,
      patent_number: lensArray[i][1]['patent-number'],
      polynomial_optics: lensArray[i][1]['polynomial-optics'],
      prime: lensArray[i][1].prime,
      product_name: lensArray[i][1]['product-name'],
      production_ready: lensArray[i][1]['production-ready'],
      year: lensArray[i][1].year,
      image: lensArray[i][1]['www-svg-location']
    }}, {upsert: true, new: true, setDefaultsOnInsert: true});
  }
}

module.exports = {lensMap};