import sys

sys.path.append('/home/nikulaj/projects/GameEngine/build')

import libGameEngine

def test(gameObject):
    gameObject.translate(libGameEngine.Vector3(0, 0, -1))
