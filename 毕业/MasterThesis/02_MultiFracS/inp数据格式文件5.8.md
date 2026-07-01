# MultiFracS 数据格式文件 5.8

*MultiFracS 多物理场断裂分析软件输入数据结构和参数配置文档*

---

MultiFracS 5.8 输入数据文件格式 
多物理场断裂分析软件MultiFracS 
5.8 输入/输出数据文件格式 
作者：严成增 
 
 
 
 
2025-01-01

MultiFracS 5.8 输入数据文件格式 
---------------------------------参数设置------------------------------------- 
*Material=elemSetName 
第一行（总共60 个数据,实体单元用到的参数） 
IeType,密度(初始时的天然密度),E(弹性模量),u(泊松比),pn(法向接触罚参数),ps(切向接触罚
参数),接触内摩擦角,-7,kf11(渗透率),kf22,kf33,kf12,kf23,kf31,-14,Biot 系数,孔隙率,应力渗透率
耦合参数,突变系数,-19,kT11(热传导系数),kT22,kT33,kT12,kT23,kT31,-26,Cp(比热容),tec(热膨
胀系数),htc( 接触换热系数),-30,kM11( 湿度传导系数),kM22,kM33,kM12,kM23,kM31,-
37,msf(湿度收缩系数),-39,ft(实体单元抗拉强度),fc(实体单元抗压强度),-42,x(裂缝中冰水混合
物损失质量占总冰水混合物质量占比),-44,-45,-46,-47,-48,-49,-50,-51,-52,-53,-54,-55,-56,-57,-
58,-59, 
第二行（总共40 个数据,节理单元用的参数） 
IbkFlag,c(粘聚力,必须大于0),phi(内摩擦角),ft(抗拉强度,>0),fs(取1e15),pfn(节理单元法向罚参
数，100E),pfs(切向罚参数，100E),GfI(I 型断裂能),GfII(II 型断裂能),-9,a0(初始张开度),amin(张
开度最小值),amax(张开度最大值),-13,hTfr(水岩换热系数),-15,hTnbj(未断裂节理单元换热系
数),dhTnbj(节理单元断裂时hnbj 的折减系数),-18,hFnbj(未断裂节理单元换流系数),hFpof(孔
隙-裂隙渗流在裂隙处的换流系数),-21,hMnbj(未断裂节理单元换湿系数),dhMnbj(断裂节理单
元换湿系数的浙减系数),-24, 该组节理处两侧附近三角形单元的接触内摩擦
角,imat1,imat2,eflag,-29,am0(力学虚拟张开量>=0),-31,dd(3D 时为倾向，2D 为自x 轴到层理面
的夹角angle，逆时针为正,x 轴水平,y 轴竖直),dip(3D 时为倾角,2D 填写-33 即可),c_min(垂直
于层理粘聚力),phi_min(内摩擦角),ft_min(抗拉强度),GIf_min,GIIf_min,-39,kTc(延裂缝的热扩
散系数),-41,kmc(延裂缝的湿度扩散系数),-43,-44,-45,-46,-47,-48,-49,-50,-51,-52,-53,-54,-55,-
56,-57,-58,-59, 
第三行（总共40 个数据，实体单元塑性本构用到的参数） 
CModelType(本构模型类别),K(体积模量),G(剪切模量),c(粘聚力),phi(内摩擦角),dilation(剪胀
角),ft(抗拉强度),-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-25,-26,-27,-
28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39, 
 
(kf-渗透率张量,kT-热传导系数张量,kM-湿度传导系数张量) 
(IeType=1,平面应力单元,IeType=2,平面应变单元,IeType=3,平面刚体单元, 
 IeType=11 4 节点可变形四面体单元,IeType=12 4 节点刚体四面体单元,IeType=13 10 节点可
变形四面体单元, Ietype=14 10 节点刚体四面体单元) 
(IbkFlag=1 表示节理单元完全断裂,当接触开启时IbkFlag 后的力学参数不起作用,当接触未开
启时IbkFlag 后的除pfn,pfs,内摩擦角以外的力学参数不起作用； 
 IbkFlag=0 节理单元未断裂,IbkFlag 后的力学参数均起作用 
 IbkFlag=-1 节理单元未断裂但是允许裂隙流体流过，用于裂隙渗流等效表征孔隙渗流模型 
或者 能够透水但仍然有一定强度裂缝 
 ) 
 
 ( 
CModelType=0 全量线弹性本构 
CModelType=1 增量线弹性本构 
 
CModelType=2 横观各向同性本构  二维情况下 
2,E1(平行于层理面的弹性模量),E3(垂直于层理面的弹性模量),v12(平行于层理面的泊松

MultiFracS 5.8 输入数据文件格式 
比),v13(垂直作用于层理面的泊松比),G13(垂直于层理面的平面内的剪切模量),angle(自x 轴
到层理面的夹角，逆时针为正,x 轴水平,y 轴竖直),-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-
19,-20,-21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39, 
 
CModelType=2 横观各向同性本构  三维情况下 
2,E1(平行于层理面的弹性模量),E3(垂直于层理面的弹性模量),v12(平行于层理面的泊松
比),v13(力垂直作用于层理面的泊松比),G13(垂直于层理面的平面内的剪切模量),dd(层理面
的倾向),dip(层理面的倾角),-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-25,-
26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39, 
 
CModelType=3 莫尔库伦本构 
3,K(体积模量),G(剪切模量),c(粘聚力),phi(内摩擦角),dilation(剪胀角),ft(抗拉强度),-7,-8,-9,-10,-
11,-12,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-
36,-37,-38,-39, 
CModelType=4 Drucker-Prager 本构 
4,K(体积模量),G(剪切模量),kphi(参数),qphi(参数),qpsi(参数),ft(抗拉强度),-7,-8,-9,-10,-11,-12,-
13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-
38,-39, 
CModelType=5 vonmises 本构 
5,K(体积模量),G(剪切模量),strength(屈服强度),H(塑性模量),-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-
15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39, 
 
CModelType=101 经典粘弹性本构-马克斯威尔体 
101,K(体积模量),G(剪切模量),eta(粘性系数),-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-
18,-19,-20,-21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39, 
CModelType=102 粘弹性本构-power model 
102,K(体积模量),G(剪切模量),A1(power 常数),A2(power 常数),n1(power 指数),n2(power 指
数),rs1(参考应力1),rs2(参考应力2),-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-
24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39, 
) 
 
