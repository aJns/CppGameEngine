import sys

sys.path.append('/home/nikulaj/projects/GameEngine/build')
print(sys.path)

import libGameEngine

def test():
    print("Teest")
    print("Hello woooorrldd")

    # libGameEngine.createVector(0,0,0)
    libGameEngine.testFunc()

test()
