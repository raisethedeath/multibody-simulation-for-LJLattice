% 定义参数
ri0 = 5;
ro =20;
A = 0.15;
e0= 1;
t0 =1;
w = 3.1416*2/t0;
v0=sqrt(e0);
ve=1*v0;

t_t = 2*t0;
t_total = 10*t0;
t_interval = 0.1*t0;


numFrames = t_total/t_interval+1; % 时间点

% 读取 CSV 文件并转换为矩阵
%LJ1 = readmatrix('energy_conservation/Cell-test,v=1v0,t=0.5,ri=5,ro=15,t_t=5,dt=0.0005.csv');
%LJ1 = readmatrix('dissipative_pendulum/Dissipative,k=0.001,A=0.2,w=2,ri=5,ro=15,t=1,t_interval=0.05.csv');
%LJ1 = readmatrix('pendulum/Cell,A=0.1,w=2,ri=5,ro=20,t=10,t_interval=0.10,dt=0.0001.csv');
%LJ1 = readmatrix('energy_conservation/test, cell, static, t_interval=0.01,dt=0.0005,ri=5,ro=15,t_total=2.csv ');
%LJ1 = readmatrix('energy_conservation/conservation, cell,ri=5,ro=20,dt=0.0002,ti=0.5,v=2,t_tot=10,interval=0.1.csv');
LJ1 = readmatrix("expansion\cell,ri=5,ro=20,v=1,t_tot=10,interval=0.1,dt=0.00002.csv");
% 设置视频写入对象
%v = VideoWriter('Dissipative,k=0.001,A=0.2,w=2,ri=5,ro=15,t=1,t_interval=0.05'); % 视频文件名
%v= VideoWriter('Video/conservation/conservation, cell,ri=5,ro=20,dt=0.0002,ti=0.5,v=2,t_tot=10,interval=0.1');
v= VideoWriter('Video/expansion/cell,ri=5,ro=20,v=1,t_tot=10,interval=0.1,dt=0.00002');
%v = VideoWriter('Cell,A=0.1,w=2,ri=5,ro=20,t=10,t_interval=0.10,dt=0.0001.csv'); % 视频文件名
v.FrameRate = 5; % 根据需要调整帧率
open(v); % 打开视频文件进行写入

% 获取所有唯一的时间值

theta = linspace(0, 2 * pi, 100);
for t = 1:numFrames
    
    updateParticleVisualization(LJ1, t, numFrames, ro, theta);
    %conservation
    %{
    if (t<5)
        %r = ri0 + v0 * 0.1 * t;
        r = ri0+A*(1-cos(w*t_interval*t));
        title(['ri= ', num2str(r)]);
    end
    if(t>=5)
        title(['ri= ', num2str(0)]);
    end
    %}
    %pendulm
    %r = ri0+A*(1-cos(w*t_interval*(t-1)));
    r = ri0 + ve*(t-1)*t_interval;
    title(['$r_i=$ ', num2str(r),'$l_0$',', t=',num2str((t-1)*t_interval/t0),'$\tau_0$'],'interpreter', 'latex', 'FontSize', 10);
    xlabel('X Coordinate');
    ylabel('Y Coordinate');
    axis equal; % 保持比例
    xlim([-ro-5, ro+5]);
    ylim([-ro-5, ro+5]);

    % 捕获当前帧并写入视频
    frame = getframe(gcf);
    writeVideo(v, frame);
end


close(v);
