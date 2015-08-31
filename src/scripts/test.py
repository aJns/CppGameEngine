import sys

sys.path.append('/home/nikulaj/projects/GameEngine/build')

import libGameEngine

def test(gameObject):
    print("Teest")
    print("Hello woooorrldd")

    # libGameEngine.createVector(0,0,0)

    gameObject.translate(libGameEngine.Vector3(-1, 0, 0))
    libGameEngine.testFunc()
