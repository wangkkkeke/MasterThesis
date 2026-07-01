function [Q] = plot_v91_ex3_yuanpan_jingxiangliu(pe,pw,re,rw,K,u)
%2018-10-12添加 圆盘径向流的压力分布
% e-表示外边界 w-表示内边界
%plot_v91_ex3_yuanpan_jingxiangliu(2e5,1e5,1,0.2,2e-12,0.001)
r=rw:0.01*(re-rw):re;
pr=pe-(pe-pw)/log(re/rw)*log(re./r);

h=1;
Q=2*pi*K*h*(pe-pw)/(u*log(re/rw));

plot(r,pr);
write_curve_To_teclplot( 'X(m)','Pore-Pressure(Pa)', r,pr,'v91-ex3-平面径向流-水压分布.dat');

end


