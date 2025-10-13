from game import CreateGameObject, GetGameObject

player = None
enemy = None

def setup():
    global player
    player = CreateGameObject("Player")


def update():
    global enemy
    if not enemy:
        enemy = GetGameObject('Boss')

    print("[Python] player:",player.position)
    print("[Python] enemy:",enemy.position)





