## Energy Model for JUNO

#### Some Questions:

1. Quenched energy distribution is asymmetrical.

   can find some clues in dEdx distribution which is not symmetric too.

   <img src="/Users/yumiao/Documents/Nutstore/Works/Simulation/Nonlinearity/dEdx.png" alt="dEdx" style="zoom:50%;" />

The asymetry could have connection with step number...(in a step, the dE/dx --> quenching is the the same)



2. Ionisation delta-electron KE:

   e-e- elastic scattering --> Mollor scattering: infrared divergence in cross section... The importance of production cut... 微分散射截面参数化，对不同的element进行拟合。

   <img src="/Users/yumiao/Documents/Nutstore/Works/Simulation/Nonlinearity/electronKE.png" alt="ElectronKE" style="zoom:50%;" />

   3. 积分gamma-e+-概率谱的结果略偏小：secondary particle number 分布

      <img src="/Users/yumiao/Documents/Nutstore/Works/Simulation/Nonlinearity/secon_number.png" style="zoom:50%;" />

      secondary number=2附近的peak来自于对产生，导致整体分布不对称。
      
      

## Bottleneck Problem: Energy Resolution Model

**How to connect single-energy gamma resolution with multiple single-electron energy resolution ??**

Simplification of Problem:

假如一个随机变量**x**可以通过两种方式抽样得到，这两种方式有确定的比例：

1. 由8次从分布1随机抽样之和构成；（比例0.7）
2. 由3次从分布2抽样加上两次从分布1抽样得到（比例0.3）

（分布1， 分布2的均值和标准差均已知）

如何估计x的均值和标准差？





由于每个gamma沉积能量的方式是不同的（产生的次级粒子的数目和能量是不同的），由于不同能量的电子的非线性是不同的，因此gamma的totalPE就会被展宽。相当于是从多个中心值不同的分布中按各自的概率去做抽样，可以通过数学证明其标准差不能写成不同能量的电子的方差按概率求和后开根号（如果中心值一样可以这么计算）

**可以看到能量分辨率是强烈耦合非线性的**

- 五个参数的非线性model可以借助电子的非线性和Geant4的电磁相互作用模拟较好地预期gamma非线性，但非线性模型本质是得到Evis的平均值相对于Etrue的大小，无法表征Evis的涨落，因此无法给出分辨率的预期；之前的预期也是基于模拟中电子的涨落+电磁相互作用模型==> 预期gamma的涨落；分辨率模型依赖于非线性模型但不能cross check非线形模型的参数；是否考虑完全依赖模拟预期分辨率？？
- 分辨率差的一个intrinsic原因是由于非线性？（especially for gamma...）unless, 可以区分Cerenkov光子并从totalPE中分离出来以减少弥散；
- OP的涨落更大，更严重偏离泊松涨落，totalPE的涨落偏离泊松分布得较小；主要是CerenkovOP涨落很大，经过光学过程后弥散减小



## 通过预期单个Event的totalPE分布并统计大样本的单个Event建立gamma的Resolution Model？

<img src="/Users/yumiao/Documents/Works/github/energyModel_juno/resolution/md_fig/SecondarySample.png" style="zoom:40%;" />

在这个计算里采取了分bin，10keV/per bin. 假设每一种沉积过程最后的totalPE是高斯分布，例如统计了1000个事例，就能得到1000个高斯分布的mean（利用电子非线性曲线计算或从模拟里得到）和sigma（从模拟里拿到对应Ebin的电子的分辨率）。 然后做MC抽样，每个分布等概率进行抽样得到一个totalPE值。多次抽样后观察totalPE的分布。可以看到这种方法会高估分辨率：

<img src="/Users/yumiao/Documents/Works/github/energyModel_juno/resolution/md_fig/1MeVgamma_resl.png" style="zoom:40%;" />



