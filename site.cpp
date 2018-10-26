#include "site.h"

Site::Site() {

}

Site::Site(float density, float velocity, float variance) {
    this->density = density;
    this->velocity = velocity;
    this->variance = variance;
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

void Site::setVariance(float th) {
    variance = th;
}

float Site::getDensity() {
    return density;
}

float Site::getVelocity() {
    return velocity;
}

float Site::getVariance() {
    return variance;
}
