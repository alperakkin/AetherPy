from Aether import CreateGameObject

enemy = None

def start():

    global enemy
    enemy = CreateGameObject("Boss")



def update():
    print(enemy)