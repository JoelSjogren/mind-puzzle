#include <png++/image.hpp>
#include <iostream>
#include <cassert>
#include <cstdlib> // For randomness
#include <ctime> // For randomness
#include <cstring>
#include <iterator>
#include <algorithm>
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::ostream;
using std::swap;
typedef png::rgba_pixel pix_t;
typedef png::image<pix_t> img_t;

ostream& operator<<(ostream& os, pix_t pix) {
    os << "(" << (int) pix.red
       << ", " << (int) pix.green
       << ", " << (int) pix.blue << ")";
    return os;
}

int main(int argc, char* argv[]) {
    assert(2 < argc); // Program name, file in, file out
    
    srand(time(NULL));
    
    const img_t img_in(argv[1]);
    const unsigned in_width = img_in.get_width();
    const unsigned in_height = img_in.get_height();
    const unsigned out_width = in_width * 2;
    const unsigned out_height = in_height;
    img_t img_out(out_width, out_height);
    
    for (size_t i = 0; i < in_width; i++) {
        for (size_t j = 0; j < in_height; j++) {
            pix_t in_pix = img_in[j][i];
            int a, b;
            const int rnd = rand() % 3;
            if (rnd == 0 or (argc == 4 and strcmp(argv[3], "-d") == 0)) {
                img_out[j][i] = in_pix;
                img_out[j][i + in_width] = in_pix;
            } else if (rnd == 1) {
                img_out[j][i] = pix_t(0, 0, 0);
                img_out[j][i + in_width] = pix_t(255, 255, 255);
            } else if (rnd == 2) {
                img_out[j][i] = pix_t(255, 255, 255);
                img_out[j][i + in_width] = pix_t(0, 0, 0);
            } else { assert(0); }
        }
    }
        
    img_out.write(argv[2]);
}





