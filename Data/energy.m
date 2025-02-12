% 读取 CSV 文件并转换为矩阵
%% 能量守恒绘图
%{
LJ1 = readmatrix('E-t,2t0.csv');
numFrames = 50; % 时间点
%%
Ek = LJ1(size(LJ1,1)/50*5+1:size(LJ1,1)/numFrames:size(LJ1,1),4);
Ep = LJ1(size(LJ1,1)/50*5+1:size(LJ1,1)/numFrames:size(LJ1,1),5);
Et = LJ1(size(LJ1,1)/50*5+1:size(LJ1,1)/numFrames:size(LJ1,1),6);
StdE = std(Et);
disp(StdE);
%%
t = linspace(0.5,5,numFrames*45/50);
figure(2)
    plot(t,Ek);
    hold on;
    plot(t,Ep);
    hold on;
    plot(t,Et);
    
    legend('Ek','Ep','Et')
%%
%}

%%
LJ1 = readmatrix('E-t,2t0,dt=0.0005.csv');
numFrames = 50; % 时间点
%%
Ek = LJ1(size(LJ1,1)/50*5+1:size(LJ1,1)/numFrames:size(LJ1,1),4);
Ep = LJ1(size(LJ1,1)/50*5+1:size(LJ1,1)/numFrames:size(LJ1,1),5);
Et = LJ1(size(LJ1,1)/50*5+1:size(LJ1,1)/numFrames:size(LJ1,1),6);
StdE = std(Et);
disp(StdE);
%%
t = linspace(0.5,5,numFrames*45/50);
figure(3)
    plot(t,Ek);
    hold on;
    plot(t,Ep);
    hold on;
    plot(t,Et);
    
    legend('Ek','Ep','Et')