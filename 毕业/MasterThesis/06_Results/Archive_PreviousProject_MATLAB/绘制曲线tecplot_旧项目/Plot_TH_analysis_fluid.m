function [ output_args ] =Plot_TH_analysis_fluid( T0,Tin,rof,cf,df,uf,lamdas,ros,cs,x,t,flag,outfilename)
%单裂纹水热耦合解析解 2017-6-20  flag=0 表示x=*m处的点温度随时间的变化 flag=1 表示t=*s时，整个x轴处的流体温度分布
%该解析解：不考虑流体的热传导，不考虑岩石的渗透性,求前100天的温度变化
% t0=x/uf+1;
% t=0:(60*60):(100*24*60*60);
%Tf=T0+(Tin-T0)*erfc((lamdas*x/(rof*cf*df))./(2*sqrt(lamdas./(ros*cs*(uf*t-x))))).*heaviside(t-x/uf);
Tf=T0+(Tin-T0)*erfc((lamdas*x/(rof*cf*uf*df)).*sqrt(ros*cs*uf./(lamdas*(uf*t+x))));
if flag==0
    plot(t/(24*60*60),Tf);
    outfilename = strcat(outfilename(1:end-4),'-fluid-T-with-t.dat');
    fidw=fopen(outfilename,'w');
    fprintf(fidw,'TITLE = "Temperature with time at %f m"\n',x);
    fprintf(fidw,'VARIABLES = "time", "Temperature-fluid(<sup>0</sup>C)"\n');
    fprintf(fidw,'ZONE DATAPACKING=POINT, T="Temperature with time"\n');
    pointTvalue=double([t; Tf]);
    fprintf(fidw,'%e %e\n',pointTvalue);
end

if flag==1
    plot(x,Tf);
    outfilename = strcat(outfilename(1:end-4),'-fluid-T-with-x.dat');
    fidw=fopen(outfilename,'w');
    fprintf(fidw,'TITLE = "Temperature with x at %f s"\n',t);
    fprintf(fidw,'VARIABLES = "X", "Temperature-fluid(<sup>0</sup>C)"\n');
    fprintf(fidw,'ZONE DATAPACKING=POINT, T="Temperature with X"\n');
    pointTvalue=double([x; Tf]);
    fprintf(fidw,'%e %e\n',pointTvalue);
end

end

