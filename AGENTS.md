# AGENTS.md - 开发指南

## 项目简介

LegionAntinoise 是一个用于消除联想拯救者笔记本电脑电路啸叫声的C++工具。通过使用miniaudio库播放无声音频来消耗多余电流，从而抑制啸叫。

## 构建命令

### Visual Studio (Windows)
```bash
# 打开解决方案并构建
msbuild LegionAntinoise.sln /p:Configuration=Release /p:Platform=x64

# 调试构建
msbuild LegionAntinoise.sln /p:Configuration=Debug /p:Platform=x64
```

### Visual Studio IDE
1. 打开 `LegionAntinoise.sln`
2. 选择配置：Debug 或 Release
3. 平台：x64
4. 按 F5 运行调试，或 Ctrl+Shift+B 构建

## 代码风格指南

### 命名规范
- **文件名**: 小写，使用下划线分隔（如 `main.cpp`）
- **类名**: PascalCase（如 `AudioPlayer`）
- **函数名**: camelCase（如 `playAudio()`）
- **变量名**: camelCase（如 `sampleRate`）
- **常量**: 全大写，下划线分隔（如 `SAMPLE_RATE`）
- **私有成员**: 下划线前缀（如 `_isRunning`）

### 格式化
- 缩进：4个空格
- 大括号：同层缩进，单独一行
- 行长度：不超过100字符
- 注释：使用 `//` 单行，`/* */` 多行

### 示例
```cpp
// 常量定义
const int SAMPLE_RATE = 48000;

// 类定义
class AudioPlayer {
public:
    AudioPlayer(int sampleRate);
    ~AudioPlayer();
    
    bool initialize();
    void play();
    
private:
    int _sampleRate;
    bool _isInitialized;
};
```

## 错误处理

- 使用异常处理关键错误
- 函数返回值表示操作成功/失败
- 使用日志记录错误信息（std::cerr 或日志库）
- 资源管理使用 RAII 模式

## 依赖管理

- miniaudio：单头文件音频库（位于 `miniaudio/`）
- Windows SDK：用于音频API
- Visual Studio 2022 或更高版本

## Git 规范

### 提交信息格式
```
<type>: <subject>

<body>

<footer>
```

### 类型
- `feat`: 新功能
- `fix`: 修复
- `docs`: 文档
- `style`: 格式化
- `refactor`: 重构
- `perf`: 性能优化
- `test`: 测试
- `chore`: 构建/工具

### 示例
```
feat: 添加音量控制功能

实现了音量滑块控制，范围0-100

Closes #123
```

## 调试技巧

1. 使用 Visual Studio 调试器设置断点
2. 查看音频设备枚举输出
3. 检查 miniaudio 初始化日志
4. 使用 Process Monitor 查看系统调用

## 发布流程

1. 更新版本号（在资源文件和代码中）
2. 构建 Release 版本
3. 运行测试
4. 创建 Git 标签：`git tag -a v1.0.0 -m "版本 1.0.0"`
5. 推送标签：`git push origin v1.0.0`
6. 在 GitHub 创建 Release

---

*最后更新：2025年3月*
