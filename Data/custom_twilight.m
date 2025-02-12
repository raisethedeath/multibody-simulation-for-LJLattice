% 自定义 twilight 颜色映射
function cmap=custom_twilight(n)
    % 定义 twilight 的颜色
    c1 = [0.80392, 0.36078, 0.36078]; % blueish color
    c2 = [0.2549, 0.41776, 0.88235]; % purplish color

    % 线性插值生成颜色
    r = linspace(c1(1), c2(1), n);
    g = linspace(c1(2), c2(2), n);
    b = linspace(c1(3), c2(3), n);

    cmap= [r', g', b'];
end




