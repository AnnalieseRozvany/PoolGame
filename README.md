# PoolGame
A C++ pool game, which implements multiple design patterns. (Created in OOD class)

The game was implemented in several stages, each of which including more features than the last. The code takes in a json config file which specifies which stage, the user wants to run, as well as other information.

```
{
"stage3" : true,
"table" : {
 "colour":"#00cc99",
 "size":{
 "x":900,
 "y":450
 },
 "friction":0.1,
 "pockets": [
 {"position":{"x":5,"y":5}, "radius":20},
 {"position":{"x":895,"y":445}, "radius":20},
 {"position":{"x": 895,"y":5}, "radius":20},
 {"position":{"x":5,"y":445}, "radius":20},
 {"position":{"x":200,"y":200},"radius":20, "portal": true, "number": 1, "out": 2, "type": 0},
 {"position":{"x":400,"y":400},"radius":20, "portal": true, "number": 2, "type": 1},
 {"position":{"x":600,"y":200},"radius":20, "portal": true, "number": 3, "out": 4, "type": 0},
 {"position":{"x":600,"y":400},"radius":20, "portal": true, "number": 4, "type": 1},
 {"position":{"x":800,"y":300},"radius":20, "portal": true, "number": 5, "out": 6, "type": 0},
 {"position":{"x":550,"y":150},"radius":20, "portal": true, "number": 6, "type": 1},
 {"position":{"x":700,"y":300},"radius":20, "portal": true, "number": 5, "out": 6, "type": 0},
 {"position":{"x":100,"y":100},"radius":20, "portal": true, "number": 6, "type": 1}
 ]
},
"balls" : [
 {"position":{"x":50,"y":50},"velocity":{"x":0,"y":0},"mass":1},
 {"colour":"#9966ff","position":{"x":150,"y":60},"mass":1,"radius":10},
 {"colour":"#9966ff","position":{"x":-150,"y":60},"mass":1,"radius":10},
 {"colour":"#6699ff","position":{"x":150,"y":40},"velocity":{"x":0,"y":0},"radius":10},
 {"colour":"#ffccff","position":{"x":250,"y":70},"mass":1,"radius":20,"strength":1e5,
 "balls":[
 {"position":{"x":-10,"y":0},"mass":1,"radius":10},
 {"position":{"x":-100,"y":0},"mass":1,"radius":10},
 {"colour":"aqua","position":{"x":10,"y":0}},
 {"colour":"#ff9999","position":{"x":0,"y":-10}},
 {"position":{"x":0,"y":10}, "mass":2,"strength":1e4,
 "balls":[
 {"colour":"aqua","strength":1e3,
 "balls":[
 {"colour":"#ff9999", "strength":1e4}
 ]
 }]
 }]
 }]
}
```

**Stage 1 features:**
- Balls can bounce off eachother / the walls
- Balls are removed from the game when going into black corner holes

**Stage 2 features:**
- Can click and drag a line to hit the white ball, only when still
- Balls can contain other balls
- If balls are hit with enough force they break, and if they have balls inside - they will roll out.
- Visibility of inner balls can be toggled

**Stage 3 features:**
- Moves can be undone by pressing 'R', the balls will all go back to their previous position.
- The game can be started again by pressing 'N'. 
- Pockets can be specified to be in/out portals. Each "in" portal has a corresponding "out" pocket". If the ball rolls into the in pocket, it will roll out of the out pocket. 
- Balls can be added mid-game, by pressing 'B'
- When 'X' is pressed, breakable balls with children balls will explode.

## Design Patterns


**Composite Design Pattern** - for the inclusion of balls within other balls

**Prototype Design Pattern** - used as a way to create deep copies of the game balls to then be saved so that they can be reverted to. The Ball class acts as the Prototype, declaring an interface to clone itself. The descendants of Ball (Stage1Ball, BallDecorator, Stage2Ball, and their descendants) implement the cloning interface, returning new copies of themselves. The prototype design pattern is accessed by the Dialog class, which acts as the client. 

**Memento Design Pattern** - used to store the states of the balls produced by the prototype cloning so that they can be returned to. The state in the memento design pattern is a pointer to a vector of pointers to Balls. The dialog class acts as the caretaker, managing the mementos. 

**Decorator pattern** - used to make portals from pockets. 
