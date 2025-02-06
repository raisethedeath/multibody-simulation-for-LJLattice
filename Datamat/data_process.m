% 读取 CSV 文件并转换为矩阵
LJ1 = readmatrix('LJ1.csv');

% 设置视频写入对象
v = VideoWriter('particle_positions.avi'); % 视频文件名
v.FrameRate = 1; % 帧率设置
open(v); % 打开视频文件进行写入

% 获取所有唯一的时间值
%uniqueTimes = linspace(1,10,10);

for t = 1:1:10
    % 提取当前时间的颗粒位置
    %timeData = data(data(:, 4) == t, :);
    
    % 创建图形
    figure(1);
    clf; % 清除之前的图形
    hold on;
    
    % 绘制颗粒
    plot(LJ1((t-1)*size(LJ1,1)/10:t*size(LJ1,1)/10, 2),LJ1((t-1)*size(LJ1,1)/10:t*size(LJ1,1)/10, 3), 'o',Color='r'); % 根据需要调整点的大小和颜色
    title(['Time: ', num2str(t)]);
    xlabel('X Coordinate');
    ylabel('Y Coordinate');
    axis equal; % 保持比例
    xlim([min(LJ1(:, 2)) max(LJ1(:, 2))]);
    ylim([min(LJ1(:, 3)) max(LJ1(:, 3))]);
    
    % 捕获当前帧并写入视频
    frame = getframe(gcf);
    writeVideo(v, frame);
end

% 结束视频写入
close(v);