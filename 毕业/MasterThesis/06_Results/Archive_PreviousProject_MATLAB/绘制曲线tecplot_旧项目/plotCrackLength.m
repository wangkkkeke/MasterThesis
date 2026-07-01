sigmaxx=[10.3 12.36 15.45 20.6 25.75];
lamda=[1.0 1.2 1.5 2.0 2.5];
d=85; %Ô²¿×µÄÖ±¾¶ 2014-6-6
length14=[115 121 185 190 190];
length15=[116 134 260 301 302];
length16=[116 159 321 337 336];
length17=[116 223 344 421 423];

length14=(length14-d)*50/85.0;
length15=(length15-d)*50/85.0;
length16=(length16-d)*50/85.0;
length17=(length17-d)*50/85.0;

plot(sigmaxx,length14);
hold on;
plot(sigmaxx,length15);
hold on;
plot(sigmaxx,length16);
hold on;
plot(sigmaxx,length17);
hold on;
figure
plot(lamda,length14);
hold on;
plot(lamda,length15);
hold on;
plot(lamda,length16);
hold on;
plot(lamda,length17);
hold on;