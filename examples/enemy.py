from game import CreateGameObject, Vector

enemy = None

def start():
    global enemy
    enemy = CreateGameObject("Boss")


def setup():
    enemy.position = Vector(2,1,2)




def update():
    enemy.position += Vector(0.0, 5.0, 0.0)




