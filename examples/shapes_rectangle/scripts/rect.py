from Aether.scene import CreateGameObject, GetGameObject
from Aether.transform import Vector
from Aether.graphics import Color
from Aether.graphics import Rectangle

player = None

def create_rect():
    color = Color(100, 250, 100, 255)
    size = Vector(10, 10, 0)
    rect = Rectangle(size=size, color=color)
    return rect


def start():
    global player
    CreateGameObject("player")
    player = GetGameObject("player")


def setup():
    rect = create_rect()
    player.shape = rect
    player.position = Vector(10, 10, 0)

def update():
    print(player.shape)
