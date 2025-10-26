from Aether.scene import CreateGameObject, GetGameObject
from Aether.transform import Vector
from Aether.graphics import Color
from Aether.graphics import Rectangle, Text

player = None
msg = None
text = None




def start():
    CreateGameObject("player")
    CreateGameObject("msg")

def setup():
    global player, msg, text
    player = GetGameObject("player")
    msg = GetGameObject("msg")

    rect =  Rectangle(
        size=Vector(10,10,0),
        color=Color(255,0,0,255)
    )
    player.shape = rect
    player.position = Vector(10, 10, 0)
    text = Text(
           text="Game Paused",
           size=Vector(50,0,0),
        color=Color(255,0,0,255)
    )
    msg.position = Vector(200,100,0)




def update():
    player.position.x += 0.1
    if player.position.x >= 50:
        msg.shape = text
        PAUSE = True


