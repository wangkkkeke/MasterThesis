outfilename='T_with_num.dat';
str_x='T';str_y='num';
x=[250 300 350 400 500];
y=[33 41 46 52 57];
figure
plot(x,y)
write_curve_To_teclplot( str_x,str_y, x,y,outfilename);

outfilename='c_with_num.dat';
str_x='c';str_y='num';
x=[400 850 1200];
y=[90 59 53];
figure
plot(x,y)
write_curve_To_teclplot( str_x,str_y, x,y,outfilename);

outfilename='alfa_with_num.dat';
str_x='alfa';str_y='num';
x=[5 7.5 10]*1e-6;
y=[44 59 74];
figure
plot(x,y)
write_curve_To_teclplot( str_x,str_y, x,y,outfilename);

outfilename='k_with_num.dat';
str_x='k';str_y='num';
x=[10 35 60 100];
y=[89 58 51 47];
figure
plot(x,y)
write_curve_To_teclplot( str_x,str_y, x,y,outfilename);

outfilename='h_with_num.dat';
str_x='h';str_y='num';
x=[1 1.5 2.0 2.5 3.0]*1e4;
y=[42 52 60 67 84];
figure
plot(x,y)
write_curve_To_teclplot( str_x,str_y, x,y,outfilename);


