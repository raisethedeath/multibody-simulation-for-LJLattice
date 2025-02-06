function plotEnergyComponents(filename, t_start,t_end,t_total,t_interval)
    % 从 CSV 文件中读取数据
    %t_interval是取数据的间隔
    LJ1 = readmatrix(filename);
    numFrames_total = t_total/t_interval;
    %numFrames_interval = t_interval/dt;
    numFrames_t_start = t_start/t_interval;
    numFrames_t_end = t_end/t_interval;

    % 根据帧数提取动能、势能和总能量
    Ek = LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:size(LJ1, 1) / numFrames_total * numFrames_t_end , 4);
    Ep = LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:size(LJ1, 1) / numFrames_total * numFrames_t_end , 5);
    Et = LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:size(LJ1, 1) / numFrames_total * numFrames_t_end , 6);

    % 计算总能量的标准差并显示
    StdE = std(Et);
    disp(['Standard Deviation of Total Energy: ', num2str(StdE)]);
    
    % 生成时间向量
    t = linspace(t_start, t_end, round((t_end-t_start)/t_interval));
    
    
    % 创建图形
    figure(6);
    clf;
    plot(t, Ek, 'DisplayName', 'Ek'); hold on;
    plot(t, Ep, 'DisplayName', 'Ep');
    plot(t, Et, 'DisplayName', 'Et');
    
    % 添加图例和标签
    legend('show');
    xlabel('Time');
    ylabel('Energy');
    title('Energy Components Over Time');
    grid on;
end
