from Aether.scene import CreateGameObject, GetGameObject
from Aether.transform import Vector
from Aether.graphics import Color, Text
from Aether.graphics import Rectangle

player = None
finish = None
gameover = None

def start():
    CreateGameObject("finish")
    CreateGameObject("gameover")

def setup():
    global player, finish, gameover
    finish = GetGameObject("finish")
    player = GetGameObject("player")
    gameover = GetGameObject("gameover")
    finish.shape = Rectangle(
        size=Vector(5,100,0),
        color=Color(255,0,0,255)
    )
    finish.position = Vector(300,100,0)
    gameover.position = Vector(200,200,0)

def update():
    if player.position.x >= finish.position.x:
        gameover.shape = Text(text="Game Over",
                   size=Vector(50, 0, 0),
                    color=Color(0, 255, 0, 255))

        player.position.x = 0
