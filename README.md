## Lennard-Jones Potential Implementation

In this study, a two-dimensional Lennard-Jones (L-J) lattice model is used to investigate the dynamic behaviour of elastic systems. The particles in the model interact on a triangular lattice through the L-J potential:
$$
V(r) = 4\epsilon_0[(\frac{\sigma_0}{r})^{12}-(\frac{\sigma_0}{r})^{6}]
$$
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
	|/src/
		├── energy_conservation.cpp
		├── energy_conservation_cell.cpp
		└── expansion_cell.cpp
```

## Description
**Particle.h** defines some vital variables for class particle, such as position, previous position, acceleration, mass and velocity and it also contains **apply force function and update function which exert the Verlet method to update rules of the positions  of the particles.** The position and velocity of the particles was used to calculate total kinetic and potential energy in **Energy.h**

| Update Rule: Verlet method[^1]                               |
| ------------------------------------------------------------ |
| **Input:** Positions $\boldsymbol{x(t)}$, time step $h$, previous positions $\boldsymbol{x(t-h)}$, force $\boldsymbol{F(t)}$ apply on particles and mass  $m$ |
| **Output:** Acceleration $\boldsymbol{a(t)}$, new Position $\boldsymbol{x(t+h)}$ and velocity $\boldsymbol{v(t)}$ of particles |
|                                                              |
| $1:$ $\frac{\boldsymbol{F(t)}}{m}\longrightarrow \boldsymbol{a(t)}$; |
| $2:$ $2\boldsymbol{x(t)}-\boldsymbol{x(t-h)}+ h^2\boldsymbol{a(t)}\longrightarrow \boldsymbol{x(t+h)}$;  //calculate new position |
| $3:$ $ \boldsymbol{x(t+h)}\longrightarrow \boldsymbol{x(t')},\boldsymbol{x(t'-h)}\longrightarrow \boldsymbol{x(t'-h)}$;    //update position |
| $4:$ $(\boldsymbol{x(t+h)}-\boldsymbol{x(t)})/h \longrightarrow \boldsymbol{v(t)}$  //velocity |
| $5:$ $\boldsymbol{a(t)}=(0,0)$  //reset acceleration         |

<center><bold> Table 1: Update Function based on Verlet method </bold></center>

**Particle.h** defines some vital variables for class particle, such as position, previous position, acceleration, mass and velocity and it also contains **apply force function and update function which exert the Verlet method to update rules of the positions  of the particles.** The position and velocity of the particles was used to calculate total kinetic and potential energy in **Energy.h**

| Update Rule: Verlet method[^1]                               |
| ------------------------------------------------------------ |
| **Input:** Positions $\boldsymbol{x(t)}$, time step $h$, previous positions $\boldsymbol{x(t-h)}$, force $\boldsymbol{F(t)}$ apply on particles and mass  $m$ |
| **Output:** Acceleration $\boldsymbol{a(t)}$, new Position $\boldsymbol{x(t+h)}$ and velocity $\boldsymbol{v(t)}$ of particles |
|                                                              |
| $1:$ $\frac{\boldsymbol{F(t)}}{m}\longrightarrow \boldsymbol{a(t)}$; |
| $2:$ $2\boldsymbol{x(t)}-\boldsymbol{x(t-h)}+ h^2\boldsymbol{a(t)}\longrightarrow \boldsymbol{x(t+h)}$;  //calculate new position |
| $3:$ $ \boldsymbol{x(t+h)}\longrightarrow \boldsymbol{x(t')},\boldsymbol{x(t'-h)}\longrightarrow \boldsymbol{x(t'-h)}$;    //update position |
| $4:$ $(\boldsymbol{x(t+h)}-\boldsymbol{x(t)})/h \longrightarrow \boldsymbol{v(t)}$  //velocity |
| $5:$ $\boldsymbol{a(t)}=(0,0)$  //reset acceleration         |

<center><bold> Table 1: Update Function based on Verlet method </bold></center>

**Particle.h** defines some vital variables for class particle, such as position, previous position, acceleration, mass and velocity and it also contains **apply force function and update function which exert the Verlet method to update rules of the positions  of the particles.** The position and velocity of the particles was used to calculate total kinetic and potential energy in **Energy.h**

| Update Rule: Verlet method[^1]                               |
| ------------------------------------------------------------ |
| **Input:** Positions $\boldsymbol{x(t)}$, time step $h$, previous positions $\boldsymbol{x(t-h)}$, force $\boldsymbol{F(t)}$ apply on particles and mass  $m$ |
| **Output:** Acceleration $\boldsymbol{a(t)}$, new Position $\boldsymbol{x(t+h)}$ and velocity $\boldsymbol{v(t)}$ of particles |
|                                                              |
| $1:$ $\frac{\boldsymbol{F(t)}}{m}\longrightarrow \boldsymbol{a(t)}$; |
| $2:$ $2\boldsymbol{x(t)}-\boldsymbol{x(t-h)}+ h^2\boldsymbol{a(t)}\longrightarrow \boldsymbol{x(t+h)}$;  //calculate new position |
| $3:$ $ \boldsymbol{x(t+h)}\longrightarrow \boldsymbol{x(t')},\boldsymbol{x(t'-h)}\longrightarrow \boldsymbol{x(t'-h)}$;    //update position |
| $4:$ $(\boldsymbol{x(t+h)}-\boldsymbol{x(t)})/h \longrightarrow \boldsymbol{v(t)}$  //velocity |
| $5:$ $\boldsymbol{a(t)}=(0,0)$  //reset acceleration         |

<center><bold> Table 1: Update Function based on Verlet method </bold></center>

