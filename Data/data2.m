% 定义参数
ri0=5;
ro=12;
A = 0.5*ri0;
w= 3.14;
v0 = 0.3;



% 读取 CSV 文件并转换为矩阵
LJ1 = readmatrix('LJ1_const_v.csv');

% 设置视频写入对象
v = VideoWriter('particle_ri0=5,ro=12,v = 0.3,color '); % 视频文件名
v.FrameRate = 3; % 根据需要调整帧率
open(v); % 打开视频文件进行写入

% 获取所有唯一的时间值
numFrames = 100; % 假设你有10个时间点
theta = linspace(0, 2*pi, 100);

for t = 1:numFrames
    % 确定当前时间的数据索引
    numParticles = size(LJ1, 1) / numFrames;
    colors = zeros(numParticles, 3); % 初始化颜色矩阵
    startIdx = (t - 1) * (size(LJ1, 1) / numFrames) + 1;
    endIdx = min(t * (size(LJ1, 1) / numFrames), size(LJ1, 1)); % 确保不超出矩阵范围
    
    % 提取当前时间的颗粒位置
    timeData = LJ1(startIdx:endIdx, :);

    % 计算配位数
    for i = 1:numParticles
    % 计算当前小球与其他小球之间的距离
        distances = sqrt(sum((timeData(:, 2:3) - timeData(i, 2:3)).^2, 2)); % 计算距离
        thresholdDistance = min(distances);
    % 找出在 thresholdDistance 范围内的邻居数量（排除自身）
        neighborCount = sum(distances < thresholdDistance*1.1 & (distances > 0));
    
    % 根据配位数给小球着色
        switch neighborCount
            case 5
                colors(i, :) = [0, 0, 1]; % 蓝色
            case 6
                colors(i, :) = [0.9, 0.9, 0.9]; % 灰色
            case 7
                colors(i, :) = [1, 0, 0]; % 红色
            otherwise
                colors(i, :) = [0, 1, 1]; % 青色
        end
    end

   
    %r = ri0+A*sin(0.1*w*t); %具体数据根据cpp模拟进行调整
    r =  ri0+v0*0.1*t;
    x1 = r*cos(theta);
    y1 = r*sin(theta);
    x2 = ro*cos(theta);
    y2 = ro*sin(theta);
    % 创建图形
    figure(1);
    clf; % 清除之前的图形
    hold on;

    % 绘制颗粒
    %plot(timeData(:, 2), timeData(:, 3), 'o','MarkerSize', 3,  'Color', 'r'); % 正确的颜色参数传递
    for i = 1:numParticles
        plot(timeData(i, 2), timeData(i, 3), 'o', 'MarkerSize', 3, 'Color', colors(i, :));
        hold on;
    end
    
    %plot(timeData(i, 2), timeData(i, 3), 'o', 'MarkerSize', 3, 'Color', colors(i, :));
    % 绘制圆形
    
    plot(x1, y1, 'blue', 'LineWidth', 1); 
    hold on;
    plot(x2, y2, 'green', 'LineWidth', 1); 

    title(['Time: ', num2str(t*0.1)]);
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
