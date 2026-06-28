#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

const double G = 6.674e-11;


class Body
{

    public:
    double posx;
    double posy;
    double velx;
    double vely;
    double mass;

    Body(double x, double y, double vx, double vy, double m)
        : posx(x), posy(y), velx(vx), vely(vy), mass(m)
    {
        
    }


};

void computeForce(Body& a, Body& b, double& fx, double& fy)
{
    if(a.posx == b.posx && a.posy == b.posy)
    {
        fx = 0;
        fy = 0;

        std::cout << "bodies are at same positions, explode" << std::endl;
        return;
    }

    double dx;
    double dy;
    double force;
    double r;           //distance between bodies

    dx = b.posx - a.posx;
    dy = b.posy - a.posy;
    r = sqrt(dx*dx + dy*dy);

    force = (G*a.mass*b.mass)/(r*r);

    fx = force*(dx/r);
    fy = force*(dy/r);
}


void update(Body& b, double fx, double fy, double dt)
{
    
    double ax = fx/b.mass;
    double ay = fy/b.mass;
    b.velx = b.velx + ax * dt;
    b.vely = b.vely + ay * dt;
    b.posx = b.posx + b.velx * dt;
    b.posy = b.posy + b.vely * dt;

}


int main()
{

    std::vector<Body> bodies;
    // Heavy central body, stationary, near origin
    bodies.emplace_back(0.0, 0.0, 0.0, 0.0, 1.0e12);

    // Lighter body off to the side, given some sideways velocity (try to orbit)
    bodies.emplace_back(100.0, 0.0, 0.0, 5.0, 1.0);

    // Another small body further out
    bodies.emplace_back(-150.0, 50.0, -3.0, -2.0, 1.0);

    double dt = 1.0;
    int steps = 50;

    std::ofstream outfile("outfile.csv");
    outfile << "step,body,x,y" << std::endl;

    for(int step = 0; step < steps; step++)
    {
        std::vector<double> totalFx(bodies.size(), 0.0);
        std::vector<double> totalFy(bodies.size(), 0.0);

        for(int i = 0; i < bodies.size(); i++)
        {
            for(int j = 0; j < bodies.size(); j++)
            {
                if(i == j) continue;

                double fx = 0.0, fy = 0.0;
                computeForce(bodies[i], bodies[j], fx, fy);
                totalFx[i] += fx;
                totalFy[i] += fy;
            }
        }

        for(int i = 0; i < bodies.size(); i++)
        {
            update(bodies[i], totalFx[i], totalFy[i], dt);
        

        std::cout << "Step " << step << " Body " << i << ": (" << bodies[i].posx
            << ", " << bodies[i].posy << ")" << std::endl;
        
        outfile << step << "," << i << "," << bodies[i].posx << ","
            << bodies[i].posy << std::endl;

        }
    }

    outfile.close();

    return 0;
};