#ifndef SITE_H
#define SITE_H

#include <math.h>
#define p0

class Site
{
public:
    Site();
    void update();
private:
    float optimalVelocity();

    float density;
    float velocity;
};

#endif // SITE_H
