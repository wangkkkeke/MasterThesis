function [ output_args ] =Plot_TH_analysis_solid( Tr0,Tf0,kr,rof,cf,vf,a,ror,cr,flag,x,y,t,outfilename)
%2017-9-6添加
%   此处显示详细说明
Tr=Tr0+(Tf0-Tr0)*erfc((2*kr*x+abs(y)*rof*cf*vf*a)./(2*rof*cf*vf*a).*sqrt(ror*cr*vf./(kr*(vf*t+x))));

if flag==0 % 水平监测线 y=*,压力随x的变化
    plot(x,Tr);
    outfilename = strcat(outfilename(1:end-4),'-solid-T-with-x.dat');
    fidw=fopen(outfilename,'w');
    fprintf(fidw,'TITLE = "solid-T-with-x at y=%f m"\n',y);
    fprintf(fidw,'VARIABLES = "X", "Temperature-solid(<sup>0</sup>C)"\n');
    fprintf(fidw,'ZONE DATAPACKING=POINT, T="solid-T-with-x at y=%f m"\n',y);
    pointTvalue=double([x; Tr]);
    fprintf(fidw,'%e %e\n',pointTvalue);
end

if flag==1 % 竖向监测线 x=*,压力随y的变化
    y=y+50;
    plot(y,Tr);
    outfilename = strcat(outfilename(1:end-4),'-solid-T-with-y.dat');
    fidw=fopen(outfilename,'w');
    fprintf(fidw,'TITLE = "solid-T-with-y at %f s"\n',x);
    fprintf(fidw,'VARIABLES = "Y", "Temperature-solid(<sup>0</sup>C)"\n');
    fprintf(fidw,'ZONE DATAPACKING=POINT, T="solid-T-with-y at %f s"\n',x);
    pointTvalue=double([y; Tr]);
    fprintf(fidw,'%e %e\n',pointTvalue);
end

end

