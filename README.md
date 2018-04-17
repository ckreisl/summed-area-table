# **About**
From [Wiki](https://en.wikipedia.org/wiki/Summed-area_table): A **summed-area table** is a data structure and algorithm for quickly and efficiently generating the sum of values in a rectangular subset of a grid. In the image processing domain, it is also known as an integral image [...].

For a better understanding i implemented this algorithm in C++. The algorithm is separated into two parts:

* [1] Preprocessing step
* [2] Computation step

Both steps with code can be seen blow.

## **Preprocessing step**
```
for(unsigned int y = 0; y < HEIGHT; ++y)
{
    for(unsigned int x = 0; x < WIDTH; ++x)
    {
        value = xs[x][y];
        if(y > 0)
            value += summedAreaTableI[x][y-1];
        if(x > 0)
            value += summedAreaTableI[x-1][y];
        if(x > 0 && y > 0)
            value -= summedAreaTableI[x-1][y-1];
        summedAreaTableI[x][y] = value;
    }
}
```
## **Computing the sum within a rectangle**
```
int A = 0, B = 0, C = 0, D = 0;
if(rectPosX > 0 && rectPosY> 0)
    A = summedAreaTableI[rectPosX-1][rectPosY-1];
if(rectPosY > 0)
    B = summedAreaTableI[rectPosX+rectWidth-1][rectPosY-1];
if(rectPosX > 0)
    C = summedAreaTableI[rectPosX-1][rectPosY+rectHeight-1];

D = summedAreaTableI[rectPosX+rectWidth-1][rectPosY+rectHeight-1];

int sum = A - B - C + D;
```

## **Usage**
Check out my [ArtWork](https://github.com/ckreisl/artwork) repository where i optimized my code by using summed-area tables.
