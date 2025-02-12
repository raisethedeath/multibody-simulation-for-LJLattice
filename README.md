## Lennard-Jones Potential Implementation

In this study, a two-dimensional Lennard-Jones (L-J) lattice model is used to investigate the dynamic behaviour of elastic systems. The particles in the model interact on a triangular lattice through the L-J potential:
$
V(r) = 4\epsilon_0[(\frac{\sigma_0}{r})^{12}-(\frac{\sigma_0}{r})^{6}]
$
where *r* denotes interparticle distance, $\sigma_0$ represents the zero-crossing distance, and $\epsilon_0$ is the potential well depth. The equilibrium bond length is defined as $l_0=2^{\frac{1}{6}}\sigma_0$, enabling bond rupture/reformation to model plastic deformation.

Characteristic temporal and velocity scales are: $\tau_0 = \sqrt{\frac{ml_0^2}{\epsilon_0}}$, $v_0 = \frac{l_0}{\tau_0}=\sqrt{\frac{\epsilon_0}{m}}$

## System Configuration
```
/multibody/
	├── /include/
	|		├── Vec2.h  
	|		├── Particle.h	
	|		├── Energy.h	
	|		├── LJForces.h	
	|		├── Constrain.h	
	|		├──	Triangular_Distribution.h 
	|		├── Save.h 	
	|		├──	Simulate_Triangular.h	
	|		└──Simulate_Triangular_Cell.h
	├── /bin/ //.exe
	├──/Data/ //.csv
	└──/src/
		├── energy_conservation.cpp
		├── energy_conservation_cell.cpp
		└── expansion_cell.cpp
```

## Description
**Particle.h** defines some vital variables for class particle, such as position, previous position, acceleration, mass and velocity and it also contains **apply force function and update function which exert the Verlet method to update rules of the positions  of the particles.** The position and velocity of the particles was used to calculate total kinetic and potential energy in **Energy.h**



**Simulate_Triangular_Cell .h**

This file plays a vital role in the program as it combined the functions and classes above to update the position of the particles.

We first divide cells by integer division of its coordinates using cut-off radius. Then ergodic cells containing particles and ergodic particles denoted by **IndexA**  in that specific cell with particles denoted by **IndexB** in its pair cell in **Neighbor_Index**, and compute the kinetic, L-J forces and L-J potentials between **IndexA** and **IndexB**. Note that as each particle will be ergodiced in the whole process, the L-J potentials are multipy with $0.5$. The **Neighbor_Index** is constructed by combining the specific cell and **offset**.


