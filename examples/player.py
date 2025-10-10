from game import CreateGameObject, GetGameObject

player = None


def setup():
    global player
    player = CreateGameObject("Player")


def update():
    print("[Python] player:",player)
    enemy = GetGameObject('Boss')
    print("[Python] player:",enemy)


