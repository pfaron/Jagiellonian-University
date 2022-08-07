const $court = $('#court');
const $racket = $('#racket');
const $ball = $('#ball');
const $startBtn = $('#startBtn');
const $result = $('#result');

const piOver64 = Math.PI / 64;

let interval = null;
let racket = null;
let ball = null;
let counter = 0;

$startBtn.click(function () {
    start();
})

function start() {
    $result.css({
        visibility: `hidden`,
    });

    ball = {
        top: 240,
        left: 400,
        angle: 0,
        speed: 5
    }

    clearInterval(interval);

    interval = setInterval(update, 16);
}

function init() {

    racket = {
        speed: 15,
        top: 0
    }

}

$court.mousemove(function (evt) {

    if (!interval) {
        return;
    }

    racket.top = Math.max(
        0,
        evt.pageY - $court.offset().top - ($racket.height() / 2)
    )
    racket.top = Math.min(
        $court.height() - $racket.height(),
        racket.top
    )
    $racket.css({
        top: `${racket.top}px`
    });

});

// 38 - up
// 40 - down


$(document).keydown(function (event) {

    if (!interval) {
        return;
    }

    var key = (event.keyCode ? event.keyCode : event.which);

    if (key == '38') {

        racket.top = Math.max(
            0,
            racket.top - racket.speed
        )
    } else if (key == '40') {

        racket.top = Math.min(
            $court.height() - $racket.height(),
            racket.top + racket.speed
        )
    }

    $racket.css({
        top: `${racket.top}px`
    });

});

function update() {
    updateBall();
    changeAngle();
}

// return a number between [-offset; offset)
function randomNumber(offset) {
    return (Math.random() - 0.5) * 2 * offset;
}

function updateAngle(prev, toAdd) {
    return (prev + toAdd) % (2 * Math.PI);
}

function changeAngle() {
    if (counter++ === 10) {
        counter = 0;
        ball.angle = updateAngle(ball.angle, randomNumber(piOver64));
    }
}

function updateBall() {

    // angles:
    // 0 * pi / 4 -> right
    // 1 * pi / 4 -> down right
    // 2 * pi / 4 -> down
    // 3 * pi / 4 -> down left
    // 4 * pi / 4 -> left
    // 5 * pi / 4 -> up left
    // 6 * pi / 4 -> up
    // 7 * pi / 4 -> up right

    function reflectAngle(normal, angle) {
        const incidenceAngle = angle + Math.PI - normal;
        return (normal - incidenceAngle) % (2 * Math.PI);
    }

    const HORIZONTAL_NORMAL = 2 * Math.PI / 4;
    const VERTICAL_NORMAL = 0;

    if (isBallOverlappingWithRacket()) {
        ball.angle = reflectAngle(VERTICAL_NORMAL, ball.angle);
        ball.speed += 1;
    } else if (isBallOverlappingWithRight()) {
        ball.angle = reflectAngle(VERTICAL_NORMAL, ball.angle);
    } else if (isBallOverlappingWithTop()) {
        ball.angle = reflectAngle(HORIZONTAL_NORMAL, ball.angle);
    } else if (isBallOverlappingWithBottom()) {
        ball.angle = reflectAngle(HORIZONTAL_NORMAL, ball.angle);
    }


    ball.top += ball.speed * Math.sin(ball.angle);
    ball.left += ball.speed * Math.cos(ball.angle);

    $ball.css({
        top: `${ball.top}px`,
        left: `${ball.left}px`
    });

    const lost = isLost();
    if (lost) {
        endGame(lost);
    }
}

function endGame(lost) {
    clearInterval(interval);
    interval = null;

    $result.text(`${lost}`);
    $result.css({
        visibility: `visible`,
    });
    $startBtn.text("Restart");
}

function isBallOverlappingWithRacket() {
    return $ball.overlaps('#racket').length > 0;
}

function isBallOverlappingWithTop() {
    return ball.top <= 0;
}

function isBallOverlappingWithBottom() {
    return ball.top >= $court.height() - $ball.height();
}

function isBallOverlappingWithRight() {
    return ball.left >= $court.width() - $ball.width();
}

function isLost() {
    if (ball.left < 0) {
        return `You lost at speed ${ball.speed}!`;
    } else {
        return false;
    }
}

init();