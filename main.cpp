#include <png++/image.hpp>
#include <iostream>
#include <cassert>
#include <cstdlib> // For randomness
#include <ctime> // For randomness
#include <iterator>
#include <algorithm>
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::ostream;
typedef png::rgba_pixel pix_t;
typedef png::image<pix_t> img_t;

ostream& operator<<(ostream& os, pix_t pix) {
    os << "(" << (int) pix.red
       << ", " << (int) pix.green
       << ", " << (int) pix.blue << ")";
    return os;
}

int main(int argc, char* argv[]) {
    assert(argc==3); // Program name, file in, file out
    
    srand(time(NULL));
    
    img_t image(argv[1]);
    
    const size_t width = image.get_width();
    const size_t height = image.get_height();
    
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            pix_t pix = image[j][i];
            float avg = float(pix.red + pix.green + pix.blue) / 3;
            int val = 0;
            if (rand() % 256 < avg)
                pix.red = pix.green = pix.blue = 255;
            else
                pix.red = pix.green = pix.blue = 0;
            image[j][i] = pix;
        }
    }
        
    image.write(argv[2]);
}





