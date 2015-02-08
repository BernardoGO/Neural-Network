#include "opencv2/core/core.hpp"
#include <opencv/highgui.h>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv/cv.hpp"
#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include <opencv/highgui.h>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv/cv.hpp"
#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

class neuron
{
public:
    float sinapsis[50][50];
    float value = 0;

    neuron()
    {
        for(int x = 0; x < 50; x++)
        {
            for(int y = 0; y < 50; y++)
            {
                sinapsis[x][y] = 1;
            }
        }
    }
};

int main()
{
    cout << "Hello world!" << endl;

    neuron* pixels[50][50];
    neuron* saidas[3];
    for(int x = 0; x < 50; x++)
    {
        for(int y = 0; y < 50; y++)
        {
            pixels[x][y] = new neuron();
        }
    }
    for(int x = 0; x < 3; x++)
    {

        saidas[x] = new neuron();

    }

    cout << pixels[1][1]->sinapsis[1][1] << endl;



    cv::Mat image1 = cv::imread("numbers/1_a.png", CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat image2 = cv::imread("numbers/2_a.png", CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat image3 = cv::imread("numbers/3_a.png", CV_LOAD_IMAGE_GRAYSCALE);
    int cicle = 0;

    while(true)
    {
        cicle++;
        for(int out = 0; out < 3; out++)
        {
            saidas[out]->value = 0;
        }
        int imgN = (cicle % 3)+1;
        Mat image;
        if(imgN == 1) image = image1;
        else if(imgN == 2) image = image2;
        else if(imgN == 3) image = image3;

        cout << "image: " + std::to_string(imgN) << endl;


        for(int out = 0; out < 3; out++)
        {

            for(int x = 0; x < 50; x++)
            {
                for(int y = 0; y < 50; y++)
                {
                    uint pix = image.at<uchar>(x,y);
                    if(pix < 50)
                    {
                        saidas[out]->value += saidas[out]->sinapsis[x][y];
                    }
                }
            }
        }

        for(int out = 0; out < 3; out++)
        {
            cout << out+1 << ": " + std::to_string(saidas[out]->value) << endl;
        }



        int gueesed = -1;
        int maxd = 0;

        for(int out = 0; out < 3; out++)
        {
            if(saidas[out]->value >= maxd)
            {
                gueesed = out;
                maxd = saidas[out]->value;
            }
        }

        cout << gueesed+1 << " - Was it correct? " << endl;
        string img;
        cin >> img;
        int correct = atoi(img.c_str())-1;
        cout << "correct: " << correct << imgN<< endl;

        if(correct != gueesed)
        {
            cout << "incorrect" << endl;
            for(int x = 0; x < 50; x++)
            {
                for(int y = 0; y < 50; y++)
                {
                    uint pix = image.at<uchar>(x,y);
                    if(pix < 50)
                    {
                        //saidas[out]->value += saidas[out]->sinapsis[x][y];

                        saidas[correct]->sinapsis[x][y] += 1;
                    }
                }
            }
        }

        //cout << std::to_string(pix) << endl;

    }

    return 0;
}
