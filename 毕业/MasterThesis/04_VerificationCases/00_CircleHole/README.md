# 00_CircleHole — 圆孔应力集中算例（历史验证）

**状态：** 已完成（成功方案 S2，见 DevelopmentHistory.md）
**平台：** MultiFracS 2026-05-08 团队版
**本构：** MC（Mohr-Coulomb），Ce3D 四面体

## 已完成的验证

- psi=30°（关联流）：曲线趋势吻合 Salencon 解析解，误差可接受
- psi=0°（非关联流）：位移场与 psi=30° 不同（正确），但收敛性待改进

## 文件说明

- `Input/mc_tunnel_circle_flac81_dil0_multifracs.inp` — MultiFracS 计算文件（FLAC F2D426算例配置）

## 与本论文的关系

此算例为 MC 本构的**已完成**验证，不在本论文最终章节中。
仅作为参数验证参考，对应 `DevelopmentHistory.md` S2。
