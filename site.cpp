#include "site.h"

Site::Site() {

}

Site::Site(float density) {
    this->density = density;
    this->velocity = 1;
}

float Site::optimalVelocity(float pn, float pc) {
    return tanh(2/pn - density/(pn*pn) - 1/pc) + tanh(1/pc);
}

void Site::setDensity(float p) {
    density = p;
}

void Site::setVelocity(float v) {
    velocity = v;
}

float Site::getDensity() {
    return density;
}

float Site::getVelocity() {
    return velocity;
}
