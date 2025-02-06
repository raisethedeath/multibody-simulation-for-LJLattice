%% Draw the state of the specified moment %%
% 定义参数
ri0 = 5;
ro = 20;
A = 0.1;
e0= 1;
t0 = 1;
w = 3.1416*2/t0;
v0=sqrt(e0);
v=0.2*v0;

t_t = 2*t0;
t_total = 10*t0;
t_interval = 0.1*t0;

t= 7.8;%指定的时刻
t_frame = t/t_interval+1;

numFrames = t_total/t_interval+1; % 时间点

% 读取 CSV 文件并转换为矩阵
%LJ1 = readmatrix('energy_conservation/cell,ri=5,ro=20,v=0.2,t_tot=10,dt=0.0001.csv ');
LJ1 = readmatrix('pendulum/Maybe right,Cell,A=0.1,w=2,ri=5,ro=20,t=10,t_interval=0.10,dt=0.0001.csv');
%LJ1 = readmatrix('dissipative_pendulum/Dissipative,k=0.001,A=0.2,w=2,ri=5,ro=15,t=1,t_interval=0.05.csv');
% 设置视频写入对象
%v = VideoWriter('Dissipative,k=0.001,A=0.2,w=2,ri=5,ro=15,t=1,t_interval=0.05'); % 视频文件名


% 获取所有唯一的时间值

theta = linspace(0, 2 * pi, 100);

    
    updateParticleVisualization(LJ1, t_frame, numFrames, ro, theta);
    %conservation
    %{
    if (t<5)
        r = ri0 + v * t;
        %r = ri0+A*(1-cos(w*t_interval*t));
        title(['ri= ', num2str(r)]);
    end
    if(t>=5)
        title(['ri= ', num2str(0)]);
    end
   
    %}
     %r = ri0 + v * t;
     r= ri0+A - A*cos(w*t);
    %% pendulm
    %r = ri0+A*(1-cos(w*t));
    title(['$r_i=$ ', num2str(r),'$l_0$',', t=',num2str(t),'$\tau_0$'],'interpreter', 'latex', 'FontSize', 10);
    %{
    xlabel('X Coordinate');
    ylabel('Y Coordinate');
    axis equal; % 保持比例
    %}
    xlabel('X Coordinate');
    ylabel('Y Coordinate');
    axis equal; % 保持比例
    xlim([-ro-5, ro+5]);
    ylim([-ro-5, ro+5]);
