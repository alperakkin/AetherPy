from game import CreateGameObject, GetGameObject

player = None


def setup():
    global player
    player = CreateGameObject("Player")


def update():
    enemy = GetGameObject('Boss')
    try:
        print("[Python] player:",player.position)
        print("[Python] enemy:",enemy.position)
    except Exception as e:
        print(e)




