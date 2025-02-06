% 生成一些随机点
numPoints = 10; % 点的数量
x = rand(numPoints, 1); % x 坐标
y = rand(numPoints, 1); % y 坐标

% 进行 Delaunay 三角剖分
tri = delaunay(x, y);

% 初始化配位数数组
coordinationNumber = zeros(numPoints, 1);

% 计算每个三角形的配位数
for i = 1:size(tri, 1)
    triangle = tri(i, :); % 三角形的顶点索引
    for j = 1:3
        coordinationNumber(triangle(j)) = coordinationNumber(triangle(j)) + 1;
    end
end

% 输出每个点的配位数
disp('各点的配位数:');
disp(coordinationNumber);

% 可视化结果
figure(10);
scatter(x, y, 'filled');
hold on;

% 绘制三角形
trisurf(tri, x, y, zeros(size(x)), 'FaceColor', 'cyan', 'EdgeColor', 'black', 'FaceAlpha', 0.5);

% 设置图形属性
title('Delaunay Triangulation with Coordination Numbers');
xlabel('X');
ylabel('Y');
axis equal; % 保持坐标轴比例
grid on;

% 在对应的点上显示配位数
for k = 1:numPoints
    text(x(k), y(k), num2str(coordinationNumber(k)), 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right');
end

hold off;
