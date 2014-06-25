# ofxVoronoi

This repo started as a fork of Vanderlins [ofxVoronoi](https://github.com/vanderlin/ofxVoronoi), but I ended up changing to much code so I decided to it make an independent addon.

This addon allows the generation of simple two-dimensional voronoi diagrams inside openframeworks. It uses a modified version of [Stephan Fortune's sweep line algorithm](http://ect.bell-labs.com/who/sjf/) written by Chris H. Rycroft for the [Voro++ project](http://math.lbl.gov/voro++/).

![Basic Example](https://github.com/madc/ofxVoronoi/raw/master/ofxVoronoi_Screenshot.png)

## Todo:

- Edge-Detection
- Clean method to draw diagram (without closing paths)
