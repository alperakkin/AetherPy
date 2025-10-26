from Aether.scene import CreateGameObject, GetGameObject
from Aether.transform import Vector
from Aether.graphics import Color
from Aether.graphics import Circle
from Aether.controls import InputControl, POS_X, POS_Y, KEYBOARD
from Aether.controls.inputs import W,A,S,D
player = None
finish = None



def create_shape():
    color = Color(100, 250, 100, 255)
    size = Vector(10, 10, 0)
    rect = Circle(size=size, color=color)
    return rect


def define_controls(player):
    control_dict = {
        W: {"on": POS_Y, "delta":-1},
        A: {"on": POS_X, "delta":-1},
        S: {"on": POS_Y, "delta":1},
        D: {"on": POS_X, "delta":0.5},
    }
    InputControl(object=player, ctrl=control_dict, ctrl_type=KEYBOARD)


def start():
    CreateGameObject("player")

def setup():

    global player, finish
    player = GetGameObject("player")
    finish = GetGameObject("finish")
    c = create_shape()
    player.shape = c
    player.position = Vector(10, 10, 0)
    define_controls(player)



def update():
    if player.position.x > 0 and player.position.x < finish.position.x:
        player.position.x -= .1


