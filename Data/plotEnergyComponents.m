function plotEnergyComponents(filename, t_start,t_end,t_total,t_interval)
    % 从 CSV 文件中读取数据
    %t_interval是取数据的间隔
    LJ1 = readmatrix(filename);
    numFrames_total = t_total/t_interval+1;
    %numFrames_interval = t_interval/dt;
    numFrames_t_start = t_start/t_interval;
    numFrames_t_end = t_end/t_interval+1;

    % 根据帧数提取动能、势能和总能量
    Ek = LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:(size(LJ1, 1) / numFrames_total) * numFrames_t_end , 4);
    Ep = LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:(size(LJ1, 1) / numFrames_total) * numFrames_t_end , 5);
    Et = LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:(size(LJ1, 1) / numFrames_total) * numFrames_t_end , 6);
    %Et = Ek+Ep;
    % 计算总能量的标准差并显示
    StdE = std(Et);
    disp(['Standard Deviation of Total Energy: ', num2str(StdE)]);
    
    % 生成时间向量
    %t = linspace(t_start, t_end, round((t_end-t_start)/t_interval));
    t= LJ1(size(LJ1, 1) / numFrames_total * numFrames_t_start+1 :size(LJ1, 1) / numFrames_total:size(LJ1, 1) / numFrames_total * numFrames_t_end , 9);
    ymin = min([Ek;Ep;Et]);
    ymax = max([Ek;Ep;Et]);
    % 创建图形
    figure(5);
    clf;
    
    plot(t, Ek,'b-^', 'DisplayName', 'Ek','LineWidth',0.5); hold on;
    plot(t, Ep,'r-s', 'DisplayName', 'Ep','LineWidth',0.5);
    plot(t, Et,'-o', 'DisplayName', 'Et','LineWidth',0.5,'Color',[1, 0.64706, 0]);
    %}
    %{
    semilogy(t, Ek,'b-^', 'DisplayName', 'Ek','LineWidth',0.5); hold on;
    semilogy(t, Ep,'r-s', 'DisplayName', 'Ep','LineWidth',0.5);
    semilogy(t, Et,'-o', 'DisplayName', 'Et','LineWidth',0.5,'Color',[1, 0.64706, 0]);
    %}
    % 添加图例和标签
    legend('show');
    ax = gca;
    ax.YAxis.Exponent = 3;
    xlabel('$t/\tau_0$ ','interpreter', 'latex', 'FontSize', 10);
    ylabel('$E/\epsilon_0$ ','interpreter', 'latex', 'FontSize', 10);
    ylim([ymin,ymax*1.3])
    %axis([xmin xmax ymin 1.2*ymax])

    title('Energy Components Over Time');
    grid on;
end
