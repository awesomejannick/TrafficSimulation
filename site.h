#ifndef SITE_H
#define SITE_H

#include <math.h>
#include <QTimer>
#include <cstdlib>

class Site
{
public:
    Site();
    Site(float density, float velocity, float variance);
    void update();
    void setDensity(float p);
    void setVelocity(float v);
    void setVariance(float th);
    float getDensity();
    float getVelocity();
    float getVariance();
    float optimalVelocity(float pn, float pc);

private:
    float density;
    float velocity;
    float variance;
};

#endif // SITE_H
