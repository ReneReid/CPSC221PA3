
#include "stats.h"

/// @todo add 3 additional vectors to be initialized (sum and sum square); 

stats::stats(PNG & im){

    sumRed.resize(im.height());
    for (unsigned int i = 0; i < im.height(); i++) {
        sumRed[i].resize(im.width());
    }
    sumGreen.resize(im.height());
    for (unsigned int i = 0; i < im.height(); i++) {
        sumGreen[i].resize(im.width());
    }
    sumBlue.resize(im.height());
    for (unsigned int i = 0; i < im.height(); i++) {
        sumBlue[i].resize(im.width());
    }
    sumsqRed.resize(im.height());
    for (unsigned int i = 0; i < im.height(); i++) {
        sumsqRed[i].resize(im.width());
    }
    sumsqGreen.resize(im.height());
    for (unsigned int i = 0; i < im.height(); i++) {
        sumsqGreen[i].resize(im.width());
    }
    sumsqBlue.resize(im.height());
    for (unsigned int i = 0; i < im.height(); i++) {
        sumsqBlue[i].resize(im.width());
    }

    for (unsigned y = 0; y < im.height(); y ++) {
        for (unsigned x = 0; x < im.width(); x++) {
            RGBAPixel *pixel = im.getPixel(x, y);
            if (y == 0) {

                if (x == 0) {
                    //std::cout << sumRed.capacity() << std::endl;
                    sumRed[y][x] = (pixel -> r);
                    //std::cout << "SumRed at (0,0): " << sumRed[y][x] << std::endl;
                    sumGreen[y][x] = (pixel -> g); 
                    //std::cout << "SumGreen at (0,0): " << sumGreen[y][x] << std::endl;
                    sumBlue[y][x] = (pixel -> b);
                    //std::cout << "SumBlue at (0,0): " << sumBlue[y][x] << std::endl;
                    sumsqRed[y][x] = pow((pixel -> r), 2); 
                    sumsqGreen[y][x] = pow((pixel -> g), 2);
                    sumsqBlue[y][x] = pow((pixel -> b), 2); 
                    //std::cout << "RR says: reached line 47" << std::endl;
                
                } 
                //std::cout << "RR says: reached line 50" << std::endl;
                if (x > 0) {
                
                    //std::cout << "RR says: reached line 53" << std::endl;
                    sumRed[y][x] = sumRed[y][x-1] + (pixel -> r);
                    //std::cout << "SumRed at (1,0): " << sumRed[y][x] << std::endl;
                    sumGreen[y][x] = sumGreen[y][x-1] + (pixel -> g);
                    //std::cout << "SumGreen at (1,0): " << sumGreen[y][x] << std::endl;
                    sumBlue[y][x] = sumBlue[y][x-1] + (pixel -> b);
                    //std::cout << "SumBlue at (1,0): " << sumBlue[y][x] << std::endl;
                    sumsqRed[y][x] = sumsqRed[y][x-1] + pow((pixel -> r), 2);
                    sumsqGreen[y][x] = sumsqGreen[y][x-1] + pow((pixel -> g), 2);
                    sumsqBlue[y][x] = sumsqBlue[y][x-1] + pow((pixel -> b), 2); 
                    //std::cout << "RR says: reached line 60" << std::endl;
                }
            } if (x == 0 && y != 0)  { 


                //std::cout << "RR says: reached line 65" << std::endl;
                sumRed[y][x] = sumRed[y-1][x] + (pixel -> r);
                //std::cout << "SumRed at (0,1): " << sumRed[y][x] << std::endl;
                sumGreen[y][x] = sumGreen[y-1][x] + (pixel -> g);
                //std::cout << "SumGreen at (0,1): " << sumGreen[y][x] << std::endl;
                sumBlue[y][x] = sumBlue[y-1][x] + (pixel -> b);
                //std::cout << "SumBlue at (0,1): " << sumBlue[y][x] << std::endl;
                sumsqRed[y][x] = sumsqRed[y-1][x] + pow((pixel -> r), 2); 
                sumsqGreen[y][x] = sumsqGreen[y-1][x] + pow((pixel -> g), 2);
                sumsqBlue[y][x] = sumsqBlue[y-1][x] + pow((pixel -> b), 2);
                //std::cout << "RR says: reached line 72" << std::endl;
                
            } if (x != 0 && y != 0) {
                //std::cout << "RR says: reached line 75" << std::endl;

                sumRed[y][x] = sumRed[y-1][x] + sumRed[y][x-1] - sumRed[y-1][x-1] + (pixel -> r);
                //std::cout << "SumRed at (1,1): " << sumRed[y][x] << std::endl;
                sumGreen[y][x] = sumGreen[y-1][x] + sumGreen[y][x-1] - sumGreen[y-1][x-1] + (pixel -> g);
                //std::cout << "SumGreen at (1,1): " << sumGreen[y][x] << std::endl;
                sumBlue[y][x] = sumBlue[y-1][x] + sumBlue[y][x-1] - sumBlue[y-1][x-1] + (pixel -> b);
                //std::cout << "SumBlue at (1,1): " << sumBlue[y][x] << std::endl;
                sumsqRed[y][x] = sumsqRed[y-1][x] + sumsqRed[y][x-1] - sumsqRed[y-1][x-1] + pow((pixel -> r), 2); 
                sumsqGreen[y][x] = sumsqGreen[y-1][x] + sumsqGreen[y][x-1] - sumsqGreen[y-1][x-1] + pow((pixel -> g), 2);
                sumsqBlue[y][x] = sumsqBlue[y-1][x] + sumsqBlue[y][x-1] - sumsqBlue[y-1][x-1] + pow((pixel -> b), 2); 
                //std::cout << "RR says: reached line 83" << std::endl;
            }
        }
    }



/* Your code here!! */

}


