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
    player.rotation = Vector(1,1,1)


def update():
    player.rotation += Vector(0,0,1)
    print(player, "pos", player.position,"rot", player.rotation)
    print(enemy, "pos", enemy.position,"rot", enemy.rotation)






