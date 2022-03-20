/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */

//#include "filler.h"

/**
 * Performs a multi-point flood fill using breadth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillBFS(FillerConfig &config) {
    return filler::fill<Queue>(config);
}

/**
 * Performs a multi-point flood fill using depth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillDFS(FillerConfig &config) {
    return filler::fill<Stack>(config);
}

inline bool
filler::validCoordinates(unsigned int x, unsigned int y, unsigned int imageWidth, unsigned int imageHeight) {
    return x >= 0 && x < imageWidth && y >= 0 && y < imageHeight;
}

inline bool filler::withinToleranceDistance(HSLAPixel pixel, float tolerance, centre centre) {
    return pixel.dist(centre.color) <= tolerance;
}

/**
 * Run a multi-point flood fill on an image
 *
 * @param  config     FillerConfig struct with data for flood fill of image
 * @return animation  object illustrating progression of flood fill algorithm
 */
template<template<class T> class OrderingStructure>
animation filler::fill(FillerConfig &config) {
    animation animation;
    OrderingStructure<point> pointContainer;
    unsigned int width = config.img.width();
    unsigned int height = config.img.height();
    vector <vector<bool>> visitedNodes(width, vector<bool>(height));
    int frameCount = 500;

    if (width > 0 && height > 0) {
        for (auto i = visitedNodes.begin(); i < visitedNodes.end(); i++) {
            for (auto j = i->begin(); j < i->end(); j++) {
                *j = false;
            }
        }
        for (unsigned int i = 0; i < config.centres.size(); i++) {
            centre centre = config.centres[i];
            ColorPicker *picker = config.pickers[i];
            pointContainer.add(point(centre));

            while (!pointContainer.isEmpty()) {
                point p = pointContainer.remove();

                // UP(-y), RIGHT(+x), LEFT(-x), DOWN(+y)
                int left = (int) p.x - 1;
                int right = (int) p.x + 1;
                int up = (int) p.y - 1;
                int down = (int) p.y + 1;

                vector <point> surroundingPixels{
                        point((int) p.x, up, centre),
                        point(right, (int) p.y, centre),
                        point(left, (int) p.y, centre),
                        point((int) p.x, down, centre)
                };

                for (unsigned long j = 0; j < surroundingPixels.size(); ++j) {
                    point currentPoint = surroundingPixels.at(j);
                    unsigned int pxCoordinate = currentPoint.x;
                    unsigned int pyCoordinate = currentPoint.y;

                    if (validCoordinates(pxCoordinate, pyCoordinate, width, height)) {
                        if (!visitedNodes[currentPoint.x][currentPoint.y]) {
                            HSLAPixel *currentPx = config.img.getPixel(currentPoint.x, currentPoint.y);

                            if (withinToleranceDistance(*currentPx, config.tolerance, centre)) {
                                visitedNodes[currentPoint.x][currentPoint.y] = true;
                                pointContainer.add(currentPoint);

                                *currentPx = picker->operator()(currentPoint);
                                if (config.frameFreq % ++frameCount == 0) {
                                    animation.addFrame(config.img);
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        return animation;
    }
    animation.addFrame(config.img);
    return animation;
}
















/**
 * @todo You need to implement this function!
 *
 * This is the basic description of a flood-fill algorithm: Every fill
 * algorithm requires an ordering structure, which is passed to this
 * function via its template parameter. For a breadth-first-search
 * fill, that structure is a Queue, for a depth-first-search, that
 * structure is a Stack. To begin the algorithm, you simply place the
 * given point in the ordering structure, marking it processed
 * (the way you mark it is a design decision you'll make yourself).
 * We have a choice to either change the color, if appropriate, when we
 * add the point to the OS, or when we take it off. In our test cases,
 * we have assumed that you will change the color when a point is added
 * to the structure.
 * Until the structure is empty, you do the following:
 *
 * 1.     Remove a point from the ordering structure, and then...
 *
 *        1.    add its unprocessed neighbors whose color values are
 *              within (or equal to) tolerance distance from the center,
 *              to the ordering structure, and
 *              mark them as processed.
 *        2.    if it is an appropriate frame, send the current PNG to the
 *              animation (as described below).
 *
 * 2.     When implementing your breadth-first-search and
 *        depth-first-search fills, you will need to explore neighboring
 *        pixels in some order.
 *
 *        While the order in which you examine neighbors does not matter
 *        for a proper fill, you must use the same order as we do for
 *        your animations to come out like ours! The order you should put
 *        neighboring pixels **ONTO** the queue or stack is as follows:
 *        ** UP(-y), RIGHT(+x), DOWN(+y), LEFT(-x). IMPORTANT NOTE: *UP*
 *        here means towards the top of the image, so since an image has
 *        smaller y coordinates at the top, this is in the *negative y*
 *        direction. Similarly, *DOWN* means in the *positive y*
 *        direction.** To reiterate, when you are exploring (filling out)
 *        from a given pixel, you must first try to fill the pixel UP
 *        from it, then the one to its RIGHT, then DOWN from it and
 *        finally to its LEFT. If you do them in a different order, your fill may
 *        still work correctly, but your animations will be different
 *        from the grading scripts!
 *
 *        Because we are doing a multi-point flood fill you will repeat the flood
 *        fill from several locations stored in the `centres` variable of FillerConfig
 *        struct. Initial fill points should be visited in the order they stored in the
 *        `centres` vector. If a pixel lies in the fill region of multiple start points,
 *        it should only be updated by the first fill. To repeat, pixels should only
 *        be modified the first time they are visited by the filler algorithm.
 *
 * 3.     For every k pixels filled, **starting at the kth pixel**, you
 *        must add a frame to the animation, where k = frameFreq.
 *
 *        For example, if frameFreq is 4, then after the 4th pixel has
 *        been filled you should add a frame to the animation, then again
 *        after the 8th pixel, etc.  You must only add frames for the
 *        number of pixels that have been filled, not the number that
 *        have been checked. So if frameFreq is set to 1, a pixel should
 *        be filled every frame.
 *
 * 4.     Finally, as you leave the function, send one last frame to the
 *        animation. This frame will be the final result of the fill, and
 *        it will be the one we test against.
 *
 */

