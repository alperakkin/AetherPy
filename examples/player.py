from game import CreateGameObject, GetGameObject

player = None
enemy = None

def start():
    global player
    player = CreateGameObject("Player")

def setup():
    global enemy
    enemy = GetGameObject('Boss')


def update():
    print("[Python] player:",player.position)
    print("[Python] enemy:",enemy.position)





