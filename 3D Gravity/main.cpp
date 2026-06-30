#include "raylib.h"
#include <cmath>
#include <vector>

const double G = 6.674e-11;

struct Body
{
    double posx, posy, posz;
    double velx, vely, velz;
    double mass;
    float radius;
    Color color;
};

void computeForce(Body& a, Body& b, double& fx, double& fy, double& fz)
{
    double dx = b.posx - a.posx;
    double dy = b.posy - a.posy;
    double dz = b.posz - a.posz;
    double r = sqrt(dx * dx + dy * dy + dz * dz + 1.0);

    double force = (G * a.mass * b.mass) / (r * r);

    fx = force * (dx / r);
    fy = force * (dy / r);
    fz = force * (dz / r);
}

void update(Body& b, double fx, double fy, double fz, double dt)
{
    double ax = fx / b.mass;
    double ay = fy / b.mass;
    double az = fz / b.mass;
    b.velx += ax * dt;
    b.vely += ay * dt;
    b.velz += az * dt;
    b.posx += b.velx * dt;
    b.posy += b.vely * dt;
    b.posz += b.velz * dt;
}

int main()
{
    InitWindow(1200, 800, "3D Gravity");
    SetTargetFPS(60);

    Camera3D camera = {};
    camera.position = {300.0f, 200.0f, 300.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    std::vector<Body> bodies;
    bodies.push_back({0.0,   0.0,  0.0,  0.0,   0.0,   0.0,  1.0e12, 8.0f, YELLOW});
    bodies.push_back({100.0, 0.0,  0.0,  0.0,   0.817, 0.0,  1.0,    3.0f, BLUE});
    bodies.push_back({0.0,   0.0, -150.0, 0.667, 0.0,  0.0,  1.0,    3.0f, RED});
    bodies.push_back({-120.0,0.0,  0.0,  0.0,  -0.745, 0.0,  1.0,    3.0f, GREEN});

    double dt = 1.0;
    int stepsPerFrame = 5;
    bool paused = true;
    bool stepOnce = false;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE)) paused = !paused;
        if (IsKeyPressed(KEY_RIGHT)) stepOnce = true;
        if (IsKeyPressed(KEY_UP)) stepsPerFrame++;
        if (IsKeyPressed(KEY_DOWN) && stepsPerFrame > 1) stepsPerFrame--;

        if (!paused || stepOnce)
        {
        stepOnce = false;
        for (int s = 0; s < stepsPerFrame; s++)
        {
            std::vector<double> totalFx(bodies.size(), 0.0);
            std::vector<double> totalFy(bodies.size(), 0.0);
            std::vector<double> totalFz(bodies.size(), 0.0);

            for (int i = 0; i < bodies.size(); i++)
            {
                for (int j = 0; j < bodies.size(); j++)
                {
                    if (i == j) continue;

                    double fx = 0.0, fy = 0.0, fz = 0.0;
                    computeForce(bodies[i], bodies[j], fx, fy, fz);
                    totalFx[i] += fx;
                    totalFy[i] += fy;
                    totalFz[i] += fz;
                }
            }

            for (int i = 0; i < bodies.size(); i++)
            {
                update(bodies[i], totalFx[i], totalFy[i], totalFz[i], dt);
            }
        }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);

        DrawGrid(20, 50.0f);

        for (int i = 0; i < bodies.size(); i++)
        {
            Vector3 pos = {(float)bodies[i].posx, (float)bodies[i].posy, (float)bodies[i].posz};
            DrawSphere(pos, bodies[i].radius, bodies[i].color);
        }

        EndMode3D();

        DrawText("3D Gravity Simulation", 10, 10, 20, WHITE);
        DrawText(paused ? "PAUSED" : "RUNNING", 10, 35, 16, paused ? RED : GREEN);
        DrawText("SPACE: pause/play | RIGHT: step | UP/DOWN: speed", 10, 55, 14, GRAY);
        DrawFPS(10, 60);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
