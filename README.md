# ofxVoronoi

![ofxAddons Thumbnail](https://raw.githubusercontent.com/madc/ofxVoronoi/master/ofxaddons_thumbnail.png)

This repo started as a fork of Vanderlins [ofxVoronoi](https://github.com/vanderlin/ofxVoronoi), but I ended up changing too much code and decided to make it an independent addon.

This addon allows the generation of simple two-dimensional voronoi diagrams inside openframeworks. It uses a modified version of [Stephan Fortune's sweep line algorithm](http://ect.bell-labs.com/who/sjf/) written by Chris H. Rycroft for the [Voro++ project](http://math.lbl.gov/voro++/).

![Basic Example](https://github.com/madc/ofxVoronoi/raw/master/ofxVoronoi_Screenshot.png)


Borg update:
Added support for [Lloyd's algorithm](https://en.wikipedia.org/wiki/Lloyd%27s_algorithm) useful for relaxing the diagram for use with stippling effects.

Example:  
Create as usual
```
ofxVoronoi relaxedVoronoi;
relaxedVoronoi.setBounds(bounds);
relaxedVoronoi.setPoints(points);
relaxedVoronoi.generate();

int relaxIterations = 3;
while(relaxIterations--){
	relaxedVoronoi.relax();
}
```

