t_start = 0.0;
t_end = 2.5;
t_total = 2.5;
t_interval = 0.025;
%filename = 'vibration_one_dimension/static,10t0,2,dt=0.0001.csv';
%filename ='pendulum/Elastic,A=0.1,w=2,ri=5,ro=15,t=10,t_interval=0.05.csv';
%filename = 'dissipative_pendulum/Dissipative,k=0.001,A=0.2,w=2,ri=5,ro=15,t=1,t_interval=0.05.csv';
%filename = 'pendulum/Maybe right,Cell,A=0.1,w=2,ri=5,ro=20,t=10,t_interval=0.10,dt=0.0001.csv';
filename = "expansion\elastic bound,cell,ri=5,ro=20,v=4,t_tot=2.5,interval=0.025,dt=0.00005.csv";
%filename = 'energy_conservation/relaxation, cell,ri=5,ro=20,dt=0.0004,ti=5,v=2,t_tot=10,interval=0.1.csv';

plotEnergyComponents(filename, t_start,t_end,t_total,t_interval);
