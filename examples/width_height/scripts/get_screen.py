from Aether.scene import CreateGameObject, GetGameObject, WIDTH, HEIGHT
from Aether.transform import Vector
from Aether.graphics import Color
from Aether.graphics import Rectangle



player = None


def start():
    CreateGameObject("player")


def setup():
    global player
    player = GetGameObject("player")

    rect =  Rectangle(
        size=Vector(10,10,0),
        color=Color(255,0,0,255)
    )
    player.shape = rect
    print(WIDTH, HEIGHT)
    player.position = Vector(WIDTH/2, HEIGHT/2, 0)





def update():
    pass


