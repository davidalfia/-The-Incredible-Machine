THE INCREDIBLE MACHINE:
----------------------

https://www.youtube.com/watch?v=Yz_Tq_HUxjo&t=120s

Student's details:
------------------

David Alfia  
Ariel Gabel  
Zalman Rabin 
Itzhak Vaknin
Ariel Zingman


General details about the project:
----------------------------------

This project is a tribute to the famous game THE INCREDIBLE MACHINE (the original).
The user interface is made with SFML, the imagery is based on the original game from 1993,
and the music and sounds were mosly made originaly for this game except for some sound effects found online.
For the physics we used the Box2D library.

The menu is pretty straightforward, the play button takes you to the game, the exit button closes the game,
the bomb clears the objects that were already set up by the user and the score, letting the user start the current level again.
The puzzle button takes you to the choose level screen where you can scroll thru the levels and choose the one you want to play.
The only button that is not so straight forward is the wranch, it will take you to the build level mode, once on it you can 
play freely using all the objects available in the game to make your own scenarios, and even build levels for the game! (more on that later on).

Before pressing play check the text box on the menu, there you can see what do you need to do to pass the level.
Once inside use the objects on the toolbar to make the things happen, explore all the objects and possibilities, 
some objects have options like rotations, or different sizes, and some levels have many ways to get to the solution,
the longer it takes you the less score you will get on the level.
Once you have set all the objects in the screen use the run button in the top right corner to activate gravity and see if you found the solution.


Design:
-------
A (not so) short definition of each class can be found below (next to each file) and the specifics of every
class can be found in the UML includeded in the zip/repo.

List of the files and classes written by us:
--------------------------------------------

main:
- main func of the program, creating the box2d world, running and catching exceptions

OverallController:
- this object is made once and is basically the menu of the game that controls everything


ResourceManager:
- this is a singleton class that saves all the files that need to be loaded only once
  (textures, sounds, fonts, etc.)

LevelController:
- this class in charge of running the level, holds the board, the toolbar, the score and takes care
  of both running the solution (applying gravity and checking if the level was won) and letting the player add and move around objects

Level.cpp, Level.h:
- this class is a storage class, it holds vectors of toolbar objects, board objects, location conditions to win the level, and activation conditions
  to win the level
  every level gets build by the FileHandler and every level is used to "feed" the levelController and load different levels
  (there's also a special constructor for the free play/build mode)

FileHandler:
- this class is in charge of reading the levels from the level.txt file and converting it into a vector of levels,
  and also saving new boards into a newLevel.txt file that will appear in the build folder once you save something

Board:
- this class holds the gameObj's, it knows how to create them, move them around, activate the physics, and even check if the conditions
  were acomplished and letting the levelController know that the level was won

Toolbar:
- this class holds all the toolbarButtons which are images with an amount, and also the run and arrows buttons

Score:
- this class is in charge of the score on the bottom of the screen, it knows how to make it run, stop, reset, and get the current score

MyListener:
- a class that derives from a Box2D class that allows us to get "callbacks" from the world whenever there is a collision.

Collisions:
- this class is called by the listener (thru the board) and has all the collision functions that need to be run for each collision,
  this class is implemented using the MultiMethods design pattern

CollisionsSFML:
- this was taken "as is" from the git repo of the SFML team, its a class that allows pixel perfect collision recognision.
  it's used for checking collisions when placing objects in the board, making the user experience more fun and real (Bounding boxes are not so fun)
  (the option to use the Box2D will be checked for later releases)

Factory:
- a (quite complex) class for making the GameObj's (lamdas, and all kinds of ugly syntax were used mostly to stress and confuse people, and compilers)

BaseImg:
- this is the base class for everything that you will see rendered on the screen, it basically holds a sprite and a bunch of functions
  to play around with it

Button:
- almost everything you see in the screen is a button, why? because you can click it, thus this class will provide the option of checking
  for clicks AND! letting you know what type of button it is (Type_t) (derives from BaseImg)

ClickButton:
- a tiny class that derives from Button, because its mostly a clickable object it knows when the mouse is above it and draws a simple animation

ToolbarButton:
- this button also derives from Button, the difference here is that we have a member called amount so we know "how many" of this type of
  object we have left.
  (amount -1 is used to state that there is infinite amount)

globals:
- a class with global consts of all kinds used for all kinds of things, mostly every class includes it.
  note that some numbers can be changed changing the behaviour of the game,
  change values at your own risk (some changes could make the game crash or even explode your computer)

GameObj:
- this is the base class for all the objects that can be added to the board, it holds all the shared functions and members like the physicsObj member

physicsObj:
- this is the class that holds the Box2D object, basically a body and a fixture
  it has some functions to for example change the size of the body or apply some impulse nothing too fancy

the rest of the classes are the different game objects, balls, walls and others

The resources folder has all the images, sounds, fonts, and txt files required for the running of the program



The levels.txt file:
--------------------
this levels on the file looks like this template

NAME OF LEVEL
-
LEVEL GOAL
-
boardobject1 xlocation ylocation A B C
boardobject2 xlocation ylocation A B C
...
boardobjectN xlocation ylocation A B C
-
toolbarObject1 amount
toolbarObject2 amount
...
toolbarObjectN amount
-
id1 xlocation ylocation widthheight     //these are location conditions to win 
id2 xlocation ylocation width height    //the id is given to the board object depending on its place int the list
...                                     //the id has to be in the square that is in the location x,y and has the size of width and height
idN xlocation ylocation width height    //x,y is the topLeft corner of the square
-
id1                                     //these are activation conditions to win
id2                                     //the object with the id has to be "activated" to win
...                                     //as for now balloos, engines, conveyors and trampolines can be activated
idN


Contributors:
-------------
- Federico Garber from Argentina donated the original music in the game.
  many thanks!


Algorithms:
-----------
- no algorithms worth mentioning


Known bugs:
-----------
- sometimes when compiling and running on macOS vsCode left click events are not recognized, seems like clicks are being stored on some buffer.
  before compiling go to the ResourceManager.cpp and comment and uncomment the pieces of code non/relevant to your OS.



How to build your own levels (finally! right?):
-----------------------------------------------
- go to the create mode make your level
  go back to the menu and press save
  look for the newLevel.txt file it should be in the build folder or somewhere around
  copy the text into the levels.txt file
  add a name and a goal following the template given a few lines ago
  add objects to the toolbar
  add conditions to win, either specific locations for given objects or ids for activation conditions
  be sure to add at least one condition (doesnt matter which type) because if not as soon as you apply
  gravity the levelController will think you passed the level
  (you can also just build the whole level manually, good luck with that!)

