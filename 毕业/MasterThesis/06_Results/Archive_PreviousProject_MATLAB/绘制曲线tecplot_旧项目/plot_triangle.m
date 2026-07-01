function [ output_args ] = plot_triangle( p1,p2,p3 )
%2017-12-24 根据三点绘制三角形p1=[x y]; 并标上节点标号
%   此处显示详细说明
x=[p1(1) p2(1) p3(1)];
y=[p1(2) p2(2) p3(2)];
plot([x(1) x(2)],[y(1) y(2)]);
hold on
plot([x(1) x(3)],[y(1) y(3)]);
hold on
plot([x(2) x(3)],[y(2) y(3)]);
hold on
text(x(1), y(1),'1'); 
text(x(2), y(2),'2'); 
text(x(3), y(3),'3'); 

end

