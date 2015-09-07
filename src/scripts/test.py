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
        x = 0
        y = 0
        z = 0
        self.vector = libGameEngine.Vector3(x, y, z)
        x = random.uniform(-1,1)
        y = random.uniform(-1,1)
        z = random.uniform(-1,1)
        radAngle = 0.01
        rotVector = libGameEngine.Vector3(x, y, z)
        rotVector.normalize()
        self.quaternion = libGameEngine.Quaternion(rotVector, radAngle)

        self.counter = 0

    def foo(self):
        print(self.counter)
        if(self.counter > 150):
            quat = libGameEngine.Quaternion()
            self.gameObject.setOrientation(quat)
            self.counter = 0
        self.gameObject.translate(self.vector)
        self.gameObject.rotate(self.quaternion)
        self.counter += 1
