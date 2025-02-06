t_total = 10;
t_interval = 0.1;
numFrames = t_total/t_interval; % 时间点
distance = 1;

LJ1 = readmatrix('vibration_one_dimension/static,10t0,2,dt=0.0001.csv');

% 设置视频写入对象
v = VideoWriter('0.5v0,10t0,3,dt=0.0001'); % 视频文件名
v.FrameRate = 3; % 根据需要调整帧率
open(v); % 打开视频文件进行写入

numParticles = size(LJ1, 1) / numFrames;
for t =1:numFrames
    startIdx = (t - 1) * numParticles + 1;
endIdx = min(t * numParticles, size(LJ1, 1)); % 确保不超出矩阵范围
% 提取当前时间的颗粒位置
timeData = LJ1(startIdx:endIdx, :);

figure(1);
    clf; % 清除之前的图形
    hold on;
    
    

    % 绘制颗粒
    plot(timeData(:, 2), timeData(:, 3),'o'); 

    % 绘制圆形
    %plot(x2, y2, 'green', 'LineWidth', 1); 

    
    xlabel('X Coordinate');
    ylabel('Y Coordinate');
    axis equal;
    xlim([-numParticles*2*distance,numParticles*2*distance]);
    ylim([-distance,distance]);

    % 捕获当前帧并写入视频
    frame = getframe(gcf);
    writeVideo(v, frame);
end

close(v);