function [ output_args ] = WriteDataToTecplot( x,y,sigmax,sigmay, outfilename)
%2016-5-27 输出数据文件到tecplot
%   x,y,sigmax,sigmay均为行向量
fidw=fopen(outfilename,'w');
fprintf(fidw,'TITLE = "monitLine Data"\n');
fprintf(fidw,'VARIABLES = "X", "Y", "<greek>s</greek><sub>xx</sub>(Pa)", "<greek>s</greek><sub>yy</sub>(Pa)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="monitLine Data"\n');
pointTvalue=[x; y; sigmax;sigmay];
fprintf(fidw,'%e %e %e %e\n',pointTvalue);
end