(GfI,GfII 两者的初始取值可为2,10) 
(对于第二行-31 后的 dd(>=0),c_min(垂直于层理的粘聚力),phi_min(内摩擦角),ft_min(抗拉强
度),GIf_min,GIIf_min，当 
当dd>=0，后面的参数才起作用，此时-31 前面的那组c,phi,ft,GIf,GIIf 表示平行于层理方向的
参数取值 
当dd<0，后面的参数不起作用，表示没有层理 
） 
 
*JointBetweenMat=imat1,imat2 
IbkFlag,c(粘聚力,必须大于0),phi(内摩擦角),ft(抗拉强度,必须大于0),fs(取1e15 不用修
改),pfn(节理单元法向罚参数),pfs(节理单元切向罚参数),GIf(I 型断裂能),GfII(II 型断裂能),-
9,a0(初始张开度),amin(张开度最小值),amax(张开度最大值),-13,hTfr(水岩换热系数),-
15,hTnbj(未断裂节理单元换热系数),dhTnbj(节理单元断裂时换热系数hnbj 的折减系数),-

MultiFracS 5.8 输入数据文件格式 
18,hFnbj(未断裂节理单元换流系数),hFpof(孔隙-裂隙渗流在裂隙处的换流系数),-21,hMnbj(未
断裂节理单元换湿系数),dhMnbj(断裂节理单元换湿系数的折减系数),-24,该组节理处两侧附
近三角形单元的接触内摩擦角,imat1,imat2,eflag,-29,am0(力学虚拟张开量>=0),-31,dd(3D时为
倾向，2D 为自x 轴到层理面的夹角angle，逆时针为正,x 轴水平,y 轴竖直),dip(3D 时为倾角,2D
填写-33
即可),c_min( 垂直于层理粘聚力),phi_min( 粘聚力),ft_min( 抗拉强
度),GIf_min,GIIf_min,-39,kTc(延裂缝的热扩散系数),-41,kmc(延裂缝的湿度扩散系数),-43,-44,-
45,-46,-47,-48,-49,-50,-51,-52,-53,-54,-55,-56,-57,-58,-59, 
 
*Joint=lineElemSetName 
IbkFlag,c(粘聚力,必须大于0),phi(内摩擦角),ft(抗拉强度,必须大于0),fs(取1e15 不用修
改),pfn(节理单元法向罚参数),pfs(节理单元切向罚参数),GIf(I 型断裂能),GfII(II 型断裂能),-
9,a0(初始张开度),amin(张开度最小值),amax(张开度最大值),-13,hTfr(水岩换热系数),-
15,hTnbj(未断裂节理单元换热系数),dhTnbj(节理单元断裂时换热系数hnbj 的折减系数),-
18,hFnbj(未断裂节理单元换流系数),hFpof(孔隙-裂隙渗流在裂隙处的换流系数),-21,hMnbj(未
断裂节理单元换湿系数),dhMnbj(断裂节理单元换湿系数的折减系数),-24,该组节理处两侧附
近三角形单元的接触内摩擦角,imat1,imat2,eflag,-29,am0(力学虚拟张开量>=0),-31,dd(3D时为
倾向，2D 为自x 轴到层理面的夹角angle，逆时针为正,x 轴水平,y 轴竖直),dip(3D 时为倾角,2D
填写-33
即可),c_min( 垂直于层理粘聚力),phi_min( 粘聚力),ft_min( 抗拉强
度),GIf_min,GIIf_min,-39,kTc(延裂缝热扩散系数),-41,kmc(延裂缝湿度扩散系数),-43,-44,-45,-
46,-47,-48,-49,-50,-51,-52,-53,-54,-55,-56,-57,-58,-59, 
 
//*JointBetweenMat 用于设置两种材料分界面的节理单元的参数 
//imat1，imat2 表示材料编号，根据*Mat 出现的顺序从0 开始编号 
//*Joint 的优先级比*JointBetweenMat 优先级高，如果一个节理单元被同时通过*Joint 和
*JointBetweenMat 指定，那么其将采用*Joint 指定参数 
 
//(IbkFlag 同上) 
//imat1 表示内摩擦角施加在节理单元所连接的实体单元材料编号为imat1 一侧的实体单元 
imat1=-1 则不施加该摩擦角 
//imat2 表示内摩擦角施加在节理单元所连接的实体单元材料编号为imat2 一侧的实体单元 
imat2=-1 则不施加该摩擦角 
//eflag 施加该摩擦角的单元的标志 取>=0 的整数 
 
*ContactBetweenMat=imat1,imat2 
pn(法向接触罚参数),ps(切向接触罚参数),接触内摩擦角,-3,htc(接触换热系数),-5,-6,-7,-8,-9, 
 
//*ContactBetweenMat 用于设置两种材料的接触参数 
//imat1，imat2 表示材料编号，根据*Mat 出现的顺序从0 开始编号 
 
---------------------------------力学计算------------------------------------- 
*GravitAcc 
gx,gy,gz, 
 
一行10 个数据

MultiFracS 5.8 输入数据文件格式 
*InitVeclocity=elemSetName 
1,Vx,Vy,Vz,-4,w,xc,yc,zc,axis,-10,-11,-12,（w>0 转动,否则平动, aix=1 绕x 轴旋转,aix=2 绕y 轴
旋转,aix=3 绕z 轴旋转) 
2,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12, (>=2 表示用户自定义初始条件) 
 
一行13 个数据  视为体荷载边界条件 
*InitSituStress=elemSetName 
1,sigxx,sigyy,sigzz,sigxy,sigyz,sigzx,-7,-8,-9,-10,-11,-12,-13,-14, 
2,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14, (>=2 表示用户自定义初始条件) 
-1,sigxx,gradx,grady,gradz,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14, 
-2,sigyy,gradx,grady,gradz,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14, 
-3,sigzz,gradx,gradz,gradz,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14, 
-4,sigxy,gradx,grady,gradz,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14, 
-5,sigyz,gradx,grady,gradz,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14, 
-6,sigzx,gradx,grady,gradz,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14, 
(符号规定: 拉正压负,地应力必须负，地应力为总应力) 
 
*IflagFastBalanceInSituStress 
0 
//0-默认值-非快速平衡  1-快速平衡地应力 
 
一行7 个数据 
*FixBoundary=nodeSetName 
1,vx,-1,-2,-3,-4,-5, 
2,vy,-1,-2,-3,-4,-5, 
3,vz,-1,-2,-3,-4,-5, 
4,w,xc,yc,zc,aix,-1,   (w 角速度,单位为弧度,逆时针为正,aix=1 绕x 轴旋转,aix=2 绕y 轴旋
转,aix=3 绕z 轴旋转) 
5,0,-1,-2,-3,-4,-5, (>=5,表示用户自定义边界) 
 
*FixEBoundary=elemSetName   (计算类型1-3 也可用,计算类型为4 时,只能使用该方式施加
刚体运动边界条件,约束施加在单元上) 
1,vx,-1,-2,-3,-4,-5, 
2,vy,-1,-2,-3,-4,-5, 
3,vz,-1,-2,-3,-4,-5, 
4,w,xc,yc,zc,aix,-1,   (aix=1 绕x 轴旋转,aix=2 绕y 轴旋转,aix=3 绕z 轴旋转) 
 
*SForceBoundary=lineElemSetName 
1,px,-1,-2,-3,-4,-5,  （与x 轴正向相同为正） 
2,py,-1,-2,-3,-4,-5, 
3,pz,-1,-2,-3,-4,-5, 
4,pn,-1,-2,-3,-4,-5,  （施加法向压力或者拉力,压为正） 
5,-1,-1,-2,-3,-4,-5,  （线边界是吸收边界） 
6,0,-1,-2,-3,-4,-5,   (>=6,表示用户自定义压力边界,吸收边界可在此处添加)

MultiFracS 5.8 输入数据文件格式 
-1,px,gradx,grady,gradz,-4,-5,  （与x 轴正向相同为正） 
-2,py,gradx,grady,gradz,-4,-5, 
-3,pz,gradx,grady,gradz,-4,-5, 
-4,pn,gradx,grady,gradz,-4,-5, 
 
//说明: 以上的力均为面力,单位为Pa 
 
*Iflagcrackmech 
0 
//0-力学计算中，不对裂缝施加压力边界,默认值 
//1-力学计算中，通过二次开发接口Sboundary.dll 对裂缝施加压力边界 
 
---------------------------------结构单元计算------------------------------------- 
*StructElemSet=GroupName  (1 行总共20 个数据) 
x1,y1,z1,x2,y2,z2,-6,elemsize,-8,itype1,value1,-11,itype2,value2,-14,lineType,aix,-17,-18,-19, 
//允许多行数据 
 
//锚杆两个端点坐标(x1,y1,z1)和(x2,y2,z2) 
//elemsize 锚杆离散尺寸，建议取值与实体单元尺寸一致 
//itype1 表示(x1,y1,z1)结构节点的类别 itype1=0-自由 ityp1e=1 绑定实体单元  
//itype1=2-固定该节点速度-取值为value itype1=3-固体该节点的力-取值为value    
//value 的符号为拉为正，压为负 即方向如果与x2,y2 指向x1,y1 点相同，则为正值 
//施加锚杆时，默认可见的一端为(x1,y1,z1) 
 
