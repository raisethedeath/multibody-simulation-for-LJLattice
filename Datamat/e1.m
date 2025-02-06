% 假设 timeData 包含小球的信息：列 2 为 x 坐标，列 3 为 y 坐标
timeData = rand(50, 3) * 10; % 随机生成一些小球位置，用于演示
thresholdDistance = 2.0; % 配位数判断的最大距离
numParticles = size(timeData, 1); % 小球数量
colors = zeros(numParticles, 3); % 初始化颜色矩阵

% 计算配位数
for i = 1:numParticles
    % 计算当前小球与其他小球之间的距离
    distances = sqrt(sum((timeData(:, 2:3) - timeData(i, 2:3)).^2, 2)); % 计算距离
    
    % 找出在 thresholdDistance 范围内的邻居数量（排除自身）
    neighborCount = sum(distances < thresholdDistance & (distances > 0));
    
    % 根据配位数给小球着色
    switch neighborCount
        case 0
            colors(i, :) = [1, 0, 0]; % 红色
        case 1
            colors(i, :) = [0, 1, 0]; % 绿色
        case 2
            colors(i, :) = [0, 0, 1]; % 蓝色
        otherwise
            colors(i, :) = [0, 1, 1]; % 青色
    end
end

% 绘制颗粒
figure;
hold on;

for i = 1:numParticles
    plot(timeData(i, 2), timeData(i, 3), 'o', 'MarkerSize', 5, 'Color', colors(i, :));
end

axis equal;
xlim([0, 10]);
ylim([0, 10]);
title('Classification of Particles Based on Coordination Number');
xlabel('X-axis');
ylabel('Y-axis');
grid on;