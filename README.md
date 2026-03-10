# 项目介绍

这是一个基于QML/C++的音乐播放器，模仿网易云音乐桌面客户端，主要是用来练习QML构建前端、QML与C++后端交互

<table>
  <tr>
    <td><img width="400" src="https://github.com/user-attachments/assets/42b7aca2-213f-4762-b150-6fcd4dc08771" />
</td>
    <td><img width="400" alt="image" src="https://github.com/user-attachments/assets/244233f5-8f6c-4b23-b023-ab4c0a669a26" /></td>
  </tr>
  <tr>
    <td><img width="400" alt="image" src="https://github.com/user-attachments/assets/4d937384-e21d-4e3a-9452-f94f2851a32d" /></td>
    <td><img width="400" alt="image" src="https://github.com/user-attachments/assets/707aaa75-6dab-4e5c-bd99-fa8c83cdcf06" /></td>
  </tr>
  <tr>
    <td><img width="400" src="https://github.com/user-attachments/assets/bcdccd74-04e4-4734-bc40-d868c2731080" />
</td>
    <td><img width="400" src="https://github.com/user-attachments/assets/20bb91db-e2a1-4394-8be7-1d9ef7b0f2ad" /></td><
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

cmake --build build --target install --config Debug

```
> ⚠<QT_DIR>是你本地的Qt安装目录，如在我电脑上是D:\Qt\Qt6.5.3\6.5.3\msvc2019_64

3. **构建UuPlayer**
```powershell
cd ../../src

cmake -B build -S . -DCMAKE_PREFIX_PATH=<QT_DIR> -DQWindowKit_DIR="../libs/qwindowkit/install/lib/cmake/QWindowKit"

cmake --build build

```

## 运行UuPlayer需安装并启动网易云音乐NodeJS版API

[指南](https://neteasecloudmusicapi.js.org/)















