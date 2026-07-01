function [ output_args ] = write_curve_to_dxf( x,y,outfilename )
%将曲线写成dxf格式 x=[x1 x2 ...];y-[y1 y2 ...];
%   curve_line=[x1 y1;x2 y2;...];
fidw=fopen(outfilename,'w');
fprintf(fidw,'0\n');
fprintf(fidw,'SECTION\n');
fprintf(fidw,'2\n');
fprintf(fidw,'ENTITIES\n');
for i=1:(size(x,2)-1)
        fprintf(fidw,'0\n');
        fprintf(fidw,'LINE\n');
        fprintf(fidw,'  8\n');
        fprintf(fidw,'Polygon\n');
        fprintf(fidw,' 10\n');
        fprintf(fidw,'%f\n',x(i)); 
        fprintf(fidw,' 20\n');
        fprintf(fidw,'%f\n',y(i));
        fprintf(fidw,' 11\n');
        fprintf(fidw,'%f\n',x(i+1));
        fprintf(fidw,' 21\n');
        fprintf(fidw,'%f\n',y(i+1));    
end
fprintf(fidw,'0\n');
fprintf(fidw,'ENDSEC\n');
fprintf(fidw,'0\n');
fprintf(fidw,'EOF\n');
fclose(fidw);

end

