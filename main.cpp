#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor blue  = TGAColor(0, 50, 255, 255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color){
    bool steep=false;
    if(std::abs(x0-x1)<std::abs(y0-y1)){
        std::swap(x0,y0);
        std::swap(x1,y1);
        steep=true;
    }
    if(x0>x1){
        std::swap(x0,x1);
        std::swap(y0,y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    float derror = std::abs(dy)*2;
    float error = 0;
    int y = y0;
    if(steep){
        for(int x=x0; x<=x1; x++){
            //float m = -0.5;
            image.set(y, x, color);
            error += derror;
            if(error > 0.5){
                y += (y1>y0?1:-1);
                error -= dx*2;
            }
        }
    }
    else{
        for(int x=x0; x<=x1; x++){
            //float m = -0.5;
            image.set(x, y, color);
            error += derror;
            if(error > 0.5){
                y += (y1>y0?1:-1);
                error -= dx*2;
            }
        }
    }
}
int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, blue);
    line(0,0,52,41,image,blue);
    line(99,99,52,41,image,red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

