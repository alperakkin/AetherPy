from game import CreateGameObject

player = None


def setup():
    global player
    player = CreateGameObject("Player")


def update():
    print(f"[Python] player: {player}")
