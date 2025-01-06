import sys
sys.path.append("../build")
import pybytetrack as pybt
tracker = pybt.ByteTracker()

for i in range(20):
    objects = [pybt.Object(prob=0.9, label=0, rect=pybt.Rect(100+i*10, 100, 50, 50)),
        pybt.Object(prob=0.85, label=1, rect=pybt.Rect(150, 150+i*10, 40, 40))]
    tracks = tracker.update(objects)
    print(tracks)

