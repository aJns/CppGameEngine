import sys

sys.path.append('/home/nikulaj/projects/GameEngine/build/lib')

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

        x = random.uniform(-1,1)
        y = random.uniform(-1,1)
        z = random.uniform(-1,1)
        radAngle = libGameEngine.Rad(0.01)
        rotVector = libGameEngine.Vector3(x, y, z).normalized()
        self.quaternion = libGameEngine.Quaternion.rotation(radAngle,
                                                            rotVector)

        self.counter = 0

    def foo(self):
        if(self.counter > 50):
            x = random.uniform(-1,1)
            y = random.uniform(-1,1)
            z = random.uniform(-1,1)
            self.vector = libGameEngine.Vector3(x, y, z)
            radAngle = libGameEngine.Rad(0.01)
            rotVector = libGameEngine.Vector3(x, y, z).normalized()
            self.quaternion = libGameEngine.Quaternion.rotation(radAngle,
                                                                rotVector)
            self.counter = 0
        self.gameObject.moveTo(self.vector)
        self.gameObject.rotate(self.quaternion)
        self.counter += 1
