const express = require('express');
const app = express();

app.get('/nordic_flags', function (req, res) {
    res.send(
        `Guess nordic flag!<br>
        The flag has:<br>
        <a href="http://localhost:3000/cross">Cross</a><br>
        <a href="http://localhost:3000/circle">Circle</a><br>`);
});

app.get('/circle', function (req, res) {
    res.send(
        `Guess nordic flag!<br>
        The flag has:<br>
        <a href="http://localhost:3000/sami">Red, green, blue and yellow</a><br>
        <a href="http://localhost:3000/greenland">White and red</a><br>`);
});

app.get('/sami', function (req, res) {
    res.send(
        `The flag is Sámi's<br>
        <img src="https://upload.wikimedia.org/wikipedia/commons/1/1b/Sami_flag.svg" alt="Sami flag">`);
});

app.get('/greenland', function (req, res) {
    res.send(
        `The flag is Greenland's<br>
        <img src="https://upload.wikimedia.org/wikipedia/commons/0/09/Flag_of_Greenland.svg" alt="Greenland flag">`);
});


app.get('/cross', function (req, res) {
    res.send(
        `Guess nordic flag!<br>
        The flag background is:<br>
        <a href="http://localhost:3000/whitebg">White</a><br>
        <a href="http://localhost:3000/bluebg">Blue</a><br>
        <a href="http://localhost:3000/redbg">Red</a><br>`);
});

app.get('/whitebg', function (req, res) {
    res.send(
        `Guess nordic flag!<br>
        The cross is:<br>
        <a href="http://localhost:3000/finland">Purely blue</a><br>
        <a href="http://localhost:3000/faroe">Red and blue</a><br>`);
});

app.get('/finland', function (req, res) {
    res.send(
        `The flag is Finland's<br>
        <img src="https://upload.wikimedia.org/wikipedia/commons/b/bc/Flag_of_Finland.svg" alt="Finland flag">`);
});

app.get('/faroe', function (req, res) {
    res.send(
        `The flag is Faroe Islands'<br>
        <img src="https://upload.wikimedia.org/wikipedia/commons/3/3c/Flag_of_the_Faroe_Islands.svg" alt="Faroe Islands flag">`);
});

app.get('/bluebg', function (req, res) {
    res.send(
        `Guess nordic flag!<br>
        The cross is:<br>
        <a href="http://localhost:3000/sweden">Purely yellow</a><br>
        <a href="http://localhost:3000/iceland">White and red</a><br>
        <a href="http://localhost:3000/aland">Yellow and red</a><br>`);
});

app.get('/sweden', function (req, res) {
    res.send(
        `The flag is Sweden's<br>
        <img src="https://upload.wikimedia.org/wikipedia/en/4/4c/Flag_of_Sweden.svg" alt="Sweden flag">`);
});

app.get('/iceland', function (req, res) {
    res.send(
        `The flag is Iceland's<br>
        <img src="https://upload.wikimedia.org/wikipedia/commons/c/ce/Flag_of_Iceland.svg" alt="Iceland flag">`);
});

app.get('/aland', function (req, res) {
    res.send(
        `The flag is Åland's<br>
        <img src="https://upload.wikimedia.org/wikipedia/commons/5/52/Flag_of_%C3%85land.svg" alt="Aland flag">`);
});

app.get('/redbg', function (req, res) {
    res.send(
        `Guess nordic flag!<br>
        The cross is:<br>
        <a href="http://localhost:3000/denmark">Purely white</a><br>
        <a href="http://localhost:3000/norway">White and blue</a><br>`);
});

app.get('/denmark', function (req, res) {
    res.send(
        `The flag is Denmark's<br>
        <img src="https://upload.wikimedia.org/wikipedia/commons/9/9c/Flag_of_Denmark.svg" alt="Denmark flag">`);
});

app.get('/norway', function (req, res) {
    res.send(
        `The flag is Norway's<br>
        <img src="https://upload.wikimedia.org/wikipedia/commons/d/d9/Flag_of_Norway.svg" alt="Norway flag">`);
});


app.listen(3000, function () {
    console.log('Guess the flag app listening on port 3000!');
});