//itype2 表示(x2,y2,z2)结构节点的类别,itype2 和value2 的物理意义同itype1 和value1 
 
//lineType 表示线型类别 1-直线型（默认） 2-圆弧型 
//lineType=1 时，x1,y1,z1 和x2,y2,z2 分别为锚杆的两个端点 
 
//lineType=2 时，x1,y1,z1,x2,y2,z2 替换为x,y,z,radius,angle1,angle2 
//表示是从角度angle1 到angle2 的一段圆弧,0 度是x 轴正向 y 轴正向是90 度 
//0=<angle1<angle2<=360 
 
//lineType=2 时需要设置aix,表示生成圆弧的旋转轴 
//aix=1 绕x 轴旋转,aix=2 绕y 轴旋转,aix=3(默认值)绕z 轴旋转 
//emax 锚杆的极限轴向应变，超过该应变值，锚杆即断裂 
 
*MatStructElemSet=GroupName (1 行总共25 个数据) 
itype,ro,E,u,D,ft,fc,-7,ks,t,crg,cgb,phirg,phigb,sigz,-15,cb,-17,emax,-19,-20,-21,-22,-23,-24, 
//结构体类别=1,密度,弹性模量,泊松比,锚杆直径,锚杆抗拉强度,锚杆抗压强度,-7,水泥浆的
剪切刚度(N/m2),水泥浆厚度,岩石和浆液的粘结强度,浆液和锚杆的粘结强度,岩石和浆液的
摩擦系数,浆液和锚杆的摩擦系数,用户定义的不在本平面的应力,-15,锚杆粘滞系数,-
17,emax(锚杆的极限轴向应变),-19,残余粘结强度cr,残余摩擦系数fr,残余强度对应的剪切位
移u2,-23,-24,

MultiFracS 5.8 输入数据文件格式 
tao2=cr+fri*sigma 
tao2<0 则为双线性模型，且残余抗剪强度==峰值抗剪强度 
tao2>=0 且u2<=抗剪强度峰值/水泥浆剪切刚度  则为双线性模型 
tao2>=0 且u2>抗剪强度峰值/水泥浆剪切刚度  则为三线性模型 
 
*DampStruct 
IAtuoDampFlag,0.0,-2,-3,-4,-5,-6, 
(IAtoDampFlag==1 自动确定锚杆阻尼 
IAtoDampFlag==0，采用用户设定的锚杆阻尼,值为IAtoDampFlag 后面的数字 
如果没有以上关键词，则表示不设置锚杆阻尼，即锚杆阻尼为0 
锚杆阻尼一定不要太大，否则结果是错误的) 
 
---------------------------------流体计算------------------------------------- 
*Fluid  (1 行30 个数据) 
Ro,Kw,u,M,-4,iTypeFluid,tao,-7,Ktf,Cpf,-10,roi,Kti,Cpi,latent,p0,lamda,bta,-18,elai,vi,-21,elaw,vw,-
24,-25,-26,-27,-28,-29, 
 
Ro 裂隙流体的密度，Kw 裂隙流体的体积模量，u 裂隙流体的粘性，M 流体的比奥模量 
iTypeFluid=0 牛顿流体,此时tao=0, iTypeFluid=1 Bingham 流体,tao 为流体的屈服应力,Ktf 流体
的热传导系数，Cpf 流体的比热容,  
roi 冰的密度，Kti 冰的热传导系数，Cpi 冰的比热，latent 冰水相变潜热系数，p0 参考压力，
lamda 常数，bta 冰水相变的体膨胀系数 
elai 冰的弹性模量，vi 冰的泊松比，elaw 水的弹性模量，vw 水的泊松比 
 
*PoreFluid (1 行30 个数据，如果未设置这一项，则孔隙流体取*Fluid 的参数) 
Ro,Kw,u,M,-4,iTypeFluid,tao,-7,Ktf,Cpf,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-
25,-26,-27,-28,-29, 
 
Ro 孔隙流体的密度，Kw 孔隙流体的体积模量，u 孔隙流体的粘性，M 孔隙流体的比奥模量 
iTypeFluid=0 牛顿流体,此时tao=0, iTypeFluid=1 Bingham 流体,tao 为孔隙流体的屈服应力,Ktf
孔隙流体的热传导系数，Cpf 孔隙流体的比热容,  
 
*Proppant 
rop,dp,-2,-3,-4,-5,-6,-7,-8,-9, 
//rop 支撑剂密度,dp 支撑剂直径 
 
*InitCrackSat=nodeSetName 
1,crackSat,-2,-3,-4,-5,-6, 
2,-1,-2,-3,-4,-5,-6, (>=2，表示用户自定义初始条件) 
 
*InitCrackPressure=nodeSetName 
1,crackPre,pgy,pgz,-4,-5,-6, (线性变化的初始裂隙压力边界设置) 
2,-1,-2,-3,-4,-5,-6, (>=2，表示用户自定义初始条件)   
//说明pgy、pgz 的含义是: 将水压写成y、z 坐标的函数 crackPre+pgy*y+pgz*z 对于二维问

MultiFracS 5.8 输入数据文件格式 
题，pgz=0 
//设边界水压分布如下图，在施加水压边界上取两个不同点(y0,p0),(y1,p1)得到两个方程：  
//crackPre+pgy*y0=p0; crakPre+pgy*y1=p1,  
//求解该方程组得出pgy 和crackPre 
----(y0,p0) 
----- 
------ 
-------(y1,p1) 
 
//支撑剂初始条件 
*InitProppant=elemSetName 
1,c,-2,-3,-4,-5,-6, 
2,-1,-2,-3,-4,-5,-6, (>=2，表示用户自定义初始条件) 
//c 支撑剂的体积浓度 
 
*InitPoreSat=elemSetName 
1,poreSat,-2,-3,-4,-5,-6, 
2,-1,-2,-3,-4,-5,-6, (>=2，表示用户自定义初始条件) 
 
*InitPorePressure=elemSetName 
1,porePre,pgy,pgz,-4,-5,-6, 
2,-1,-2,-3,-4,-5,-6, (>=2，表示用户自定义初始条件) //说明pgy、pgz 的含义是: 将水压写成y、
z 坐标的函数 porePre+pgy*y+pgz*z 对于二维问题，pgz=0 
 
 
*FixCrackFluidFemNode=nodeSetName 
1,p,dp,maxp,pgy,pgz,-6,-7,-8,-9, 
2,q,dq,maxq,0,0,-6,-7,-8,-9, 
3,pb,h,0,0,0,-6,-7,-8,-9, 
4,-1,-2,-3,-4,-5,-6,-7,-8,-9,  //标记这些节点为张开以便允许流体流过 
itype,id,0,0,0,0,-6,-7,-8,-9,  //(itype>=5,表示用户自定义边界, id=1-自定义压力边界 id=2-自定
义流量边界-流量施加在单个节点上) 
 
//说明pgy,pgz 的含义是: 将水压写成y 坐标的函数 p+pgy*y+pgz*z  
 
//支撑剂边界条件 
*FixProppantFemNode=nodeSetName 
1,c,dc,maxc,-4,-5,-6,-7,-8,-9, 
2,q,dq,maxq,-4,-5,-6,-7,-8,-9,  //流量边界 
3,q,dq,maxq,-4,-5,-6,-7,-8,-9,  //流量密度边界 
itype,id,-2,-3,-4,-5,-6,-7,-8,-9, //(itype>=5,表示用户自定义边界, id=1-自定义压力边界 id=2-自
定义流量边界-流量施加在单个节点上  id=3-自定义流量密度边界)

