function [ output_args ] = plot_monitor_line_Temperature_to_tecplot( Tin,Tout,r0,R0,outfilename)
%2015-9-11添加  绘制 shuiyazhilie.y 内外周界温度固定 最终的温度分布曲线 并将曲线数据导出为tecplot文件
%   此处显示详细说明
r=r0:0.01*(R0-r0):R0;
T=log(R0./r)/log(R0/r0)*Tin+log(r0./r)/log(r0/R0)*Tout;
plot(r,T);

str_x='X(m)';str_y='Temperature-d-solid(<sup>0</sup>C)';
x=r; y=T;
write_curve_To_teclplot( str_x,str_y, x,y,outfilename);
end