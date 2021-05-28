/* Constants for bricks */
var NUM_ROWS = 8;
var BRICK_TOP_OFFSET = 10;
var BRICK_SPACING = 2;
var NUM_BRICKS_PER_ROW = 10;
var BRICK_HEIGHT = 10;
var SPACE_FOR_BRICKS = getWidth() - (NUM_BRICKS_PER_ROW + 1) * BRICK_SPACING;
var BRICK_WIDTH = SPACE_FOR_BRICKS / NUM_BRICKS_PER_ROW;

/* Constants for ball and paddle */
var PADDLE_WIDTH = 80;
var PADDLE_HEIGHT = 15;
var PADDLE_OFFSET = 10;
var BALL_RADIUS = 15;

/*Global variables*/
var counterY = BRICK_TOP_OFFSET;
var counterX = 0 + BRICK_SPACING;
var colorCounter = 0;
var brick;

/*Shapes*/
var paddle = new Rectangle(PADDLE_WIDTH, PADDLE_HEIGHT);
paddle.setPosition(getWidth()/2 - PADDLE_WIDTH/2, getHeight() - PADDLE_OFFSET * 2);

var ball;
var dx = 4;
var dy = 4;

var vx;
var vy;
var ballElm;
var brickElm;



function start(){
    logic();
}

function logic(){
    Ball();
    add(paddle);
    drawBrick();
    setTimer(draw, 20);
    mouseMoveMethod(move);
    setSpeed();
}

function Ball(){
    ball = new Circle(20);
	ball.setPosition(getWidth()/2, getHeight()/2);
	add(ball);
}

function move(e){
    paddle.setPosition(e.getX() - PADDLE_WIDTH / 2, getHeight() - PADDLE_OFFSET * 2);
}

function drawBrick(){
    while(counterY <= NUM_ROWS * 12){
        brick = new Rectangle(BRICK_WIDTH, BRICK_HEIGHT);//creates brick
        brick.setPosition(counterX, counterY);//sets the starting position for the stating row
        add(brick);
        counterX += BRICK_WIDTH + BRICK_SPACING;//adds the BRICK_WIDTH + the spacing every iteration
        if(counterX >= NUM_BRICKS_PER_ROW * 37){//37 is the number of bricks in the 8 rows of bricks
            counterX = 0 + BRICK_SPACING;
            counterY += BRICK_HEIGHT + BRICK_SPACING;
            //colorCounter ++;
        }
        colorChecker();
        colorCounter ++;
    }
}

function draw(){
	checkObject();
	//checkObjects();
	ball.move(dx, dy);
	checkWin();
	checkLose();
}

function checkWalls(){
	// Bounce off right wall
	if(ball.getX() + ball.getRadius() > getWidth()){
		dx = -dx;
	}
	
	// Bounce off left wall
	if(ball.getX() - ball.getRadius() < 0){
		dx = -dx;
	}
	
	// Bounce off top wall
	if(ball.getY() - ball.getRadius() < 0){
		dy = -dy;
	}
	
	// Bounce off bottom wall
	if(ball.getY() + ball.getRadius() >= getHeight()){
		stopTimer(draw);
	}
	
	//Bounce off paddle
	ballElm = getElementAt(ball.getX(), ball.getY() + ball.getRadius());
	if(ballElm == paddle){
	    dy = -dy;
	}
	
	brickElm = getElementAt(brick.getX() + BRICK_WIDTH, brick.getY() + BRICK_HEIGHT);
	if(brickElm == ballElm){
	    remove(brickElm);
	    dy = -dy;
	}
	
}

function setSpeed(){
    vx = Randomizer.nextInt(2, 7);
    vy = Randomizer.nextInt (2, 7);
    if(Randomizer.nextBoolean()){
        vx = -vx;
    }
}

function colorChecker(){
    if(colorCounter % 2 == 0 ){
        brick.setColor(Color.blue);
    }
    if(colorCounter < 20){
        brick.setColor(Color.red);
    }
    if(colorCounter >= 20 && colorCounter < 40){
        brick.setColor(Color.orange);
    }
    if(colorCounter >= 40 && colorCounter < 60){
        brick.setColor(Color.green);
    }
    if(colorCounter >= 60 && colorCounter < 80){
        brick.setColor(Color.blue);
    }
}


function getCollideObject(){
    var left = ball.getX() - ball.getRadius();
    var right = ball.getX() + ball.getRadius();
    var top = ball.getY() - ball.getRadius();
    var bottom = ball.getY() + ball.getRadius();
    var topLeft = getElementAt(left, top);
    if(topLeft){
        return topLeft;
    }
    var topRight = getElementAt(right, top);
    if(topRight){
        return topRight;
    }
    var bottomLeft = getElementAt(left, bottom);
    if(bottomLeft){
        return bottomLeft;
    }
    var bottomRight = getElementAt(right, bottom);
    if(bottomRight){
        return bottomRight;
    }
}

function checkObject(){
    var elem = getCollideObject();
    if(elem != null){
        if(elem != paddle){
            remove(elem);
            dy = -dy;
        }
    }
}

function checkLose(){
    if(gameOver == true){
        turnsLeft --;
        remove(ball);
        if(turnLeft == 0){
            stopTimer(draw);
            draw(game);
        }else{
            stopTimer(draw);//reset
            setTimer(draw, 40);
            logic();
            setSpeed();
            gameOver = false;
        }
    }
}

function checkWin(){
    if(bricksLeft == 0){
        stopTimer(draw);
    }
}
