#include "site.h"

Site::Site() {

}

float Site::optimalVelocity(float p) {
    int pc = 0;
    return tanh(2/p0 - p/(p0*p0) - 1/pc) + tanh(1/pc);
}

void Site::update() {

}
