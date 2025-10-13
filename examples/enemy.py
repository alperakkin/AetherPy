from game import CreateGameObject

enemy = None

def start():
    global enemy
    enemy = CreateGameObject("Boss")


def setup():
    enemy.position.y = 12




def update():
    enemy.position.x += 5


