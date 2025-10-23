from Aether.scene import CreateGameObject, GetGameObject
from Aether.transform import Vector
from Aether.graphics import Color
from Aether.graphics import Rectangle, Circle

player = None
enemy = None

def create_rect():
    color = Color(100, 250, 100, 255)
    size = Vector(10, 10, 0)
    rect = Rectangle(size=size, color=color)
    return rect

def create_circle():
    try:
        color = Color(200, 250, 0, 255)
        size = Vector(30, 0, 0)
        circle = Circle(size=size, color=color)
        return circle
    except Exception as e:
        print("Err:",e)


def start():
    global player, enemy
    CreateGameObject("player")
    CreateGameObject("enemy")
    player = GetGameObject("player")
    enemy = GetGameObject("enemy")
    enemy.position = Vector(600,50,0)


def setup():
    global player
    rect = create_rect()
    circle = create_circle()
    player.shape = rect
    player.position = Vector(10, 10, 0)
    enemy.shape = circle

def update():
    player.position.y += 1
    enemy.position.x -= 1

