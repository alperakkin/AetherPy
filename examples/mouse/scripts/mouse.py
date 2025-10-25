from Aether.scene import CreateGameObject, GetGameObject
from Aether.transform import Vector
from Aether.graphics import Color
from Aether.graphics import Rectangle
from Aether.controls import (InputControl,
                             MOUSE,
                             MOUSE_MOVE, MOUSE_CLICK,
                             POS_ALL, POS_X)
player = None



def create_rect():
    color = Color(100, 250, 100, 255)
    size = Vector(10, 10, 0)
    rect = Rectangle(size=size, color=color)
    return rect


def define_controls(player):
    control_dict = {
        MOUSE_MOVE: {"on": POS_ALL, "delta":0},
        MOUSE_CLICK: {"on": POS_X, "delta":1},
    }
    InputControl(object=player, ctrl=control_dict, ctrl_type=MOUSE)


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


