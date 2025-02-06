% 读取 CSV 文件并转换为矩阵
LJ1 = readmatrix('LJ1.csv');

% 设置视频写入对象
v = VideoWriter('particle_positions.avi'); % 视频文件名
v.FrameRate = 1; % 根据需要调整帧率
open(v); % 打开视频文件进行写入

% 获取所有唯一的时间值
numFrames = 100; % 假设你有10个时间点

for t = 1:numFrames
    % 确定当前时间的数据索引
    startIdx = (t - 1) * (size(LJ1, 1) / numFrames) + 1;
    endIdx = min(t * (size(LJ1, 1) / numFrames), size(LJ1, 1)); % 确保不超出矩阵范围
    
    % 提取当前时间的颗粒位置
    timeData = LJ1(startIdx:endIdx, :);
    
    % 创建图形
    figure(1);
    clf; % 清除之前的图形
    hold on;

    % 绘制颗粒
    plot(timeData(:, 2), timeData(:, 3), 'o', 'Color', 'r'); % 正确的颜色参数传递
    title(['Time: ', num2str(t)]);
    xlabel('X Coordinate');
    ylabel('Y Coordinate');
    axis equal; % 保持比例
    xlim([min(LJ1(:, 2)), max(LJ1(:, 2))]);
    ylim([min(LJ1(:, 3)), max(LJ1(:, 3))]);

    % 捕获当前帧并写入视频
    frame = getframe(gcf);
    writeVideo(v, frame);
end

% 结束视频写入
close(v);
