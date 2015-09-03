import sys

sys.path.append('/home/nikulaj/projects/GameEngine/build')

import libGameEngine

import random

def test(gameObject):
    return testClass(gameObject)

class testClass:
    def __init__(self, gameObject):
        self.gameObject = gameObject
        self.x = random.uniform(-1,1)
        self.y = random.uniform(-1,1)
        self.z = random.uniform(-1,1)
    def foo(self):
        self.gameObject.translate(libGameEngine.Vector3(self.x, self.y, self.z))
