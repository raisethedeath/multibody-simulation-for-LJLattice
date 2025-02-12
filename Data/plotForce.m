LJ1 = readmatrix("expansion\elastic bound,cell,ri=5,ro=20,v=1,t_tot=10,interval=0.1,dt=0.00002.csv");
v=1.0;
t_total = 10;
t_interval = 0.1;
dx= v*t_interval;
x =linspace(dx,v*t_total-1,v*t_total/dx-1);
numFrames_total = t_total/t_interval+1;
%numFrames_interval = t_interval/dt;
numFrames_t_start = t_start/t_interval;
numFrames_t_end = t_end/t_interval+1;

% 根据帧数提取动能、势能和总能量
%Ek = LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:(size(LJ1, 1) / numFrames_total) * numFrames_t_end , 4);
%Ep = LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:(size(LJ1, 1) / numFrames_total) * numFrames_t_end , 5);
Et = LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:(size(LJ1, 1) / numFrames_total) * numFrames_t_end , 6);
%t= LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:size(LJ1, 1) / numFrames_total * numFrames_t_end , 9);
F = diff(Et,1);
k = diff(Et,2);

figure(4)
clf;
plot(x, k,'b-^', 'DisplayName', 'F','LineWidth',0.5);
