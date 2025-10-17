from Aether.scene import CreateGameObject,GetGameObject
from Aether.transform import Vector

player = None
enemy = None


def start():
    global player
    player = CreateGameObject("Player")

def setup():
    global enemy
    enemy = GetGameObject("Boss")
    player.position = Vector(1,1,1)


def update():
    print("Player", player.position)
    print("Enemy", enemy.position)
    player.position += Vector(0,0,1)

