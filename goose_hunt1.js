/*VARS for lines for target*/
var xLine = new Line(0, getHeight()/2, getWidth()/2, getHeight()/2);
var xLine2 = new Line(getWidth()/2, getHeight()/2, getWidth(), getHeight()/2);
var yLine = new Line(getWidth()/2, getHeight(), getWidth()/2, getHeight()/2);
///////

///Just make an if statement for every piece of the goose clicked by the mouse
/*VARs for background and ground*/
var back;
var ground;

/*VARs for goose*/
var dx = 2;
var dy = 2;

var square;
var square1;
var square2;
var square3;
var square4;
var square5;
var square6;
var square7;
var square8;
var square9;
///////////

/*VARS for click*/
var currElm;
///////////

function start(){
    setUp();
    setTimer(draw, 20);
}

function setUp(){
    background();
    ground();
    add_goose();
    add(xLine2);
    add(yLine);
    add(xLine);
    mouseMoveMethod(target);
}

function add_goose(){
    /*
    square 0-3 are part of the head
    square 4-5 are part of the neck
    square 6 is the wing
    square 7 is the white end of the goose
    square 8 is the black rectangle that goes across the goose
    square 9 is the black tip of the wing
    */
    square = new Rectangle(10, 10);
    square.setPosition(getWidth()/2, getHeight()/2);
    add(square);
    
    square1 = new Rectangle(5, 5);
    square1.setPosition((getWidth()/2) + 10, (getHeight()/2) + 5);
    add(square1);
    
    square2 = new Rectangle(5, 5);
    square2.setPosition((getWidth()/2) - 5, (getHeight()/2) + 5);
    add(square2);
    
    square3 = new Rectangle(5, 5);
    square3.setPosition((getWidth()/2) + 15, (getHeight()/2) + 5);
    add(square3);
    
    square4 = new Rectangle(5, 5);
    square4.setPosition((getWidth()/2) - 10, (getHeight()/2) + 10);
    add(square4);
    
    square5 = new Rectangle(5, 5);
    square5.setPosition((getWidth()/2) - 15, (getHeight()/2) + 15);
    square5.setColor(Color.white);
    add(square5);
    
    square6 = new Rectangle(30, 40);
    square6.setPosition((getWidth()/2) - 45, (getHeight()/2) - 5);
    square6.setColor("#B8A36F");
    add(square6);
    
    square7 = new Rectangle(10, 10);
    square7.setPosition((getWidth()/2) - 55, (getHeight()/2) + 25);
    square7.setColor(Color.white);
    add(square7);
    
    square8 = new Rectangle(45, 10);
    square8.setPosition((getWidth()/2) - 60, (getHeight()/2) + 15);
    add(square8);
    
    square9 = new Rectangle(15, 10);
    square9.setPosition((getWidth()/2) - 30, (getHeight()/2) - 15);
    add(square9);
}

function remove_goose(){
    remove(square);
    remove(square1);
    remove(square2);
    remove(square3);
    remove(square4);
    remove(square5);
    remove(square6);
    remove(square7);
    remove(square8);
    remove(square9);
}

function click(e){
    /*VAR to store the current location of the mouse*/
    var elm = getElementAt(e.getX(), e.getY());
    ///////
    
    if(elm <= square.getX() + 10 || elm <= square.getY() + 10){
        remove_goose();
    }
    
    if(elm <= square1.getX() + 5 || elm <= square1.getY() + 5){
        remove_goose();
    }
    
    if(elm <= square2.getX() + 5 || elm <= square2.getY() + 5){
        remove_goose();
    }
    
    if(elm <= square3.getX() + 5 || elm <= square3.getY() + 5){
        remove_goose();
    }
    
    if(elm <= square4.getX() + 5 || elm <= square4.getY() + 5){
        remove_goose();
    }
    
    if(elm <= square5.getX() + 5 || elm <= square5.getY() + 5){
        remove_goose();
    }
    
    if(elm <= square6.getX() + 30 || elm <= square6.getY() + 40){
        remove_goose();
    }
    
    if(elm <= square7.getX() + 10 || elm <= square7.getY() + 10){
        remove_goose();
    }
    
    if(elm <= square8.getX() + 45 || elm <= square8.getY() + 10){
        remove_goose();
    }
    
    if(elm <= square9.getX() + 15 || elm <= square9.getY() + 10){
        remove_goose();
    }
    else{
        println("you missed your shot! :)");
    }
    
}

function move_goose(x, y){
    square.move(x, y);
    square1.move(x, y);
    square2.move(x, y);
    square3.move(x, y);
    square4.move(x, y);
    square5.move(x, y);
    square6.move(x, y);
    square7.move(x, y);
    square8.move(x, y);
    square9.move(x, y);
    
}

function check_walls(){
    if(square3.getX() + square3.getWidth() > getWidth()){
        dx = -dx;
    }
    if(square6.getY() + square6.getHeight() > getHeight()){
        dy = -dy;
    }
    if(square8.getX() < 0){
        dx = -dx;
    }
    if(square9.getY() < 0){
        dy = -dy;
    }
}

function draw(){
    check_walls();
    mouseDownMethod(click);
    move_goose(dx, dy);
}

function target(e){
    xLine2.setPosition(e.getX(), e.getY());
    xLine2.setColor(Color.black);
    xLine2.setEndpoint(getWidth(), e.getY());
    
    xLine.setPosition(e.getX(), e.getY());
    xLine.setColor(Color.black);
    xLine.setEndpoint(0, e.getY());
    
    yLine.setPosition(e.getX(), 0);
    yLine.setColor(Color.black);
    yLine.setEndpoint(e.getX(), getHeight());
}

function background(){
    back = new Rectangle(getWidth(), getHeight());
    back.setColor("#89cff0");
    add(back);
    
}

function ground(){
    ground = new Rectangle(getWidth(), getHeight()/2);
    ground.setColor(Color.green);
    ground.setPosition(0, getHeight()/2);
    add(ground);
}