MultiFracS 5.8 输入数据文件格式 
*FixPoreFluidFemNode=nodeSetName 
1,p,dp,maxp,pgy,pgz,-6,-7,-8,-9, 
2,q,dq,maxq,0,0,-6,-7,-8,-9,   //流量边界 流量施加在单个节点 
3,q,dq,maxq,0,0,-6,-7,-8,-9,   //流量密度边界  
itype,id,0,0,0,0,-6,-7,-8,-9,  //(itype>=5,表示用户自定义边界, id=1-自定义压力边界 id=2-自定
义流量边界-流量施加在单个节点上  id=3-自定义流量密度边界) 
 
//说明pgy,pgz 的含义是: 将水压写成y 坐标的函数 p+pgy*y+pgz*z  对于二维问题，pgz=0  
 
*PlaceWell=lineElemSetName  //布置线形井筒 一旦设定，将仅流过流体，但不给侧壁施加
流体压力，2D-要为线单元集合  3D-为面单元集合 
 
---------------------------------热学计算------------------------------------- 
*InitSolidTemperature=elemSetName 
1,solidTemp,-2,-3,-4,-5,-6, 
2,-1,-2,-3,-4,-5,-6, (>=2，表示用户自定义初始条件，注意最末尾的数字也紧跟逗号) 
 
*InitFluidTemperature=nodeSetName 
1,fluidTemp,-2,-3,-4,-5,-6, 
2,-1,-2,-3,-4,-5,-6, (>=2，表示用户自定义初始条件) 
 
*InitIceRatio=elemSetName 
1,iceRatio,-2,-3,-4,-5,-6, 
2,-1,-2,-3,-4,-5,-6, (>=2，表示用户自定义初始条件) 
//iceRatio 表示冰的质量占冰水混合物的总质量之比 
 
*FixSolidThermalFemNode=nodeSetName 
1,T,dT,maxT,-1,-2,-3,-4,-5,-6,  
2,qT,dqT,maxqT,-1,-2,-3,-4,-5,-6,  //qT 为流量  该流量施加在单个节点上 
3,qT,dqT,maxqT,-1,-2,-3,-4,-5,-6,  //qT 为流量密度 
4,Tb,h,0,-1,-2,-3,-4,-5,-6, 2018-1-18 添加-对流边界 Tb-边界所处环境的温度 h-边界的换热系
数 
itype,id,0,0,-1,-2,-3,-4,-5,-6,  //(itype>=5,表示用户自定义边界, id=1-自定义温度边界  id=2-
自定义流量边界-流量施加在单个节点上  id=3-自定义流量密度边界) 
 
*FixFluidThermalFemNode=nodeSetName 
1,T,dT,maxT,-1,-2,-3,-4,-5,-6,  
2,qT,dqT,maxqT,-1,-2,-3,-4,-5,-6, //qT 为流量， 该流量施加在单个节点上 
 
*Iflagcrackqt 
0 
//0-固体传热计算中,不对裂缝施加用户自定义的裂缝边界(默认值),1-固体传热计算中,对裂
缝施加用户自定义的裂缝边界

MultiFracS 5.8 输入数据文件格式 
-------------湿度计算（湿度=含水率=孔隙中水的质量/干燥岩土的重量）----------------- 
*InitMoisture=elemSetName 
1,w,-2,-3,-4,-5,-6,    (w 取大于0 的值,可以大于1) 
2,-1,-2,-3,-4,-5,-6, (>=2，表示用户自定义初始条件) 
 
*ShrinkageLimit 
0 
//缩限含水率 
 
一行10 个数据 
*FixSolidMoistureFemNode=nodeSetName 
1,w,dw,minw,-1,-2,-3,-4,-5,-6, 
2,qw,dqw,maxqw,-1,-2,-3,-4,-5,-6,  //qw 为质量流量 该流量施加在单个节点上 
3,qw,dqw,maxqw,-1,-2,-3,-4,-5,-6,  //qw 为质量流量密度 
4,wb,hw,0,-1,-2,-3,-4,-5,-6,  //对流边界 
5,w,bta,minw,-1,-2,-3,-4,-5,-6, 
itype,id,0,0,-1,-2,-3,-4,-5,-6,  //(itype>=6,表示用户自定义边界, id=1-自定义湿度边界  id=2-
自定义流量边界-流量施加在单个节点上  id=3-自定义流量密度边界) 
 
*Iflagcrackqw 
0 
//0-湿度计算中,不对裂缝施加用户自定义的裂缝边界(默认值),1-湿度计算中,对裂缝施加用
户自定义的裂缝边界 
 
---------------------------------监测设置------------------------------------- 
每行8 个数据 
*MonitorNode=nodeSetName    
itype,-1,-2,-3,-4,-5,-6,-7, 
(设置后，会输出zMonitor-Node 开头的.csv 文件，可在paraview 中打开该文件查看监测曲线, 
如果nodeSetName对应的是固定速度边界，该文件中还会输出外界通过该边界输入的能量， 
对于施加的面力边界，统计能量输入，可通过位移曲线以及输入的面力曲线，根据功的定义， 
自行数据处理求得) 
 
*MonitorElem=elemSetName   (2D-三角形单元集合 3D-四面体单元集合) 
itype,-1,-2,-3,-4,-5,-6,-7, 
(设置后，会输出zMonitor-Elem 开头的.csv 文件，可在paraview 中打开该文件查看监测曲线) 
 
*MonitorPoint=stringName  (一个stringName 只允许一行数据) 
x,y,z,-3,-4,-5,-6,-7,  
(设置后，会输出zMonitor-point 开头的.csv 文件，可在paraview 中可以打开该文件查看监测
曲线) 
 
*MonitorJoint=lineSetName  （2D-线单元集合  3D-面单元集合） 
itype,-1,-2,-3,-4,-5,-6,-7,

MultiFracS 5.8 输入数据文件格式 
(设置后，会输出zMonitor-Joint 开头的.csv 文件，可在paraview 中可以打开该文件查看监测
曲线) 
 
 
（31）输出监测点数据到文件的间隔  只输出一个文件 监测点的值随时间的变化 
*UpdateMonitorDataFrequency 
10000 
(对于GPU 计算，该参数取值不能太小，否则会显著影响计算速度并输出Copy_GPUdata2CPU) 
 
