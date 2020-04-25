#include "rebound.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void heartbeat(struct reb_simulation* r){
    //printf("%e    %e %e    %e %e  \n",r->t, r->particles[0].x, r->particles[0].y, r->particles[0].vx, r->particles[0].vy);
    //printf("%e    %e %e    %e %e  \n",r->t, r->particles[1].x, r->particles[1].y, r->particles[1].vx, r->particles[1].vy);
    printf("-------------\n");
}

int main(int argc, char* argv[]) {
    struct reb_simulation* r = reb_create_simulation();
    r->dt = 2;
    r->heartbeat = heartbeat;
    r->integrator = REB_INTEGRATOR_MERCURANA;
    r->ri_mercurana.kappa = 1e-7;
    r->ri_mercurana.N_dominant = 0;
    
    struct reb_particle p1 = {0}; 
    p1.m = 1.;
    reb_add(r, p1);  
    
    struct reb_particle p2 = {0};
    p2.x = 1;
    p2.vy = 1;
    p2.m = 1e-3;
    reb_add(r, p2); 
    
    struct reb_particle p3 = {0};
    p3.x = 2;
    p3.vy = 0.74;
    p3.m = 1e-3;
    reb_add(r, p3); 

    double E0 = reb_tools_energy(r);
    reb_integrate(r,10.);
    double E1 = reb_tools_energy(r);
    printf("dE/E = %e\n",fabs((E0-E1)/E0));
}
