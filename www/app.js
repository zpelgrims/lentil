const express = require('express');
const app = express();

// Dynamically switch between dev and live ports
const PORT = process.env.PORT || 3000;

// Setup ejs
app.set('view engine', 'ejs');
// References files from /public directory
app.use(express.static(__dirname + '/public'));

// Require route file(s)
const indexRoutes = require('./routes/index');

// Use route files
app.use(indexRoutes);

app.listen(PORT, () => {
  console.log('The server is running on: ', PORT);
});