function updateParticleVisualization(LJ1, t, numFrames, ro, theta)
    % 确定当前时间的数据索引
    numParticles = round(size(LJ1, 1) / (numFrames));
    colors = zeros(numParticles, 3); % 初始化颜色矩阵
    measure = zeros(numParticles,1);
    startIdx = (t-1) * numParticles + 1;
    endIdx = min(t * numParticles, size(LJ1, 1)); % 确保不超出矩阵范围
    g=0;
    b=0;
    r=0;
    y=0;
    
    % 提取当前时间的颗粒位置
    timeData = LJ1(startIdx:endIdx, :);
    % 计算速度分量
    %u = timeData(:, 7);
    %v = timeData(:, 8);
   
    if (t>=2)
        pre_startIdx = (t-2) * numParticles + 1;
        pre_endIdx = min((t-1) * numParticles, size(LJ1, 1)); % 确保不超出矩阵范围
        pre_timeData = LJ1(pre_startIdx:pre_endIdx, :);
    end

    if (t==1)
        pre_timeData = timeData;

    end
    
    dislocation = timeData(:,2:3)-pre_timeData(:,2:3);
    %}
    %{
    if (t<numFrames)
        lat_startIdx = (t) * numParticles + 1;
        lat_endIdx = min((t+1) * numParticles, size(LJ1, 1)); % 确保不超出矩阵范围
        lat_timeData = LJ1(lat_startIdx:lat_endIdx, :);
    end

    if (t==numFrames)
        lat_timeData = timeData;

    end
    
    dislocation =lat_timeData(:,2:3)-timeData(:,2:3);
    %}
    %nonZeroIndices = (u ~= 0) | (v ~= 0); % 选择速度不全为零的粒子
    tri = delaunay(timeData(:,2), timeData(:,3));
    % 初始化配位数数组
    neighborCounts = zeros(numParticles, 1);

% 计算每个三角形的配位数
    for i = 1:size(tri, 1)
        triangle = tri(i, :); % 三角形的顶点索引
        for j = 1:3
            neighborCounts(triangle(j)) = neighborCounts(triangle(j)) + 1;
        end
    end
    

    % 根据配位数给小球着色
    for i = 1:numParticles
        switch neighborCounts(i)
            case 4
                colors(i, :) = [0, 1, 0]; % 绿色
                measure(i)=20;
                g=g+1;
            case 7
                colors(i, :) = [0, 0, 1]; % 蓝色
                measure(i)=20;
                b=b+1;
            case 6
                colors(i, :) = [0.5, 0.5, 0.5]; % 灰色
                measure(i)=10;
            case 5
                colors(i, :) = [1, 0, 0]; % 红色
                measure(i)=20;
                r=r+1;
            case 8
                colors(i, :) = [1, 1, 0]; % 黄色
                measure(i)=20;
                y=y+1;
            otherwise
                colors(i, :) = [0.5, 0, 0]; % 深红
                measure(i)=20;
        end
    end

    
    x2 = ro * cos(theta);
    y2 = ro * sin(theta);

    % 创建图形
    figure(1);
    clf; % 清除之前的图形
    hold on;

    % 绘制颗粒
    scatter(timeData(:, 2), timeData(:, 3), measure, colors, 'filled'); % 使用 scatter 函数绘制并填充颜色
    % 绘制速度向量
    %quiver(timeData(nonZeroIndices, 2), timeData(nonZeroIndices, 3), u(nonZeroIndices), v(nonZeroIndices), 'grey', 'LineWidth', 0.3);
    %{
    hv=atan(timeData(:,7)/timeData(:,8));
    cmap = custom_twilight(256);
    colors = cmap; % 生成色图矩阵
    color_indices = round((hv+ 5) / 10 * 255) + 5;
    %color_indices()
    %{
    for i = 1:numParticles
    quiver(timeData(:, 2), timeData(:, 3), timeData(:, 7), timeData(:, 8), 'LineWidth',2, ... % 0.5为箭头缩放比例
        'Color', colors(color_indices(i), :), ...
        'AutoScale', 'off');
    end
    %}
    colormap(cmap);
    colorbar;
    %}
    %quiver(timeData(:, 2), timeData(:, 3), timeData(:, 7), timeData(:, 8), 'Color', [0.5, 0.5, 0.5],'LineWidth', 0.5); % 速度向量
    quiver(timeData(:, 2), timeData(:, 3), 2*dislocation(:,1), 2*dislocation(:,2), 'Color', [0,0,0],'LineWidth', 1,'MaxHeadSize',1); % 位错向量
    %quiver(timeData(:, 2), timeData(:, 3), dislocation(:,1), dislocation(:,2), 'Color', colors(color_indices, :),'LineWidth', 0.8); % 位错向量
    % 绘制圆形
    plot(x2, y2, 'green', 'LineWidth', 1);
    

    
end
