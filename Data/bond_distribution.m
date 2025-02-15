%% 定义参数并对数据进行triangular预处理
ri0 = 5;
ro =20;
A = 0.15;
e0= 1;
t0 =1;
w = 3.1416*2/t0;
v0=sqrt(e0);
ve=0.1*v0;


t_total = 100*t0;
t_interval = 1*t0;
%t_start = 0.0;
%t_end = 30*t0;

moment =100.0;
t=moment/t_interval+1;
numFrames = t_total/t_interval+1; % 时间点
%numFrames_total = t_total/t_interval+1;
numFrames_t_start = t_start/t_interval;
numFrames_t_end = t_end/t_interval+1;

% 读取 CSV 文件并转换为矩阵
%LJ1 = readmatrix('energy_conservation/Cell-test,v=1v0,t=0.5,ri=5,ro=15,t_t=5,dt=0.0005.csv');
%LJ1 = readmatrix('dissipative_pendulum/Dissipative,k=0.001,A=0.2,w=2,ri=5,ro=15,t=1,t_interval=0.05.csv');
%LJ1 = readmatrix('pendulum/Cell,A=0.1,w=2,ri=5,ro=20,t=10,t_interval=0.10,dt=0.0001.csv');
%LJ1 = readmatrix('energy_conservation/test, cell, static, t_interval=0.01,dt=0.0005,ri=5,ro=15,t_total=2.csv ');
%LJ1 = readmatrix('energy_conservation/relaxation, cell,ri=5,ro=20,dt=0.0004,ti=2,v=1,t_tot=30,interval=0.1.csv');
LJ1 = readmatrix('expansion/elastic bound,cell,ri=5,ro=20,v=0.1,t_tot=100,interval=1,dt=0.001.csv');

numParticles = round(size(LJ1, 1) / (numFrames));



startIdx = (t-1) * numParticles + 1;
endIdx = min(t * numParticles, size(LJ1, 1)); % 确保不超出矩阵范围
%当前位置
timeData = LJ1(startIdx:endIdx, :);

tri = delaunay(timeData(:,2), timeData(:,3));

%% 计算近邻距离
% 获取每个三角形的边
edges = [];
for i = 1:size(tri, 1)
    edges = [edges; tri(i, [1 2]); tri(i, [2 3]); tri(i, [3 1])];
end

% 找到唯一的边（去重）
edges = unique(sort(edges, 2), 'rows');

% 初始化距离数组
distances = zeros(size(edges, 1), 1);

% 计算距离
for i = 1:size(edges, 1)
    point1 = timeData(edges(i, 1), 2:3); % 第一个点
    point2 = timeData(edges(i, 2), 2:3); % 第二个点
    distances(i) = norm(point1 - point2); % 计算欧几里得距离
end
distances(distances<1.001&distances>0.999)=[]; 
distances(distances>2)=[];

% 绘制距离分布
figure(8);
histogram(distances,500,'BinLimits',[0,2],'FaceColor',[0.3010, 0.7450, 0.9330],'EdgeColor',[0 0.4470 0.7410], 'Normalization', 'probability');
xlabel(['Bond Lenght',' ','$l_0$'],'Interpreter','latex');
ylabel('PDF');
title('Distribution of Bond Length');
