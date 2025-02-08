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
| $3:$ $ \boldsymbol{x(t+h)}\longrightarrow \boldsymbol{x(t')}$,$\boldsymbol{x(t'-h)}\longrightarrow \boldsymbol{x(t'-h)}$;    //update position |
| $4:$ $(\boldsymbol{x(t+h)}-\boldsymbol{x(t)})/h \longrightarrow \boldsymbol{v(t)}$  //velocity |
| $5:$ $\boldsymbol{a(t)}=(0,0)$  //reset acceleration         |

<center><bold> Table 1: Update Function based on Verlet method </bold></center>

| L-J Force Calculation [^2]:                                  |
| ------------------------------------------------------------ |
| **Input:** Particle a & b from Particle Class involving $ \boldsymbol{x_{a,b}(t)},$ $\boldsymbol{x_{a,b}(t-h)}$ $\boldsymbol{v_{a,b}(t)}, $  unit energy $\epsilon_0$ and length parameter $\sigma_0$ |
| **Output:** $\boldsymbol{F(t)}$ between Particle a & Particle b |
|                                                              |
| $1:$ direction vector $\vec{AB} =\boldsymbol{x_{b}(t)}-\boldsymbol{x_{a}(t)}$; **distance ** $|\vec{AB}| = \vec{AB}.$ length() ; // defined in Vec2.h |
| $2:$ **if** (**distance** == 0 && **distance ** $> 3l_0$  ) **then** |
| $3:$     **return** {0,0}; //prevent the denominator from zero and set cutoff length |
| $4:$ **end if**                                              |
| $5:$  **if** (**distance** $\leq 3l_0$ ) **then**            |
| $6:$      $4\epsilon_0(-12\frac{\sigma_0^{12}}{\bold{d} ^{13}}+6\frac{\sigma_0^6}{\bold{d}^{7}}) \longrightarrow$ **forceMagnitude**; |
| $7:$      **return** $\vec{AB}/|\vec{AB}|$ *  **forceMagnitude** |
| $8:$ **end if**                                              |
|                                                              |

<center>Table 2: L-J Force Calculation Function</center>



**Simulate_Triangular_Cell .h**

This file plays a vital role in the program as it combined the functions and classes above to update the position of the particles.

We first divide cells by integer division of its coordinates using cut-off radius. Then ergodic cells containing particles and ergodic particles denoted by **IndexA**  in that specific cell with particles denoted by **IndexB** in its pair cell in **Neighbor_Index**, and compute the kinetic, L-J forces and L-J potentials between **IndexA** and **IndexB**.[^4] Note that as each particle will be ergodiced in the whole process, the L-J potentials are multipy with $0.5$. The **Neighbor_Index** is constructed by combining the specific cell and **offset**[^3].

| Algorithm: Cell Subdivision Simulation [^6]                  |
| :----------------------------------------------------------- |
| **Input:** Particle Class involving $ \boldsymbol{x(t)}, \boldsymbol{x(t-h)}, \boldsymbol{v(t)}, \boldsymbol{a(t)} $, time step $h$, unit energy $\epsilon_0$ and length parameter $\sigma_0$, outer radius $r_o$, inner radius $r_i$. |
| **Output:** New positions for particles $\boldsymbol{x(t+h)}$, total kinetic $E_{k,tot}$, total potential $E_{p,tot}$, total energy $E_{tot}$ |
|                                                              |
| $1:$ **SET** $r_c$= $3\times 2^{1/6}\sigma_0$; cell_size = $r_c$; $N=$particle.size() ; |
| $2:$ **RESET** particle energy and acceleration;             |
| // Step 1: Create grid for subdivision                       |
| $3:$ grid. clear();                                          |
| $4:$ **for** ($i = 0$; $i<N$; ++i) **do**                    |
| $5:$      **Set** **grid_Index** =int (particles[i].$\boldsymbol{x(t)}$.x / $r_c$), particles[i].$\boldsymbol{x(t)}$.y / $r_c$);  //particles’ grid index |
| $6:$      **grid**[**grid_Index**].push_back(i); // put particles into grid |
| $7:$ **end for**                                             |
| // Step 2: Calculate L-J interactions and energy             |
| $8:$ **offset**$=${{1,1},{1,0},{1,-1},{0,1},{0,0},{0,-1},{-1,1},{-1,0},{-1,-1}}; |
| $9:$ **for** (auto& **cell: grid**) **do**  //Ergodic cells containing particles |
| $10:$     **for** ($i = 0$; $i<$ **cell**.size() ++i) **do**  //Ergodic particles in the cell |
| $11:$          **cell[i]**  $\longrightarrow$ **IndexA** ;   |
| $12:$          **cell** + **offset** $\longrightarrow$ **Neighbor_Index** ;   grid[**Neighbor_Index**] $\longrightarrow$**neighborParticleIndices**  ; |
| $13:$          **for** (**IndexB : neighborParticleIndices**) **do** |
| $14:$                 **if** (**IndexA** <= **IndexB**)  **then**     **continue**；  **end if** // skip itself |
| $15:$                     compute **Force** based on LJForce function[^2]; |
| // Apply forces on particles and ensure that only particles within the outer circle will be applied forces. |
| $16:$                **if** (**Particles[IndexA]** :$\boldsymbol{|x_A(t)|}<r_o$ && $\boldsymbol{|x_B(t)|}<r_o$)  **then** [^4] |
| $17:$                    apply **Force** on **Particles[IndexA]**, apply -**Force** on **Particles[IndexB]**; |
| $18:$                **end if**                              |
| $19:$                **else if ** **(Particles[IndexA]:$\boldsymbol{|x_A(t)|<}r_o$)**  **then** |
| $20:$                          apply **Force** on **Particles[IndexA]**, apply no forces on **Particles[IndexB]**; // aplly no force to particles outer the circle but compute their potentials. |
| $21:$                **end else if**                         |
| $22:$                **else if**  **(Particles[IndexB]:$\boldsymbol{|x_B(t)|<}r_o$)**  **then** |
| $23:$                            apply -**Force** on **Particles[IndexB]**, apply no forces on **Particles[IndexA]**; // aplly no force to particles outer the circle but compute their potentials. |
| $24:$               **end else if**                          |
| $25:$          **end for**                                   |
|                                                              |
| $26:$      **end for**                                       |
| $27:$ **end for**                                            |
| $28:$ update particle positions and velocity based on **Force**; |
|                                                              |
|                                                              |

<center>Table 3: Cell subdivsion method for ergodic</center>

**Constrain.h**

| Constrain particles[^5]                                      |
| ------------------------------------------------------------ |
| **Input:** Inner radius and outer radius $r_i$, $r_o$, **particles** |
| **Output:** confine **particles** out the inner circle       |
|                                                              |
| $1:$ **for** (auto& particle  : **particles**)               |
| $2:$      **if** $\boldsymbol{|x(t)|}< r_i$ **then**         |
| $3:$          $\boldsymbol{x(t)}/\boldsymbol{|x(t)|}$*$r_i \rightarrow$ $\boldsymbol{x(t+h)}$ |
| $4:$      **end if**                                         |
| $5:$ **end for**                                             |

<center>Table 4: Constrain function</center>

