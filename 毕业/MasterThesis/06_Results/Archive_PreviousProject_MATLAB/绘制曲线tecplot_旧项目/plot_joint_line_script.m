% 绘制论文28中的节理线，并按照.dxf文件格式输出
w=100e-3;
x=0:0.01*w:w;
y=0.5*1e-3*(1.5*sin(12*pi*(x+0.018)/w)+sin(20*pi*(x+0.01)/w));
plot(x,y);
hold on
plot([0 0],[-20e-3 20e-3]);
plot([0 100e-3],[-20e-3 -20e-3]);
outfilename='joint_line.dxf';
write_curve_to_dxf( x,y,outfilename );