----------------------------整体计算设置------------------------------- 
(23) 计算类型 
*CalulationType 
1 
说明:  
(0-不考虑开裂) 
(1-连续） 
(2-离散）   
(3-连续-非连续) 
(4-刚体) 
(5-自适应有限-离散元法 AFDEM) 
(11-GPU 版本) 
通常指定为1 即可，如果是GPU 版，则可请指定为11 
 
(32) 涉及水热力三场的哪几个场 
*NumTHMpStep 
1,0,0  纯热学 
0,1,0  纯渗流 
0,0,1 纯力学 
(33)是否进行接触判断和接触力计算 
*DetectionContactForce 
1 
说明:  
(0-不进行接触判断和接触力计算,只有确定模拟的问题一定不会出现接触,才可以设置为0,这
样可极大提高计算速度) 
(1-进行接触判断和接触力计算) 
 
*MaxNumPossibleContact 
iAutoFlag,num,-2,-3,-4,-5,-6 
(最大可能接触数 iAutoFlag=1 表示自动确定（默认）num 不起作用; iAutoFlag=0 表示用户设
定，数值为num； 
只有当尚未出现step 1 的信息时就出现接触数太小时，才需要用户设定改值，其余情况一律
由软件自动确定, 
step 1 后才出现该信息，说明计算不收敛，出现爆炸，时间步长太大)

MultiFracS 5.8 输入数据文件格式 
*SetSearchRange 
IAutoFlag,xmin,xmax,ymin,ymax,zmin,zmax,-7, 
IAutoFlag=1，自动确定搜索范围，后面参数没有用到，默认值 
IAutoFlag=0，手动确定搜索范围 
 
*CloseDeleteElemCrossBoundary 
IFlag,xmin,xmax,ymin,ymax,zmin,zmax,-7, 
//自动删除越界单元 
说明： 
IFlag=1，关闭越界自动删除，后面参数没有用到，默认值 
IFlag=0，开启越界自动删除 
 
*SmallMove 
0 
(默认值0 0-表示关闭  1-开启，表示在打开接触情形下,仅对模型边界计算接触力) 
*FullContact 
0 
(默认值0 0-关闭全接触  1-开启全接触，一开始所有实体单元均进行接触判断及接触力计算) 
 
*SetDllToContactForce 
1 
(1-Cf2D/3D.dll 2-Cf2D/3D_vol.dll 3-嵌入量接触力算法  默认值取1) 
 
*RoundRadiusRatioContact 
IAtuoFlag,lamda,-2,-3,-4,-5,-6, 
(1-自动计算确定(默认) 0-采用后面设定的值  圆角半径是最短边长的lamda 倍,0<lamda<1) 
 
*SetDllToJoint 
1 
(1-曲线本构-默认值取1  2-曲线本构D 简化  3-D 简化折线本构(推荐)   
4-D 简化折线本构,使用用户设定的抗剪强度，且使得粘聚力co=抗剪强度fs，摩擦角不再起
作用，即不再使用摩尔库伦计算抗剪强度 
5-D 简化折线本构，考虑损伤不可逆（推荐）; 
6-D 简化折线本构，考虑损伤不可逆，断裂应变 
>=20 用户自定义节理单元本构 
) 
 
*SetJointCalulationType 
1 
(1-默认，2-方式2，3-方式3) 
 
*SpecifyContactBoundary=nodeSetName 
//说明一旦有该语句程序不再自动确定边界单元,如果需要程序自动确定,则注释掉该语句

MultiFracS 5.8 输入数据文件格式 
*DamageCriticalValue 
1 
说明: 取值范围[0,1],默认值1，当实体单元的损伤变量大于该临界值，即在后处理中不显示
该实体单元 
 
*OutChartType  //---输出曲线的类别 
2 
说明 1-Tecplot  2-ParaView(默认) 
 
*NumCPUCore 
0 
//设置程序使用的CPU 核数 0-表示程序使用的核数==CPU 拥有的核数 1-表示只使用1 个核,
程序相当于是串行的 
 
*ThreadPerBlock 
32 
//设置单个线程块的线程数，要求为32 的倍数 默认值32 
 
----------------------------力学设置---------------------------------------- 
*DampNode 
itype,IAtuoDampFlag,0.8,-3,-4,-5,-6, 
 
(默认关闭，itype=2---Flac 阻尼基于节点  itype=3----基于节点速度的粘性阻尼 
itype=4---基于节点速度的粘性阻尼(节点质量) 
推荐使用itype=3 即节点速率阻尼，具体取值需要用户参考自动计算值并根据模拟结果进行
调整 
IAtuoDampFlag=1 MultiFracS 自动确定阻尼取值  IAtuoDampFlag=0 采用用户设定的值 
) 
 
*DampStrainRate 
IAtuoDampFlag,0.0,-2,-3,-4,-5,-6, 
(默认开启，如果设置了节点速率阻尼，可以考虑将该阻尼关闭) 
 
*DampContact 
IAtuoDampFlag,Cn,Ct,-3,-4,-5,-6, 
(默认关闭，只有模拟中涉及接触碰撞，才需要设置) 
 
IAtuoDampFlag=1 自动计算阻尼,后面的参数没用到；  
IAtuoDampFlag=0 使用后面的参数设置为阻尼 
Cn-法向接触阻尼,Ct-切向接触阻尼 
 
(20) 强度折减系数   
*StrengthReductionMethod 
Fssr,-1    //2018-4-15 添加 强度折减系数 c'=c/Fsr, phi'=arctan(tan(phi)/Fsr)

MultiFracS 5.8 输入数据文件格式 
(21) 离心加载法  
*CentrifugalloadingMethod 
Fclm,-1       //2018-4-18 添加 g'=g*Fclm 
 
*ScaleMass  
1.0 
//质量缩放系数,用于提高静力问题计算速度,最大值不能超过100,一般情况下推荐取5 
 
*ScaleSize 
1.0 
//尺寸缩放系数 
 
*ScaleFluid 
1.0 
//缩放流体计算 
 
*ExpandShrinkWidth 
0 
//单元膨胀或者收缩宽度，默认值0，>0 膨胀 <0 表示收缩 
 
*BoundaryCoorflag 
1 
//施加边界条件时，基于初始坐标还是当前坐标 0-初始坐标 1-当前坐标 默认取1 
 
*TotalOrIncrementMethod 
0 
//0-全量法(默认) 1-增量法（如果开发自定义实体单元本构，需要采用增量法) 
 
------UCS,BD,UT 测试设置---------------- 
（36）指示是否进行单（三）轴压缩或者单轴拉伸 
*IFlagTestUCSUT 
id,xlb,ylb,xrt,yrt,-1,-2,-3,-4,-5, 
 
id=0 不进行(默认值）, id=1 进行单轴或三轴压缩(有加载板), id=2 进行单轴拉伸、单/三轴压
缩(无加载板） 
试样左下角的坐标(xlb,ylb) 
试样右上角的坐标(xrt,yrt) 
试样的轴向必须沿着y 轴 
如果是单轴压缩或拉伸试验，则必须设置id=1 或2 且xlb,ylb,xrt,yrt 要设置为gmsh 模型中试
样的左上角和右上角的坐标， 
否则将无法输出z-UCS 或z-UT 应力-应变曲线   
 
（37）指示是否进行巴西劈裂 
*IFlagTestBD

MultiFracS 5.8 输入数据文件格式 
Id,xc,yc,r,thick,-1,-2,-3,-4,-5, 
 
Id=0 不进行(默认值）;Id=1 进行巴西劈裂 
圆盘的中心坐标(xc,yc),圆盘的半径r， 
thick 圆盘的厚度 2D 时thick=1,3D 时根据实际取值 厚度方向必须沿着z 轴，竖向为y 轴，
水平为x 轴 
如果是巴西劈裂试验，则必须设置id=1 且xc,yc,r 要设置为gmsh 中圆盘模型的中心坐标和
半径，否则无法输出z-BD 曲线 
 
(38) 指示是否进行扭转试验  旋转轴为z 轴 
*IFlagTestTorision 
Id,w,xc,yc,zmin,zmax,-6,-7,-8,-9, 
Id=0 不进行(默认值);Id=1 进行扭转 
w 为旋转角速度 
xc,yc 为xy 平面上旋转中心坐标 
zmin,zmax 为试样在z 轴上的最小值和最大值 
 
(38) BD,UT,UCS 等基本岩石力学试验的监测数据到文件的输出间隔  监测点随时间的变化 
*UpdateBasicTestMointorFrequency 
100 
每隔100 步输出一组监测数据 
(对于GPU 计算，该参数取值不能太小，否则会显著影响计算速度并输出Copy_GPUdata2CPU) 
 
----------------------------渗流设置------------------------------ 
（33）指示在进行渗流计算时,是进行孔隙渗流计算,裂隙渗流计算,还是两者都进行 
*IFlagCrPoFlow 
0,0  不进行任何渗流计算 
1,0  纯裂隙渗流 
0,1  纯孔隙渗流 
1,1  同时进行孔隙渗流和裂隙渗流 
 
*ItypeCrFlow 
0 
//0-默认的裂隙渗流计算方式  1-大时间步长裂隙渗流计算方式 2-超快速裂隙渗流计算方
式 
 
（34）指示在进行渗流计算时,是进行饱和还是非饱和渗流 
*IFlag1Sat0UnSat  
1  饱和渗流 
0  非饱和渗流 
 
*IflagMech2CrPoFlow 
0,0 不考虑力学体积对渗流的影响 
1,0 考虑力学体积对裂隙渗流的影响

MultiFracS 5.8 输入数据文件格式 
0,1 考虑力学体积对孔隙渗流的影响 
1,1 同时考虑力学体积对裂隙渗流、孔隙渗流的影响 
//-----是否考虑力学体积变化对孔隙压力的影响 0-不考虑（默认值）1-考虑 
 
*IflagLeakoff 
0 裂隙渗流不考虑滤失(默认值) 
1 裂隙渗流考虑滤失 
 
*IflagPoreFluidToSolid //孔隙流体对固体的作用方式 
0 拖拽力 (默认值) 
1 有效应力 
 
*IflagProppant 
0  不考虑支撑剂运移 
1  考虑支撑剂运移 
 
 
(36)指示是否进行湿度计算 
*IFlagMoistureFlow 
0 不进行湿度计算 
1 进行湿度计算 
---------------------------传热设置------------------------------- 
(37) 指示在进行传热计算时,是否进行接触传热计算 
*IFlagContactHeat 
0 不进行接触传热计算 
1 进行接触传热计算 
*IFlagFricHeat 
0 不进行摩擦热计算 默认值 
1 进行摩擦热计算 
*IFlagCrfluidSolidHeat 
0,0 不进行任何传热计算 
1,0 仅进行裂隙内流体传热计算 
0,1 进行固体传热计算 
1,1 同时进行裂隙内流体和固体传热计算 
*IFlagCrFluidAdvection 
0 //不开启裂隙流体对流换热 
1 //开启裂隙流体对流换热 默认开启 
*IFlagPhaseHeat 
0 //不开启冰水相变热  默认不开启 
1 //开启冰水相变热 
 
---------------------每间隔多少步数新输出一个结果文件------------- 
*WriteNodeForceToRestoreFile=nodeSetName 
//涉及吸收边界、振动荷载时，需要在地应力平衡时对所有吸收边界、动荷载边界集合应用

MultiFracS 5.8 输入数据文件格式 
该命令 
（24）重启动文件输出的间隔 
*OutRestoreFileFrequency 
40000 
（26）结果文件的输出间隔  
*OutResultFileFrequency 
1000 
(对于GPU 计算，该参数取值不能太小，否则会显著影响计算速度并输出Copy_GPUdata2CPU) 
（31）连续介质应力+裂缝 文件的输出间隔 
*OutContinuumStresFileFrequency 
100000000 
(32) 输出节点信息.dat 文件输出间隔 
*OutNodeInfoData 
1000000000 
(对于GPU 计算，该参数取值不能太小，否则会显著影响计算速度并输出Copy_GPUdata2CPU) 
(33) 输出所有节理单元开度 
*OutAllJointApertureFileFrequency 
1000000000 
(对于GPU 计算，该参数取值不能太小，否则会显著影响计算速度并输出Copy_GPUdata2CPU) 
 
*OutBrokenSoftJointFileFrequency   
100000 
//控制含有broken-joint 或soft-joint 的.csv 文件输出间隔， 
//该文件含有破裂或软化节理单元的统计信息，可用于输出玫瑰图，指示优势裂纹方向 
 
*OutInsituPorePreCSV 
100000 
//控制含有-insitu-stress-pore-pressure-的.csv 文件输出间隔，输出应力场、孔隙压力场 
 
-----------------每间隔多少步数添加一组监测数据到文件或者控制台------------- 
（25）控制台中结果输出的间隔 
*UpdateConsoleResultFrequency 
100 
 
*TimeStepSize 
IAtuoTimeFlag,dletsT,deltfT,-3,deltpf,deltcf,-6,deltM,-8,deltW,-10,deltrb,-12,-13,-14,-15,-16,-17, 
 
说明:  
(IAtuoTimeFlag=1,程序自动计算时间步长,后面的参数不使用； 
IAtuoTimeFlag=0,采用后面给出的时间步长进行模拟计算 
dletsT 固体传热时间步长,deltfT 流体传热时间步长, 
deltpf 孔隙渗流时间步长,deltcf 裂隙渗流时间步长, 
deltM 力学计算时间步长, 
deltW 湿度计算时间步长,

MultiFracS 5.8 输入数据文件格式 
deltrb 锚杆计算时间步长 
 
进行力学+锚杆的计算时，需要设置力学时间步长==锚杆时间步长) 
 
*AdaptiveCrackFluidTimeStep 
0 
//0-非自适应(默认值) 1-自适应 
 
---------------------------------计算过程设置------------------------------------- 
*setAccuracy   
1e-6  //则表示系统的最大速度小于1e-6 时,即达到平衡,计算终止 
 
*Begin  //命令开始处 
 
-----------地应力平衡 
*solve 
*save geostress_balance.sav  //存储重启动文件 
 
-----------开挖-方案1 
*setdispzero 
*excavate elemSetName nstep 
*solve 
*save filename1.sav 
-----------施加锚杆 
*addrockbolt groupName 
*solve 
*save filename2.sav 
 
 
-----------开挖-方案2 
*restore geostress.sav 
*setdispzero 
*excavate elemSetName nstep 
*step 2000 
*save filename3.sav 
-----------施加锚杆 
*addrockbolt groupName 
*solve 
*save filename4.sav 
 
 
-----------开挖-方案3 
*restore geostress.sav 
*setdispzero //位移清零

MultiFracS 5.8 输入数据文件格式 
*excavate elemSetName nstep  //表示先在nstep 内将开挖区弹性模量降低为0，然后挖掉，
nstep>=0 
*step 2000 
*backfill elemSetName  //回填 
*save filename5.sav 
-----------施加锚杆 
*addrockbolt groupName 
*solve 
*save filename6.sav 
 
*settimezero //时间重置为0 
 
*setstressallzero  //将整个模型应力清零 
*setstresszero elemSetName //将集合的应力清零 
*setvelzero //将速度清零 
 
*initvel //读入重启动文件后，再次根据.inp 文件设置初速度，用于重启动后，设置不同的初
速度问题 
*outvtkfile 
 
*vexcavate //配合Exca.dll 二次开发接口一块使用 
 
*plug itype  //暂堵 itype 一个识别数字，会传入到Plug.c 中 
*move elemSetName dx dy dz  //将一个集合整体移动(dx,dy,dz)这个矢量 
 
*modifyMat elemSetName  //动态修改区域集合的参数 
第一行（总共60 个数据） 
IeType,密度(初始时的天然密度),E(弹性模量),u(泊松比),pn(法向接触罚参数),ps(切向接触罚
参数),接触内摩擦角,-7,kf11(渗透率),kf22,kf33,kf12,kf23,kf31,-14,Biot 系数,孔隙率,应力渗透率
耦合参数,突变系数,-19,kT11(热传导系数),kT22,kT33,kT12,kT23,kT31,-26,Cp(比热容),tec(热膨
胀系数),htc( 接触换热系数),-30,kM11( 湿度传导系数),kM22,kM33,kM12,kM23,kM31,-
37,msf(湿度收缩系数),-39,ft(实体单元抗拉强度),fc(实体单元抗压强度),-42,-43,-44,-45,-46,-
47,-48,-49,-50,-51,-52,-53,-54,-55,-56,-57,-58,-59, 
第二行（总共60 个数据） 
IbkFlag,c(粘聚力),phi(内摩擦角),ft(抗拉强度),fs(取1e15 不用修改),pfn(节理单元法向罚参
数),pfs(节理单元切向罚参数),GfI(I 型断裂能),GfII(II 型断裂能),-9,a0(初始张开度),amin(张开度
最小值),amax(张开度最大值),-13,hTfr(水岩换热系数),-15,hTnbj(未断裂节理单元换热系
数),dhTnbj(节理单元断裂时换热系数hnbj 的折减系数),-18,hFnbj(未断裂节理单元换流系
数),hFpof( 孔隙- 裂隙渗流在裂隙处的换流系数),-21,hMnbj( 未断裂节理单元换湿系
数),dhMnbj(断裂节理单元换湿系数的浙减系数),-24,该组节理处两侧附近三角形单元的接触
内摩擦角,-26,-27,-28,-29,am0(力学虚拟张开量>=0),-31,dd(3D 时为倾向，2D 为自x 轴到层理
面的夹角angle，逆时针为正,x 轴水平,y 轴竖直),dip(3D 时为倾角,2D 填写-33 即可),c_min(垂
直于层理粘聚力),phi_min(内摩擦角),ft_min(抗拉强度),GIf_min,GIIf_min,-38,-39,kTc(延裂缝的
热扩散系数),-41,kmc(延裂缝的湿度扩散系数),-43,-44,-45,-46,-47,-48,-49,-50,-51,-52,-53,-54,-

MultiFracS 5.8 输入数据文件格式 
55,-56,-57,-58,-59, 
 
*modifyJoint lineElemSetName  //动态修改节理线集合的参数 
IbkFlag,c(粘聚力),phi(内摩擦角),ft(抗拉强度),fs(取1e15 不用修改),pfn(节理单元法向罚参
数),pfs(节理单元切向罚参数),GIf(I 型断裂能),GfII(II 型断裂能),-9,a0(初始张开度),amin(张开度
最小值),amax(张开度最大值),-13,hTfr(水岩换热系数),-15,hTnbj(未断裂节理单元换热系
数),dhTnbj(节理单元断裂时换热系数hnbj 的折减系数),-18,hFnbj(未断裂节理单元换流系
数),hFpof( 孔隙- 裂隙渗流在裂隙处的换流系数),-21,hMnbj( 未断裂节理单元换湿系
数),dhMnbj(断裂节理单元换湿系数的折减系数),-24,该组节理处两侧附近三角形单元的接触
内摩擦角,imat1,imat2,eflag,-29,am0(力学虚拟张开量>=0),-31,dd(3D 时为倾向，2D 为自x 轴到
层理面的夹角angle，逆时针为正,x 轴水平,y 轴竖直),dip(3D 时为倾角,2D 填写-33 即
可),c_min(垂直于层理粘聚力),phi_min(内摩擦角),ft_min(抗拉强度),GIf_min,GIIf_min,-38,-
39,kTc(延裂缝的热扩散系数),-41,kmc(延裂缝的湿度扩散系数),-43,-44,-45,-46,-47,-48,-49,-50,-
51,-52,-53,-54,-55,-56,-57,-58,-59, 
 
*modifyIbkFlagMat elemSetName 
1 
//1-区域内节理单元断裂 0-区域内节理单元未断裂 
 
*modifyIbkFlagJoint LineElemSetName 
1 
//1-线集合指定的节理单元断裂 0-线集合指定的节理单元未断裂 
 
//*restore 命令会将MultiFracS 状态恢复到.sav 文件的状态（位置、速度、节理单元断裂状
态）， 
//如果*restore .sav 的inp 文件相对于该.sav 文件有更新节理单元的断裂状态，那么*restore
的使用，将会使得这些更新无效， 
//如果要保持这些更新，请在*restore 命令后使用*modifyIbkFlagMat elemSetName 或
*modifyIbkFlagJoint LineElemSetName 命令， 
//再次设置这些节理单元的断裂状态 
 
*geosolve //快速地应力平衡求解，本次求解是进行地应力平衡 
 
*End 
---------------------------------------------------------------------------------- 
 
后处理数据格式 
文件名.vtk 文件 输出云图分布 
Coor 坐标矢量，有x,y,z 三个方向的分量 
Tf_1 裂隙内流体温度 
Ts_1 固体温度 
Ts_2 固体温度 
U 位移矢量，有x,y,z 三个方向的分量 
V 速度矢量，有x,y,z 三个方向的分量



---

## 第 21 页开始

MultiFracS 5.8 输入数据文件格式 
crflow 裂隙流量 
crpre 裂隙压力 
crsat 裂隙饱和度 
fluidV 流体速度矢量，有x,y,z 三个方向的分量 
heatE 单元热能增量，相对初始状态 
id 材料分区编号 
maxprinstress 最大主应力，拉为正、压为负 
maxshearstress 最大剪应力 
minprinstress 最小主应力 
maxprinstrain 最大主应变，拉为正、压为负 
maxshearstrain 最大剪应变 
minprinstrain 最小主应变 
von_mises_stress  冯米塞斯应力 
moisture_1 湿度 
moisture_2 湿度 
poflow_1 孔隙流量 
poflow_2 孔隙流量 
popre_1 孔隙压力 
popre_2 孔隙压力 
posat_1 孔隙饱和度 
posat_2 孔隙饱和度 
sigma 应力张量 0-8 分别为sigmaxx sigxy sigyz; sigmayx, sigmayy, sigmayz; sigmazx, sigmazy, 
sigmazz; 
strain 应变张量 0-8 分别为exx exy eyz; eyx, eyy, eyz; ezx, ezy, ezz; 
 
带有后缀_1,_2 的变量，inp 文件中*CalulationType 为1 时看_1 的变量，*CalulationType 为2
和3 时看_2 的变量即可 
 
文件名-crack-I.vtk  拉伸裂纹 
文件名-crack-II.vtk 剪切裂纹 
文件名-crack-III.vtk 拉剪混合裂纹 
文件名-crack-ini.vtk 初始裂纹 
文件名-crack-interface.vtk 交界面 
 
文件名-AE-energy-.vtk 文件  输出声发射分布图 
AE_energy(J) 声发射释放的能量大小 
 
文件名-stress-.vtk 文件 输出为未断裂前连续的应力分布 
变量名同 文件名.vtk 文件 
 
文件名-joint-aperture-.vtk 输出所有节理单元的张开度 
Aperture_mech(m) 力学法向张开度 
Slip_mech(m) 力学切向滑移量 
Aperture_seepage(m) 渗流法向张开度

MultiFracS 5.8 输入数据文件格式 
 
文件名-jstress-.vtk 输出*Joint 指定的线单元集合上的应力分布，用于监测衬砌受到的围岩压
力 
jsigma(Pa) 法向应力 
jtau(Pa) 切向应力 
 
文件名-principal-stress-direction-.vtk 输出主应力方向图 又称为主应力轨迹线图 
stress_value 应力值的大小 
stress_sign 应力的符号 拉正压负 
 
文件名-rockbolt-.vtk 输出锚杆的轴力、剪力等云图信息 
 
文件名-fragment-.vtk 输出块度分布图 
文件名-fragment-.csv 
fragment_id  area(m2)/Volume(m3) 
块体编号      块体面积(2D)/块体体积(3D) 
 
zMat-distribution-solid.vtk 输出实体单元材料分布 
Ela 弹性模量 
v 泊松比 
kT 热传导系数 
tec 热膨胀系数 
km 湿度扩散系数 
alfa 湿度收缩或者膨胀系数 
 
zMat-distribution-joint.vtk 输出节理单元材料分布 
ft 抗拉强度 
co 粘聚力 
fric 内摩擦角 
gi I 型断裂能 
gii II 型断裂能 
Aperture_mech 力学法向张开量 
 
文件名-broken-joint.csv  输出断裂节理单元的几何和类别信息，用于生成节理玫瑰花图，分
析优势破裂方向 
joint_id 断裂节理单元的编号 
angle(°) 断裂节理单元的角度（与x 轴正向的夹角） 
length(m) 断裂节理单元的长度 
type 断裂节理单元的类型 10-初始裂缝 11-拉破坏 12-剪切破坏 13-拉剪破坏 
nx,ny,nz 3D 时节理单元的单位法向向量 
area(m2) 3D 时节理单元的面积 
 
文件名-soft-joint.csv  输出软化节理单元的几何和类别信息，用于生成节理玫瑰花图，分析
优势软化方向

MultiFracS 5.8 输入数据文件格式 
joint_id 软化节理单元的编号 
angle(°) 软化节理单元的角度（与x 轴正向的夹角） 
length(m) 软化节理单元的长度 
type 软化节理单元的类型 10-初始裂缝 11-拉破坏 12-剪切破坏 13-拉剪破坏 
nx,ny,nz 3D 时节理单元的单位法向向量 
area(m2) 3D 时节理单元的面积 
 
zmhis.csv 或zmhis.dat 中各个变量的含义 
1: nhcstep 整体计算步数 
2: ncfstep 流体计算步数 
3: nctstep 热学计算步数 
4: ncmstep 力学计算步数 
5: t_mech(s) 力学时间 
6: t_fluid(s) 流体时间 
7: amax_act(m) 裂缝最大实际张开度 
8: xm_crack_tip(m) 裂缝尖端的x 坐标 
9: nbj 断裂节理单元的总数目 
10: nbjt 拉伸断裂节理单元的数目 
11: nbjs 剪切断裂节理单元的数目 
12: nbjts 拉剪断裂节理单元的数目 
12: nbj_space  一定间隔时间步内的断裂节理单元的数量 
13: nbjt_space 一定间隔时间步内的拉伸断裂节理单元的数量 
14: nbjs_space 一定间隔时间步内的剪切断裂节理单元的数量 
15: volume_crack(m3) 裂缝的体积 
16: area_crack(m2) 裂缝的面积 
interface_crack_area(m2) 断裂的界面的面积 
interface_crack_length(m) 断裂的界面的长度 
interface_crack_volume(m3) 断裂的界面的体积 
17: water_average 平均湿度 
18: damage_area(m2) 损伤单元的面积 2D 
19: damage_area(m3) 损伤单元的体积 3D 
18: dEkbj(J)  从0 时刻起累计的声发射能量 
19: dEkbjt(J) 从0 时刻起累计的拉破坏声发射能量 
20: dEkbjs(J) 从0 时刻起累计的剪切破坏声发射能量 
21: dEkbjts(J) 从0 时刻起累计的拉剪混合破坏声发射能量 
21: dEkbj_space(J) 输出间隔内累计的声发射能量 
22: dEkbjt_space(J) 输出间隔内累计的拉破坏声发射能量 
23: dEkbjs_space(J) 输出间隔内累计的剪切破坏声发射能量 
24: dEkbjts_space(J) 输出间隔内累计的拉剪混合破坏声发射能量 
24: Ethermal(J) 热能 
25: Ek(J) 动能 
26: Es(J) 应变能 
27: Eg(J) 重力势能 
28: E(J)总能量

MultiFracS 5.8 输入数据文件格式 
29: grout_ratio 注浆率 
30: sumTf 流体温度之和 
31: sumTs 固体温度之和 
32: sumPc 裂隙压力之和 
33: sumPs 孔隙压力之和 
34: sumW 湿度之和 
 
zMonitor-Node 开头的.dat 或.csv 文件各个变量的含义 
Wx(J) 如果该边界是固定速度边界，此处表示通过该边界延着x 方向累计输入的能量(做功) 
Wy(J) 如果该边界是固定速度边界，此处表示通过该边界延着y 方向累计输入的能量(做功) 
Wz(J) 如果该边界是固定速度边界，此处表示通过该边界延着z 方向累计输入的能量(做功) 
W(J) 如果该边界是固定速度边界，此处表示通过该边界输入的能量(做功) 
 
sumpoflow_1 累计孔隙流量 (从0 时刻到当前时刻) 
sumpoflow_2 累计孔隙流量 
sumcrflow 累计裂隙流量 
sumsTflow_1 累计固体热流量 
sumsTflow_2 累计固体热流量 
sumfTflow 累计流体热流量 
sumwflow_1 累计湿度质量流量 
sumwflow_2 累计湿度质量流量 
同上 
 
zMonitor-Elem 开头的.dat 或.csv 文件各个变量的含义 
同上 
 
zMonitor-point 开头的.dat 或.csv 文件各个变量的含义 
同上 
 
zMonitor-Joint 开头的.dat 或.csv 文件各个变量的含义 
同上 
 
Z-BD 开头的.dat 或.csv 文件各个变量的含义   巴西劈裂试验曲线 
1: step 计算步数 
2: Uy 加载的竖向位移绝对值 
3: Fy 竖向加载力的大小 
4: s 根据巴西劈裂测试抗拉强度公式换算得到的拉应力 
其余变量同上 
 
z-UCS 开头的.dat 或.csv 文件各个变量的含义   单/三轴压缩试验曲线 
4: e1 竖向应变 
5: e2 横向应变 
6: ev 体积应变 
7: s 竖向压应力

MultiFracS 5.8 输入数据文件格式 
8: E 试样弹性模量 
9: m 试样的泊松比 
10: s_ana 竖向压应力解析解 
11: E_ana 输入的弹性模量 
12: m_ana 输入的泊松比 
 
z-UT 开头的.dat 或.csv 文件各个变量的含义  单轴拉伸或者无加载板的单/三轴压缩试验 
同上 
 
z-time-step.dat 文件 可以查看MultiFracS 采用的计算时间步长， 
当时间步长是MultiFracS 自动确定时，可以通过该文件查看MultiFracS 自动确定的时间步长
的大小 
 
z-elem-info.dat 文件  可以查看实体单元数量、节理单元数量、节点数 
hmin 实体单元高的最小值，hav 实体单元高的平均值，hmax 实体单元高的最大值 
lenmin 实体单元边长的最小值，lenav 实体单元边长的平均值，lenmax 实体单元边长的最大
值 
 
z-elem-edge-length-per-elem-info.dat  可以查看实体单元的最短的高 
单元编号 单元最短的高 
 
z-damp.dat 可以查看MultiFracS 采用的阻尼大小 
如果阻尼是MultiFracS 自动确定的，可以通过该文件查看MultiFracS 自动确定的阻尼的大小， 
如果觉得自动确定阻尼不合适，则可以该文件中的阻尼值作为参考调整阻尼大小 
 
z-contact.dat 可以查看MultiFracS 确定的最大可能接触数，如果觉得该值不合适，用户可以
该文件中的最大可能接触数为参考，调整最大可能接触数的取值 
 
zConsolePrint-.dat 文件 可以查看MultiFracS 控制台中输出的所有信息，如果MultiFracS 出现
闪退，可以通过这个文件确定其在闪退前输出的步数等相关信息 
 
文件名-node-info-步数.csv  输出数据格式 
节点信息 
*Node 
 
*Telem_info 
i0,i1,i2 
 
*Broken_joint_info 
x0,y0,x1,y1,x2,y2,x3,y3 
 
--------------------前处理建模-------------------------------------------- 
对于采用abaqus 建模生成的.inp 文件，请在生成.inp 文件前， 
在abaqus 界面下方的命令行窗口输入如下命令，并按Enter 键:

MultiFracS 5.8 输入数据文件格式 
mdb.models['Model-1'].setValues(noPartsInputFile=ON) 
 
对于复杂模型建模，如果在gmsh 中建模不方便， 
可以用abaqus,catia,solidworks 等第三方软件建立几何模型，导出.stp 或.step 文件， 
然后在gmsh 中打开这些.stp 或.step 文件，建立集合，划分网格，最后生成.inp 文件， 
通过这种方式，任意复杂的模型都是可以建立起来的 
 
MultiFracS 可以处理neper 软件生成的泰森多边形： 
neper 输出.geo 文件 
gmsh 中打开.geo 文件，生成网格，导出.inp 文件 
不在inp 文件添加材料等信息，直接打开MultiFracS 输入：inp 文件名 -group 
按照提示输入分组数量和各组占的比例，即可以在原有.inp 文件末尾添加分组集合信息 
然后再按照常规流程赋给材料、边界等信息，然后进行计算即可 
对于不同分组界面的节理单元材料参数指定，则可以通过*JointBetweenMat=imat1,imat2 来
实现

