import sys

sys.path.append('/home/nikulaj/projects/GameEngine/build')

import libGameEngine

import random

def test(gameObject):
    x = random.uniform(-1,1)
    y = random.uniform(-1,1)
    z = random.uniform(-1,1)
    gameObject.translate(libGameEngine.Vector3(x, y, z))
