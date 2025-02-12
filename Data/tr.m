cmap = custom_twilight(256); % 获取自定义颜色映射

% 生成测试数据
[X, Y] = meshgrid(-3:0.1:3, -3:0.1:3);
Z = sin(sqrt(X.^2 + Y.^2)); % 示例数据

% 绘图
figure;
surf(X, Y, Z, 'EdgeColor', 'none'); % 创建表面图
colormap(cmap); % 应用自定义颜色映射
colorbar; % 显示颜色条
title('Custom Twilight Colormap Example');