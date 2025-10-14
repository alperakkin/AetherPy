from game import CreateGameObject, Vector

enemy = None

def start():
    global enemy
    enemy = CreateGameObject("Boss")


def setup():
    enemy.position = Vector(2.0, 1.1, 1.2)



def update():
    enemy.position.x += 0.5


