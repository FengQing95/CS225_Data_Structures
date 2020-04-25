/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    MosaicCanvas * res = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> myPoints;
    map<Point<3>, size_t> point2ind;

    for (size_t i = 0; i < theTiles.size(); i++) {
      LUVAPixel cur = theTiles[i].getAverageColor();

      point2ind.insert(pair<Point<3>, size_t>(convertToXYZ(cur), i));
      myPoints.push_back(convertToXYZ(cur));
    }

    KDTree<3> * myTree = new KDTree<3>(myPoints);
    for (int i = 0; i < theSource.getRows(); i++) {
      for (int j = 0; j < theSource.getColumns(); j++) {
        LUVAPixel regionColor = theSource.getRegionColor(i, j);

        Point<3> newPoint = myTree->findNearestNeighbor(convertToXYZ(regionColor));
        size_t newInd = point2ind[newPoint];

        res->setTile(i, j, & theTiles.at(newInd));
      }
    }

    delete myTree;
    return res;
}
