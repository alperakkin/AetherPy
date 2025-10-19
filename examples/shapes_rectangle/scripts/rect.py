from Aether.scene import CreateGameObject, GetGameObject
from Aether.transform import Vector
from Aether.graphics import Color

player = None

def set_shape(player):
    color = Color(100, 250, 100, 255)
    print(color)


def start():
    CreateGameObject("player")

def setup():
    global player
    player = GetGameObject("player")
    player.position = Vector(1, 1, 0)
    set_shape(player)
    print(player)
