#pragma once

#include "ofMain.h"

/// \brief ofxVoronoiCell class defines a Voronoi cell.
class ofxVoronoiCell {
  public:
    vector<ofPoint> pts;    ///< The list of points defining the cell bounds.
    ofPoint pt;             ///< The Voronoi centroid.
};

class ofxVoronoi {
    
public:
    
    ofxVoronoi();
    ~ofxVoronoi();
    
    /// \brief clear deletes cells and points
    void clear();
    
    /// \brief generate Voronoi's cells once a list of points have been added
    /// \param ordered lets cells have same order as points.
    void generate(bool ordered=true);
    
    /// \brief draw displays voronoi's cells and centroids.
    void draw();
    
    /// \brief setBounds sets Voronoi outer limits
    /// \params _bounds rectangular boundary.
    void setBounds(ofRectangle _bounds);
    
    /// \brief setPoints sets a new list of points from which the Voronoi cells will be generated.
    /// Points and cells previously added will be cleared.
    /// \param _points a list of points in vector format.
    void setPoints(vector<ofPoint> _points);
    
    /// \brief addPoint adds a single point to the list for generating the Voronoi cells.
    /// \param _point is a single point.
    void addPoint(ofPoint _point);
    
    /// \brief addPoints adds a list of points to the list from which the Voronoi cells will be generated.
    /// \param _points is a list of points in vector format.
    void addPoints(vector<ofPoint> _points);
    
    /// \brief getBound retrieces the bounds.
    /// \return rectangular bounds.
    ofRectangle getBounds();
    
    /// \brief getPoints retrieves the list of added points.
    /// \return a list of points in vector format.
    vector<ofPoint>& getPoints();
    
    /// \brief getCells retrieves the Voronoi cells.
    /// \return a list of Voronoi cells in vector format.
    vector <ofxVoronoiCell>& getCells();
    
    /// \brief getCell retrieves the cell containing a given point.
    /// \param _point the point.
    /// \param approximate false if point already added, set true and then the closest cell to the point is returned
    /// \return the retrieved cell
    ofxVoronoiCell& getCell(ofPoint _point, bool approximate=false);
    
    /// \brief Consult https://en.wikipedia.org/wiki/Lloyd%27s_algorithm
    void relax();
    
private:
    
    ofRectangle bounds;             ///< rectangular bound where Voronoi cells are generated.
    vector<ofPoint> points;         ///< List of points to generate the Voronoi cells.
    vector<ofxVoronoiCell> cells;   ///< The list of Voronoi cells.
};
