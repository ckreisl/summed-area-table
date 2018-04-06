#include <iostream>
#include <vector>
#include <chrono>
#include <assert.h>

using namespace std;

int main()
{
    /* WIDTH and HEIGHT of our summed-area table,
     * mostly used in image processing
     * (ex. computing the mean of a rectangle) */
    unsigned int WIDTH = 3;
    unsigned int HEIGHT = 3;
    assert((WIDTH > 0) && (HEIGHT > 0));

    /* create pseudo 2D array / vector for computing a summed-area table */
    vector <vector<int> > xs;
    xs.resize(WIDTH);
    for(unsigned int i = 0; i < WIDTH; ++i)
        xs[i].resize(HEIGHT);

    assert(xs.size() == WIDTH);
    assert(xs[0].size() == HEIGHT);

    /* fill array / vector with dump values */
    int counter = 1;
    for(unsigned int y = 0; y < HEIGHT; ++y)
        for(unsigned int x = 0; x < WIDTH; ++x)
            xs[x][y] = counter++;

    /* unsigned int summed-area table,
     * (be aware of arithmetic overflow by using summed-area tables)
     *
     * int:             -2.147.483.648 till +2.147.483.647 (4 Byte, 32 Bits)
     * unsigned int:    0              till 4.294.967.295  (4 Byte, 32 Bits)
     * ...              ...                 ...             ...
     *
     * (https://www.tutorialspoint.com/cplusplus/cpp_data_types.htm)
     *
     **/
    vector< vector<unsigned int> > summedAreaTableI;

    /* if a summed-area table which is defined as an vector in a header file,
     * we can set the corresponding vector size like this in our source file constructor */
    summedAreaTableI.resize(WIDTH);
    for(unsigned int i = 0; i < WIDTH; ++i)
        summedAreaTableI[i].resize(HEIGHT);

    /* preprocess filling our summed-area table */
    int value = 0;
    for(unsigned int y = 0; y < HEIGHT; ++y) {
        for(unsigned int x = 0; x < WIDTH; ++x) {
            /* get value from array / vector */
            value = xs[x][y];
            /* compute summed-area table value, avoid out of bounce access */
            if(y > 0)
                value += summedAreaTableI[x][y-1];
            if(x > 0)
                value += summedAreaTableI[x-1][y];
            if(x > 0 && y > 0)
                value -= summedAreaTableI[x-1][y-1];
            /* save computed value in summed-area table */
            summedAreaTableI[x][y] = value;
        }
    }

    /* how to use our generated summed-area table,
     * now it is easy to compute a sum of any rectangle size in
     * O(1) instead of O(rec_width*rec_height) */

    /* since we maybe want to use this summed-area table within an image we set dummy pixels positions x and y */
    unsigned int imagePosX = 0;
    unsigned int imagePosY = 0;

    assert(imagePosX < WIDTH);
    assert(imagePosY < HEIGHT);

    /* our rectangle is defined with the upper left point and its width and height */
    unsigned int rectWidth = WIDTH;         // care boundings (rectWidth <= WIDTH)
    unsigned int rectHeight = HEIGHT;       // care boundings (rectHeight <= HEIGHT)
    unsigned int rectPosX = imagePosX;      // set imagePosX and imagePosY as rectangle starting point
    unsigned int rectPosY = imagePosY;

    assert((rectWidth <= WIDTH) && (rectPosX < WIDTH));
    assert((rectHeight <= HEIGHT) && (rectPosY < HEIGHT));


    /* From Wiki: https://en.wikipedia.org/wiki/Summed-area_table
     * get each corner value of our rectangle */
    int A = 0, B = 0, C = 0, D = 0;

    /* get correct values from summed-area table,
     * (take care about out of bounce errors) */
    if(rectPosX > 0 && rectPosY> 0)
        A = summedAreaTableI[rectPosX-1][rectPosY-1];
    if(imagePosY > 0)
        B = summedAreaTableI[rectPosX+rectWidth-1][rectPosY-1];
    if(imagePosX > 0)
        C = summedAreaTableI[rectPosX-1][rectPosY+rectHeight-1];

    D = summedAreaTableI[rectPosX+rectWidth-1][rectPosY+rectHeight-1];

    int sum = A - B - C + D;

    /* check against native way in O(rectWidth * rectHeight) */
    int sumNative = 0;
    for(unsigned int y = rectPosY; y < rectWidth; ++y) {
        for(unsigned int x = rectPosX; x < rectHeight; ++x) {
            sumNative += xs[x][y];
        }
    }

    assert(sum == sumNative);
    cout << "Final sum of rectangle: " << sum << endl;
    cout << "Slow way sum of rectangle: " << sumNative << endl;

    return 0;
}
