% 创建示例数据
x = linspace(0, 10, 20); % X坐标
y = sin(x);              % Y坐标
u = cos(x);             % X方向速度
v = sin(x);             % Y方向速度

% 创建新的图形窗口
figure;

% 使用 scatter 绘制点
scatter(x, y, 50, 'b', 'filled'); % 蓝色填充的散点

hold on; % 保持当前图层以便叠加其他绘图

% 使用 quiver 绘制箭头
quiver(x, y, u, v, 0, 'r', 'LineWidth', 1.5); % 红色箭头

% 使用 plot 绘制线
plot(x, y, 'g-', 'LineWidth', 1.5); % 绿色线

hold off; % 释放当前图层

% 添加图例和标签
xlabel('X轴');
ylabel('Y轴');
title('在同一图层内绘制 quiver、scatter 和 plot');
legend('散点', '速度箭头', '曲线');

% 显示网格
grid on;

