class Bullet {
    constructor(x, y, speed) {
        this.x = x;
        this.y = y;
        this.speed = speed;
        this.active = false;
    }
    moveUp() {
        this.y -= this.speed;
        if (this.y <= 0) {
            this.remove();
        }
    }
    shoot(x, y) {
        if (!this.active) {

            this.active = true;
            this.x = x;
            this.y = y;
            updateBulletInterval = setInterval(bulletMovement, 20);
        }
    }
    remove() {

        this.active = false;
        ctx.fillStyle = "white";
        ctx.fillRect(this.x, this.y, 8, 20);
        clearInterval(updateBulletInterval);
    }
}

function bulletMovement() {

    if (bullet.active) {

        ctx.fillRect(bullet.x, bullet.y, 8, 20);
        bullet.moveUp();
        ctx.drawImage(bulletImg, bullet.x, bullet.y, 8, 20);

        if (bullet.y <= 0) {
            bullet.remove();
        }

        for (let i = 0; i < enemiesArray.length; i++) {
            let enemy = enemiesArray[i];
            if (enemy.alive && bullet.x >= (enemy.x - 7) && bullet.x <= (enemy.x + 64) && bullet.y >= enemy.y && bullet.y <= (enemy.y + 64)) {
                enemy.kill();
                bullet.remove();
            }
        }
    }

}

class Alien {
    constructor(x, y, speed) {
        this.x = x;
        this.y = y;
        this.speed = speed;
        this.alive = true;
    }

    moveLeft() {
        this.x -= this.speed
    }

    moveRight() {
        this.x += this.speed
    }

    moveDown() {
        this.y += 30;
    }

    kill() {

        ctx.fillRect(this.x, this.y, 64, 64);
        this.alive = false;
        enemiesLeft -= 1;
        if (enemiesLeft <= 0) {
            gameWon();
        }
    }
}

class Player {
    constructor(x, y, speed) {
        this.x = x;
        this.y = y;
        this.speed = speed;
    }

    moveLeft() {
        this.x = Math.max(
            0,
            this.x - this.speed
        );
    }

    moveRight() {
        this.x = Math.min(
            640 - 64,
            this.x + this.speed
        );
    }
}

let updateBulletInterval;
let updateAliensInterval;

let canvas;
let ctx;

let alien01Img;
let playerImg;
let bulletImg;

let player;

let bullet;

const numberOfAliensInRow = 3;
const numberOfRows = 6;
let enemiesLeft = numberOfAliensInRow * numberOfRows;
let enemiesArray;

function setupPlayer() {
    player = new Player((320 - 32), 500, 8);
    ctx.drawImage(playerImg, player.x, player.y, 64, 64);
}

function setupEnemies() {
    enemiesArray = new Array(numberOfRows * numberOfAliensInRow);
    for (let i = 0; i < enemiesArray.length; i++) {
        let y = - Math.floor(i / numberOfAliensInRow) * 96;
        let x = (i % numberOfAliensInRow) * 120;
        enemiesArray[i] = new Alien(x, y, 12);
        ctx.drawImage(alien01Img, x, y, 64, 64);
    }

    updateAliensInterval = setInterval(enemiesMovement, 20);
}

let directionRight = true;

function enemiesMovement() {

    let changeDirection = false;

    for (let i = 0; i < enemiesArray.length; i++) {

        let enemy = enemiesArray[i];

        if (enemy.alive) {

            ctx.fillRect(enemy.x, enemy.y, 64, 64);

            if (directionRight) {
                enemy.moveRight();
                if (enemy.x >= (640 - 64 - enemy.speed)) {
                    changeDirection = true;
                }
            } else {
                enemy.moveLeft();
                if (enemy.x <= 0) {
                    changeDirection = true;
                }
            }
        }
    }

    if (changeDirection) {
        for (let i = 0; i < enemiesArray.length; i++) {

            let enemy = enemiesArray[i];

            if (enemy.alive) {
                enemy.moveDown();
                if (enemy.y >= (500 - 64)) {
                    gameLost();
                }
            }
        }
        directionRight = !directionRight;
    }

    for (let i = 0; i < enemiesArray.length; i++) {
        let enemy = enemiesArray[i];
        if (enemy.alive) {
            ctx.drawImage(alien01Img, enemy.x, enemy.y);
        }

    }

}

function setupBullet() {
    bullet = new Bullet(0, 0, 8);
}

function setup() {
    canvas = document.getElementById('canvas');
    ctx = canvas.getContext('2d');

    ctx.fillStyle = "white";

    alien01Img = new Image();
    playerImg = new Image();
    bulletImg = new Image();

    alien01Img.onload = setupEnemies;
    playerImg.onload = setupPlayer;
    bulletImg.onload = setupBullet;

    alien01Img.src = './resources/alien01.png';
    playerImg.src = './resources/player01.png';
    bulletImg.src = './resources/bullet.png';

}

window.onload = setup;

document.onkeydown = checkKey;
function checkKey(event) {
    event = event || window.event;

    const key = String(event.keyCode ? event.keyCode : event.which);

    if (key === '32') {

        console.log("space");
        bullet.shoot(player.x + 28, player.y - 20);

    } else if (key === '37') {

        console.log("left");
        ctx.fillStyle = "white";
        ctx.fillRect(player.x, player.y, 64, 64);

        player.moveLeft();

        ctx.drawImage(playerImg, player.x, player.y,);

    } else if (key === '39') {

        console.log("right");

        ctx.fillRect(player.x, player.y, 64, 64);

        player.moveRight();

        ctx.drawImage(playerImg, player.x, player.y,);

    }
}

function gameOver() {

    bullet.remove();

    ctx.font = "30px Comic Sans MS";
    ctx.fillStyle = "black";
    ctx.textAlign = "center";

    clearInterval(updateAliensInterval);

    document.onkeydown = null;

}

function gameWon() {
    gameOver();
    ctx.fillText("Game over. You won!", canvas.width / 2, canvas.height / 2);
}

function gameLost() {
    gameOver();
    ctx.fillText("Game over. You lost!", canvas.width / 2, canvas.height / 2);
}