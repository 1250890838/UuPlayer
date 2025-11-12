# 项目介绍

这是一个基于QML/C++的音乐播放器，模仿网易云音乐桌面客户端，主要是用来练习QML构建前端、QML与C++后端交互

<table>
  <!-- 第一行，第一张图片跨两列 -->
  <tr>
    <td colspan="2">
      <img src="https://github.com/user-attachments/assets/d1d8a312-89df-4fe0-bc85-b914200c95bc" width="800"/>
    </td>
  </tr>

  <!-- 第二行，剩下四张图片，2x2 -->
  <tr>
    <td><img src="https://github.com/user-attachments/assets/9ea1500d-970d-43c5-afe4-b78d860429d5" width="400"/></td>
    <td><img src="https://github.com/user-attachments/assets/a7083747-dc30-4ef9-8bb3-0c41124634a0" width="400"/></td>
  </tr>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/ca347830-c3b7-43cf-bb2a-507b61cc2dad" width="400"/></td>
    <td><img src="https://github.com/user-attachments/assets/14c904c3-27d5-46f4-abf0-a4e9eea88f02" width="400"/></td>
  </tr>
</table>

---



## 如何构建


### 依赖项

在开始构建之前，请确保你已经安装了以下依赖：

- **操作系统**：
  - Windows 10/11
- **编译工具**：
  - Visual Studio 2019 或以上
  - CMake 3.16 及以上
- **库依赖**：
  - Qt 6 (Quick, Gui, Multimedia, Network)
  - QWindowKit

---

### 构建步骤

1. **克隆仓库（包含子模块）**  
```powershell
git clone --recursive https://github.com/1250890838/UuPlayer.git

cd UuPlayer
```

2. **先构建并安装QWindowKit**
```powershell
cd libs

cd QWindowKit

cmake -B build -S . -DQWINDOWKIT_BUILD_QUICK=ON -DCMAKE_PREFIX_PATH=<QT_DIR> -DCMAKE_INSTALL_PREFIX="./install"

cmake --build build

```
> ⚠<QT_DIR>是你本地的Qt安装目录，如在我电脑上是D:\Qt\Qt6.5.3\6.5.3\msvc2019_64

3. **构建UuPlayer**
```powershell
cd ../src

cmake -B build -S . -DCMAKE_PREFIX_PATH=<QT_DIR> -DQWindowKit_DIR="../libs/qwindowkit/install/lib/cmake/QWindowKit"

cmake --build build

```

## 运行UuPlayer需安装并启动网易云音乐NodeJS版API

[指南](https://neteasecloudmusicapi.js.org/)















