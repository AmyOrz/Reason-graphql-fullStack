const path = require('path');
const isProd = process.env.NODE_ENV === "production";

module.exports = {
  entry: './lib/es6_global/src/client/index.js',
  mode: isProd ? "production" : "development",
  output: {
    path: path.join(__dirname, "public/js"),
    filename: 'bundle.js',
  },
};
