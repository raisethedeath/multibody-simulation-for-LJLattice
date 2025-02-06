% 随机生成一些小球的坐标
numParticles = 10; % 小球数量
positions = rand(numParticles, 2) * 5; % 在 [0, 10] 范围内随机生成小球位置
radii = 0.5*ones(numParticles, 1); % 所有小球半径为1

% 定义阈值以确定邻居数量
thresholdDistance = 2.0; % 判断为邻居的最大距离
colors = zeros(numParticles, 3); % 初始化颜色矩阵

% 计算每个小球周围的邻居数量
for i = 1:numParticles
    % 计算当前小球与其他小球之间的距离
    distances = sqrt(sum((positions - positions(i, :)).^2, 2)); % 计算距离
    
    % 找出在 thresholdDistance 范围内的邻居数量
    neighborCount = sum(distances < thresholdDistance & (distances > 0)); % 排除自己
    
    % 根据邻居数量给小球着色
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

% 绘制小球
figure;
hold on;
for i = 1:numParticles
    % 绘制每个小球
    viscircles(positions(i, :), radii(i), 'Color', colors(i, :), 'LineWidth', 1);
end

axis equal;
xlim([0, 10]);
ylim([0, 10]);
title('Classification of Particles Based on Neighbors');
xlabel('X-axis');
ylabel('Y-axis');
grid on;
