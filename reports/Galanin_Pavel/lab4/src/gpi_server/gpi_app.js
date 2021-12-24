const path = require('path');
const express = require('express');

const app = express();
app.listen(3002);
console.log(`Open http://localhost:3002/`);

app.use(express.static(path.join(__dirname, 'public')));

app.get("/", function (req, res) {
    res.send("Hello, world!");
});

app.get("/versions", function (req, res) {
    res.send(require('./gpi_versions.json'));
});
