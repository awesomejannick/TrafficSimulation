#ifndef SITE_H
#define SITE_H

#include <math.h>
#include <QTimer>
#include <cstdlib>

class Site
{
public:
    Site();
    Site(float density);
    void update();
    void setDensity(float p);
    void setVelocity(float v);
    float getDensity();
    float getVelocity();
    float optimalVelocity(float pn, float pc);

private:
    float density;
    float velocity;
};

#endif // SITE_H
