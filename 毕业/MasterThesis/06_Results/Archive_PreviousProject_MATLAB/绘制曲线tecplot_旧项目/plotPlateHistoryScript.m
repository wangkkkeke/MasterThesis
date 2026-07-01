width=3;
high=6;
leftData=plotPlateHistory( fullfile('poly-buzhongdie-static-leftplate-his.dat') );
%rightData=plotPlateHistory( fullfile('poly-new-wanbei-static-rightplate-his.dat') );
upData=plotPlateHistory( fullfile('poly-buzhongdie-static-upplate-his.dat') );
ee1=-upData(:,1)/high*100; %轴向应变 压缩为正
ee3=2*leftData(:,1)/width*100; %环向应变 压缩为正
sigma1=abs(upData(:,2)); %rightData(:,2)改为upData(:,2)
sigma3=abs(leftData(:,2));

figure
plot(ee1,sigma1-sigma3)
title('sigma1-sigma3与ee1');
xlabel('ee1');
ylabel('sigma1-sigma3');

figure
plot(ee1,sigma3)
title('sigma3与ee1')
xlabel('ee1');
ylabel('sigma3');

figure
plot(ee1,sigma1)
title('sigma1与ee1')
xlabel('ee1');
ylabel('sigma1');

