/* Constants for bricks */ var NUM_ROWS = 8; var BRICK_TOP_OFFSET = 10; var BRICK_SPACING = 2; var NUM_BRICKS_PER_ROW = 10; var BRICK_HEIGHT = 10; var SPACE_FOR_BRICKS = getWidth() - (NUM_BRICKS_PER_ROW + 1) * BRICK_SPACING; var BRICK_WIDTH = SPACE_FOR_BRICKS / NUM_BRICKS_PER_ROW;

/* Constants for ball and paddle */ var PADDLE_WIDTH = 80; var PADDLE_HEIGHT = 15; var PADDLE_OFFSET = 10;

var BALL_RADIUS = 15;

var ball;

var width = getWidth();

var height = getHeight();

var dx = 4; var dy = 4;

var counter = 0; var counterTwo = 0; var counterThree = 0;

var colorChange = Color.red;

var paddle; var paddleX = width/2 - PADDLE_WIDTH /2; var paddleY = height - PADDLE_OFFSET - (PADDLE_HEIGHT /2);

function start(){
	makeRows();
	ball = new Circle(BALL_RADIUS);
	ball.setPosition(width/2, height/2); 
	add(ball);

	paddle = new Rectangle(PADDLE_WIDTH, PADDLE_HEIGHT);
	paddle.setPosition(paddleX, paddleY);
	mouseMoveMethod(movePaddle);
	add(paddle);

	setTimer(draw, -1);
}

function draw(){ //checks if the ball has hit any bricks checkElement(); //checks if the ball is hitting a wall checkWalls(); //moves the ball ball.move(dx, dy); }

function brick(color, x, y){ 
	var rect = new Rectangle(BRICK_WIDTH, BRICK_HEIGHT); 
	rect.setColor(color); 
	rect.setPosition(x, y); 
	add(rect); 
}

function brickColor(){ 
	if (counterThree == 20){ 
		colorChange = Color.orange; 
	}else if(counterThree == 40){ 
		colorChange = Color.green; 
	}else if(counterThree == 60){ 
		colorChange = Color.blue; 
	}else if(counterThree == 80){ 
		colorChange = Color.red; 
	} 
}

function makeRows(){ 
	for(var i = 0; i <= ((NUM_BRICKS_PER_ROW * NUM_ROWS)-1); i++){ 
		counterThree++; 
		if(i % 10 == 0){ 
			counter++; 
		} 
		counterTwo++; 
		if(i % 10 == 0){ 
			counterTwo = 0; 
		} 
		brick(colorChange, 0 + BRICK_SPACING + (BRICK_WIDTH * counterTwo + BRICK_SPACING * counterTwo), (BRICK_TOP_OFFSET * counter + BRICK_SPACING * counter));
		brickColor();
    }
}

function checkElement(){ 
	var elemT = getElementAt(ball.getX(), ball.getY() - 15); 
	var elemB = getElementAt(ball.getX(), ball.getY() + 15); 
	var elemL = getElementAt(ball.getX() - 15, ball.getY()); 
	var elemR = getElementAt(ball.getX() + 15, ball.getY());

	if(elemT != null){
	    dy = -dy;
	    if(elemT.getColor() != Color.black){
		remove(elemT);
	    }
	}

	if(elemB != null){
	    dy = -dy;
	    if(elemB.getColor() != Color.black){
		remove(elemB);
	    }
	}

	if (elemL != null){
	    dy = -dy;
	    if(elemL.getColor() != Color.black){
		remove(elemL);
	    }
	}

	if (elemR != null){
	    dy = -dy;
	    if(elemR.getColor() != Color.black){
		remove(elemR);
	    }
	}
}

function checkWalls(){ // Bounce off right wall if(ball.getX() + ball.getRadius() > getWidth()){ dx = -dx; }

// Bounce off left wall
if(ball.getX() - ball.getRadius() < 0){
	dx = -dx;
}

// Bounce off bottom wall
if(ball.getY() + ball.getRadius() > getHeight()){
    stopTimer(draw);
    var txt = new Text("You lost! 😂", "Comic Sans");
    txt.setPosition(width/4, height/3);
    add(txt);
    ball.setPosition(width/2, height/2);
}

// Bounce off top wall
if(ball.getY() - ball.getRadius() < 0){
	dy = -dy;
	}
}

function movePaddle(e) { 
	paddle.setPosition(e.getX() - PADDLE_WIDTH / 2, paddleY);

	if (e.getX() <= (PADDLE_WIDTH / 2)) {
    		paddle.setPosition(0, paddleY);
	}

	if (e.getX() >= (getWidth() - (PADDLE_WIDTH /2))) {
    		paddle.setPosition(getWidth() - PADDLE_WIDTH, paddleY);
	}
}
