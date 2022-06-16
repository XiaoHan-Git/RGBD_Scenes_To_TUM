## Convert RGB-D Scenes dataset v2 to TUM RGB-D format

[The RGB-D Scenes Dataset v2](https://rgbd-dataset.cs.washington.edu/dataset/rgbd-scenes-v2/) consists of 14 scenes containing furniture  (chair, coffee table, sofa, table) and a subset of the objects in the  RGB-D Object Dataset (bowls, caps, cereal boxes, coffee mugs, and soda  cans). Each scene is a point cloud created by aligning a set of video  frames using Patch Volumes Mapping*.

However, the original file is not in TUM RGB-D format, which is not convenient for ORB-SLAM2 to use. This script converts its format.

## Building

```c++
mkdir build
cd build 
cmake ..
make
```

## Example

Organize the original file as follows：

```
path/
		   -scene_01
		   -01.pose
```

then run the ConvertRGBD:

```
build/ConvertRGBD  path  01(number)
```

The results are as follows:

```
path/
		   -scene_01            (01 is the sequence number)
		   -01.pose
		   depth/
		   rgb/
		   associations.txt
		   depth.txt
		   rgb.txt
		   groundtruth.txt
```

## Note

Since the original file has no explicit timestamp, the converted timestamp is the frame interval (50ms), which can be modified.