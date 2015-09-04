import sys

sys.path.append('/home/nikulaj/projects/GameEngine/build')

import libGameEngine

import random

def test(gameObject):
    return testClass(gameObject)

class testClass:
    def __init__(self, gameObject):
        self.gameObject = gameObject
        x = random.uniform(-1,1)
        y = random.uniform(-1,1)
        z = random.uniform(-1,1)
        self.vector = libGameEngine.Vector3(x, y, z)
    def foo(self):
        self.gameObject.translate(self.vector)
