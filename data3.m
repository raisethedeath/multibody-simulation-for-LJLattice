% 定义参数
ri0 = 5;
ro = 10;
A = 0.5 * ri0;
w = 3.14;
%v0 = 0;
numFrames = 80; % 时间点

% 读取 CSV 文件并转换为矩阵
LJ1 = readmatrix('E-t,2t0.csv');

% 设置视频写入对象
v = VideoWriter('E-t,2t0'); % 视频文件名
v.FrameRate = 3; % 根据需要调整帧率
open(v); % 打开视频文件进行写入

% 获取所有唯一的时间值

theta = linspace(0, 2 * pi, 100);

for t = 1:numFrames
    % 确定当前时间的数据索引
    numParticles = size(LJ1, 1) / numFrames;
    colors = zeros(numParticles, 3); % 初始化颜色矩阵
    startIdx = (t - 1) * numParticles + 1;
    endIdx = min(t * numParticles, size(LJ1, 1)); % 确保不超出矩阵范围
    
    % 提取当前时间的颗粒位置
    timeData = LJ1(startIdx:endIdx, :);
    
    % 向量化计算配位数
    distances = pdist2(timeData(:, 2:3), timeData(:, 2:3)); % 计算所有小球之间的距离


% 将自身的距离设为无穷大，以便不会被选中
    distances(1:size(distances, 1) + 1:end) = inf; 
    minDistances = min(distances, [], 2); % 每行的最小距离

% 计算第二小的距离
    secondMinDistances = distances; 
    for i = 1:size(secondMinDistances, 1)
        secondMinDistances(i, :) = sort(secondMinDistances(i, :)); % 对每行排序
    end

% 获取第二小的距离
    secondMinValue = secondMinDistances(:, 2); % 提取第二小的距离


    threshold = secondMinValue * 1.4;

% 计算邻居数量，按行检查与每个球体的距离是否小于阈值
    neighborCounts = sum(distances < threshold, 2); % 按行计算每个粒子的邻居数量

    % 根据配位数给小球着色
    for i = 1:numParticles
        switch neighborCounts(i)
            case 4
                colors(i, :) = [0, 1,0]; % 绿色
            case 7
                colors(i, :) = [0, 0, 1]; % 蓝色
            case 6
                colors(i, :) = [0.5, 0.5, 0.5]; % 灰色
            case 5
                colors(i, :) = [1, 0, 0]; % 红色
            case 8
                colors(i, :) = [1, 1, 0]; % 黄色
            otherwise
                colors(i, :) = [0.5,0, 0]; % 深红
        end
    end

    % 圆形轨迹
    %{
    if (t<=100)
        r = ri0 + v0 * 0.05 * t;
    end
    if (t>100) 
        r = 10;
    end
    %}
    %r = ri0;
    %r = ri0 + v0 * 0.08 * t;
    %r = ri0+A*sin(0.1*w*t); %具体数据根据cpp模拟进行调整
    %x1 = r * cos(theta);
    %y1 = r * sin(theta);
    x2 = ro * cos(theta);
    y2 = ro * sin(theta);

    % 创建图形
    figure(1);
    clf; % 清除之前的图形
    hold on;

    % 绘制颗粒
    %plot(timeData(:, 2), timeData(:, 3), 'o', 'MarkerSize', 3, 'Color', colors); % 使用数组绘制
    
    % 绘制颗粒
    scatter(timeData(:, 2), timeData(:, 3), 10, colors, 'filled'); % 使用 scatter 函数绘制并填充颜色

    % 绘制圆形
    plot(x1, y1, 'blue', 'LineWidth', 1); 
    plot(x2, y2, 'green', 'LineWidth', 1); 
    %{
    if (t<=100)
        title(['ri= ', num2str(ri0+0.1*v0*t)]);
    end
    if (t>100)
        title(['ri= ', num2str(ri0+5)]);
    end
    %}
    title(['ri= ', num2str(r)]);
    xlabel('X Coordinate');
    ylabel('Y Coordinate');
    axis equal; % 保持比例
    xlim([-ro-5, ro+5]);
    ylim([-ro-5, ro+5]);

    % 捕获当前帧并写入视频
    frame = getframe(gcf);
    writeVideo(v, frame);
end

% 结束视频写入
close(v);
