from Aether.scene import CreateGameObject, GetGameObject
from Aether.transform import Vector
from Aether.graphics import Color
from Aether.graphics import Rectangle
from Aether.controls import InputControl, POS_X, POS_Y
player = None



def create_rect():
    color = Color(100, 250, 100, 255)
    size = Vector(10, 10, 0)
    rect = Rectangle(size=size, color=color)
    return rect


def define_controls(player):
    control_dict = {
        "w": {"on": POS_Y, "delta":-1},
        "a": {"on": POS_X, "delta":-1},
        "s": {"on": POS_Y, "delta":1},
        "d": {"on": POS_X, "delta":1},
    }
    InputControl(object=player, ctrl=control_dict)


def start():
    CreateGameObject("player")

def setup():

    global player
    player = GetGameObject("player")
    rect = create_rect()
    player.shape = rect
    player.position = Vector(10, 10, 0)
    define_controls(player)



def update():
    player.position.x += 0.1


