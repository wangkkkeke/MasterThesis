function [ output_args ] = write_curve_To_teclplot( str_x,str_y, x,y,outfilename)
%2017-12-10 将曲线数据输出到tecplot
%   str_x是x在tecplot中的变量名，str_y是y在tecplot中的变量名  要求x,y为行向量
fidw=fopen(outfilename,'w');
fprintf(fidw,'TITLE = "%s with %s"\n',str_x,str_y);
fprintf(fidw,'VARIABLES = "%s", "%s"\n',str_x,str_y);
fprintf(fidw,'ZONE DATAPACKING=POINT, T="%s with %s"\n',str_x,str_y);
pointTvalue=[x; y];
fprintf(fidw,'%e %e\n',pointTvalue); %按列输出

end