// calculates the sum (for each color channel) for a square
// whose position is by ul value and size by 2^dim.  
// refer to diagram for visual explanation (ask Rene)
long stats::getSum(char channel, pair<int,int> ul, int dim){
    long sum = 0;


    if (ul.first == 0 && ul.second == 0) {

        if (channel == 'r') {
            
            sum = sumRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];
            //std::cout << "RR says GetSumRed at (1,1): " << sum << std::endl;
        }

        if (channel == 'g') {

            sum = sumGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];
            //std::cout << "RR says GetSumGreen at (1,1): " << sum << std::endl;

        }

        if (channel == 'b') {

            sum = sumBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];
            //std::cout << "RR says GetSumBlue at (1,1): " << sum << std::endl;

        }

    }

    if (ul.first == 0 && ul.second != 0) {

        if (channel == 'r') {

            sum = sumRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumRed[ul.second - 1][ul.first + pow(2, dim) - 1]; 
            //std::cout << "GetSumRed at (1,1): " << sum << std::endl;


        }

        if (channel == 'g') {

            sum = sumGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumGreen[ul.second - 1][ul.first + pow(2, dim) - 1]; 
            //std::cout << "GetSumGreen at (1,1): " << sum << std::endl;
        }

        if (channel == 'b') {

            sum = sumBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumBlue[ul.second - 1][ul.first + pow(2, dim) - 1]; 
            //std::cout << "GetSumGreen at (1,1): " << sum << std::endl;
        }


    }

    if (ul.first != 0 && ul.second == 0) {

        if (channel == 'r') {

            sum = sumRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumRed[ul.second + pow(2, dim) - 1][ul.first - 1]; 
        }

        if (channel == 'g') {

            sum = sumGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumGreen[ul.second + pow(2, dim) - 1][ul.first - 1];
        }

        if (channel == 'b') {

            sum = sumBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumBlue[ul.second + pow(2, dim) - 1][ul.first - 1];
        }
    }


    if (ul.first != 0 && ul.second != 0) { 

        if (channel == 'r') {

            sum = sumRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumRed[ul.second - 1][ul.first + pow(2, dim) - 1] - 
            sumRed[ul.second + pow(2, dim) - 1][ul.first - 1] + 
            sumRed[ul.second - 1][ul.first - 1]; //good
            //std::cout << "GetSumRed at (1,1): " << sum << std::endl;
            

        } if (channel == 'g') {

            sum = sumGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumGreen[ul.second - 1][ul.first + pow(2, dim) - 1] - 
            sumGreen[ul.second + pow(2, dim) - 1][ul.first - 1] + 
            sumGreen[ul.second - 1][ul.first - 1];
            //std::cout << "GetSumGreen at (1,1): " << sum << std::endl;

        } if (channel == 'b') {

            sum = sumBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumBlue[ul.second - 1][ul.first + pow(2, dim) - 1] - 
            sumBlue[ul.second + pow(2, dim) - 1][ul.first - 1] + 
            sumBlue[ul.second - 1][ul.first - 1];
            //std::cout << "GetSumBlue at (1,1): " << sum << std::endl;
        }
    }

    return sum;
/* Your code here!! */
}

// this should be accessing the sumSquare vectors which are populated in the constructor "stats"

