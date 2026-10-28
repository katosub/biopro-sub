#include"image.hpp"

typedef unsigned char uchar;

int main(void){
    Image sample("sample.png");
    Image grey_image(sample.w,sample.h,3);
    
    for(int y=0;y<sample.h;y++){
        for(int x=0;x<sample.w;x++){
            uchar v=0;
            for(int c=0;c<3;c++){   
                v=v+sample.GetPixel(y,x,c)/3;
            }
            for(int c=0;c<3;c++){
                grey_image.SetPixel(y,x,c,v);
            }
        }
    }
    grey_image.save("grey.png");
    return 0;
}