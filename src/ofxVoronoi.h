/*
 *  ofxVoronoi.h
 *
 * \brief This addon allows the generation of simple two-dimensional voronoi diagrams inside openframeworks.
 * It uses a modified version of Stephan Fortune's sweep line algorithm written by Chris H. Rycroft for the Voro++ project.
 *
 * Added support for Lloyd's algorithm useful for relaxing the diagram for use with stippling effects.
 * https://en.wikipedia.org/wiki/Lloyd%27s_algorithm
 *
 * Contributors: Todd Vanderlin, Matthias Esterl, Andreas Borg, Amnon Owed, Rafael Redondo.
 */

#pragma once

#include "ofMain.h"

/// \brief ofxVoronoiCell class defines a Voronoi cell.
struct ofxVoronoiCell {
    std::vector<ofDefaultVec3> points;      ///< The list of points defining the cell bounds.
    ofDefaultVec3 centroid;                 ///< The Voronoi centroid.
};

class ofxVoronoi {
    
public:
    
    ofxVoronoi(){};
    ~ofxVoronoi(){};
    
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
    
    void setBounds(ofPolyline _outline);

    /// \brief setPoints sets a new list of points from which the Voronoi cells will be generated.
    /// Points and cells previously added will be cleared.
    /// \param _points a list of points in std::vector format.
    void setPoints(std::vector<ofDefaultVec3> _points);
    
    /// \brief addPoint adds a single point to the list for generating the Voronoi cells.
    /// \param _point is a single point.
    void addPoint(ofDefaultVec3 _point);
    
    /// \brief addPoints adds a list of points to the list from which the Voronoi cells will be generated.
    /// \param _points is a list of points in std::vector format.
    void addPoints(std::vector<ofDefaultVec3> _points);
    
    /// \brief getBound retrieves the bounds.
    /// \return rectangular bounds.
    ofRectangle getBounds();
    
    /// \brief getPoints retrieves the list of added points.
    /// \return a list of points in std::vector format.
    std::vector<ofDefaultVec3>& getPoints();
    
    /// \brief getCells retrieves the Voronoi cells.
    /// \return a list of Voronoi cells in std::vector format.
    std::vector<ofxVoronoiCell>& getCells();
    
    /// \brief getCell retrieves the cell containing a given point.
    /// \param _point the point.
    /// \param approximate false if point already added, set true and then the closest cell to the point is returned
    /// \return the retrieved cell
    ofxVoronoiCell& getCell(ofDefaultVec3 _point, bool approximate=false);
    
    /// \brief Consult https://en.wikipedia.org/wiki/Lloyd%27s_algorithm
    void relax();
    
private:
    ofPolyline outline;                                ///< Vector shape where Voronoi cells are generated.
    std::vector<ofDefaultVec3> points;                 ///< List of points to generate the Voronoi cells.
    std::vector<ofxVoronoiCell> cells;                 ///< The list of Voronoi cells.
    ofPoint intersection(ofPoint p1, ofPoint p2,
                         ofPoint p3, ofPoint p4);      ///< Auxiliar method for calculating virtual intersection
    ofPoint getNormalised(ofPoint p1, ofPoint p2);     ///< Auxiliar method for normalising vectors
    ofPoint getMidPoint(ofPoint p1, ofPoint p2);       ///< Auxiliar method for calculating mid point
    double getDistance(ofPoint p1, ofPoint p2);        ///< Auxiliar method for distance calculation
    double getDistance(glm::vec3 p1, glm::vec3 p2);    ///< Auxiliar method for distance calculation
    double getRadians(ofPoint p1, ofPoint p2);         ///< Auxiliar method for radians calculation
    double getDegrees(ofPoint p1, ofPoint p2);         ///< Auxiliar method for degrees calculation
    double getPositiveDegrees(ofPoint p1, ofPoint p2); ///< Auxiliar method for degrees calculation
};