long stats::getSumSq(char channel, pair<int,int> ul, int dim){

    long sumSq = 0; 

        if (ul.first == 0 && ul.second == 0) {

        if (channel == 'r') {
            
            sumSq = sumsqRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];
            //std::cout << "Rene Says: SumSqRed at (1,1) line 232: " << sumSq << std::endl;
        }

        if (channel == 'g') {

            sumSq = sumsqGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];
            //std::cout << "Rene Says: SumSqGreen at (1,1) line 238: " << sumSq << std::endl;

        }

        if (channel == 'b') {

            sumSq = sumsqBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1];
            //std::cout << "Rene Says: SumSqBlue at (1,1) line 245: " << sumSq << std::endl;

        }

    }

    if (ul.first == 0 && ul.second != 0) {

        if (channel == 'r') {

            sumSq = sumsqRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumsqRed[ul.second - 1][ul.first + pow(2, dim) - 1]; 
            //std::cout << "GetSumRed at (1,1): " << sum << std::endl;


        }

        if (channel == 'g') {

            sumSq = sumsqGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumsqGreen[ul.second - 1][ul.first + pow(2, dim) - 1]; 
            //std::cout << "GetSumGreen at (1,1): " << sum << std::endl;
        }

        if (channel == 'b') {

            sumSq = sumsqBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumsqBlue[ul.second - 1][ul.first + pow(2, dim) - 1]; 
            //std::cout << "GetSumGreen at (1,1): " << sum << std::endl;
        }


    }

    if (ul.first != 0 && ul.second == 0) {

        if (channel == 'r') {

            sumSq = sumsqRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumsqRed[ul.second + pow(2, dim) - 1][ul.first - 1]; 
        }

        if (channel == 'g') {

            sumSq = sumsqGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumsqGreen[ul.second + pow(2, dim) - 1][ul.first - 1];
        }

        if (channel == 'b') {

            sumSq = sumsqBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumsqBlue[ul.second + pow(2, dim) - 1][ul.first - 1];
        }
    }


    if (ul.first != 0 && ul.second != 0) { 

        if (channel == 'r') {

            sumSq = sumsqRed[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumsqRed[ul.second - 1][ul.first + pow(2, dim) - 1] - 
            sumsqRed[ul.second + pow(2, dim) - 1][ul.first - 1] + 
            sumsqRed[ul.second - 1][ul.first - 1]; 
            //std::cout << "GetSumRed at (1,1): " << sum << std::endl;
            

        } if (channel == 'g') {

            sumSq = sumsqGreen[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumsqGreen[ul.second - 1][ul.first + pow(2, dim) - 1] - 
            sumsqGreen[ul.second + pow(2, dim) - 1][ul.first - 1] + 
            sumsqGreen[ul.second - 1][ul.first - 1];
            //std::cout << "GetSumGreen at (1,1): " << sum << std::endl;

        } if (channel == 'b') {

            sumSq = sumsqBlue[ul.second + pow(2, dim) - 1][ul.first + pow(2, dim) - 1] - 
            sumsqBlue[ul.second - 1][ul.first + pow(2, dim) - 1] - 
            sumsqBlue[ul.second + pow(2, dim) - 1][ul.first - 1] + 
            sumsqBlue[ul.second - 1][ul.first - 1];
            //std::cout << "GetSumBlue at (1,1): " << sum << std::endl;
        }
    }

    return sumSq;
/* Your code here!! */
}

/// @todo change the power sign here too 

long stats::rectArea(int dim) {

    long length = pow(2, dim); 
    long area = length * length;

    //long area = pow(pow(2, dim), 2); 
    return area;

/* Your code here!! */

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
long stats::getVar(pair<int,int> ul, int dim){
/* Your code here!! */


    long sumsqRed = getSumSq('r', ul, dim);
    //cout << "RR says sumsqRed: " << long(sumsqRed) << endl;
    long sumsqGreen = getSumSq('g', ul, dim);
    //cout << "RR says sumsqGreen: " << long(sumsqGreen) << endl;
    long sumsqBlue = getSumSq('b', ul, dim);
    //cout << "RR says sumsqBlue: " << long(sumsqBlue) << endl;

    long sumRed = getSum('r', ul, dim);
    long sumGreen = getSum('g', ul, dim);
    long sumBlue = getSum('b', ul, dim);

    long area = rectArea(dim);
    //cout << "RR says the expected area is: " << long(area) << endl;

    long variance = (sumsqRed - pow(sumRed, 2)/area) + (sumsqGreen - pow(sumGreen, 2)/area) + (sumsqBlue - pow(sumBlue, 2)/area);
    return variance;

}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int dim){

    RGBAPixel pixel; 
    long sumRed = getSum('r', ul, dim);
    //cout << "RR says sumRed: " << long(sumRed) << endl; 
    long sumGreen = getSum('g', ul, dim);
    //cout << "RR says sumGreen: " << long(sumGreen) << endl; 
    long sumBlue = getSum('b', ul, dim); 
    //cout << "RR says sumBlue: " << long(sumBlue) << endl;

    long area = rectArea(dim); 

    long avgRed = sumRed/area;
    long avgGreen = sumGreen/area;
    long avgBlue = sumBlue/area;

    pixel.r = avgRed;
    //cout << int(pixel.r) << endl;
    pixel.g = avgGreen;
    //cout << int(pixel.g) << endl;
    pixel.b = avgBlue;
    //cout << int(pixel.b) << endl;
    //cout << "RR says stats.cpp line 210: " << endl;
    
    return pixel;

/* Your code here!! */



}
