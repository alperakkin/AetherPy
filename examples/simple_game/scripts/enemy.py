from Aether.scene import CreateGameObject
from Aether.transform import Vector


enemy = None

def start():
    global enemy
    enemy = CreateGameObject("Boss")


def setup():
    enemy.position = Vector(5,5,5)


def update():
    enemy.position.x += 2
