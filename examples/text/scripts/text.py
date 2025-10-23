from Aether.scene import CreateGameObject, GetGameObject
from Aether.transform import Vector
from Aether.graphics import Color
from Aether.graphics import Rectangle, Text

player = None
text = None



def create_rect():
    color = Color(100, 250, 100, 255)
    size = Vector(10, 10, 0)
    rect = Rectangle(size=size, color=color)
    return rect





def start():
    try:
        global player, text
        CreateGameObject("player")
        CreateGameObject("text")
        player = GetGameObject("player")
        text = GetGameObject("text")
    except Exception as e:
        print("start",e)


def setup():
    try:
        global player,text
        rect = create_rect()
        player.shape = rect
        player.position = Vector(10, 10, 0)
        txt = Text(text="Hello Aether",
                   size=Vector(30, 0, 0),
                    color=Color(0, 0, 100, 255))
        text.shape = txt
        text.position = Vector(200,200,0)
    except Exception as e:
        print("setup",e)


def update():
    player.position.y += 1


