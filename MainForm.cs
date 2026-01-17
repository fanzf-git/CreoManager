using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using Microsoft.Win32;
using Newtonsoft.Json;

namespace BIMManager
{

    public partial class MainForm : Form
    {
        private string creoPath;
        private IntPtr wrapperPtr = IntPtr.Zero;

        [DllImport("CreoWrapper.dll")]
        private static extern IntPtr Wrapper_New();

        [DllImport("CreoWrapper.dll")]
        private static extern void Wrapper_Delete(IntPtr w);

        [DllImport("CreoWrapper.dll")]
        private static extern bool InitCreo(IntPtr w, [MarshalAs(UnmanagedType.LPWStr)] string path);

        [DllImport("CreoWrapper.dll")]
        private static extern void CloseCreo(IntPtr w);

        [DllImport("CreoWrapper.dll")]
        private static extern bool CreatePart(IntPtr w, ref PartParams p);

        [DllImport("CreoWrapper.dll")]
        private static extern bool CreatePartFromJson(IntPtr w, [MarshalAs(UnmanagedType.LPWStr)] string json);

        public MainForm()
        {
            InitializeComponent();
            wrapperPtr = Wrapper_New();
            creoPath = GetCreoParametricPath();
        }

        /// <summary>
        /// 从注册表读取 Creo Parametric 的安装路径
        /// </summary>
        /// <returns>parametric.exe 的完整路径，如果未找到则返回 null</returns>
        private string GetCreoParametricPath()
        {
            // 尝试从注册表读取安装路径
            string[] registryPaths = new[]
            {
                @"SOFTWARE\PTC\Creo Parametric",
                @"SOFTWARE\PTC\Creo",
                @"SOFTWARE\WOW6432Node\PTC\Creo Parametric",
                @"SOFTWARE\WOW6432Node\PTC\Creo"
            };

            // 首先尝试从 PTC 注册表键读取
            foreach (var baseKey in registryPaths)
            {
                try
                {
                    using (var key = Registry.LocalMachine.OpenSubKey(baseKey))
                    {
                        if (key != null)
                        {
                            // 尝试读取 InstallPath 或 InstallLocation
                            var installPath = key.GetValue("InstallPath") as string ??
                                            key.GetValue("InstallLocation") as string ??
                                            key.GetValue("Path") as string;

                            if (!string.IsNullOrEmpty(installPath) && Directory.Exists(installPath))
                            {
                                // 构造 parametric.exe 路径
                                var exePath = Path.Combine(installPath, "Parametric", "bin", "parametric.exe");
                                if (File.Exists(exePath))
                                {
                                    return exePath;
                                }

                                // 如果 installPath 已经是 Parametric 目录
                                exePath = Path.Combine(installPath, "bin", "parametric.exe");
                                if (File.Exists(exePath))
                                {
                                    return exePath;
                                }
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    // 忽略注册表读取错误，继续尝试其他路径
                    System.Diagnostics.Debug.WriteLine($"读取注册表键 {baseKey} 失败: {ex.Message}");
                }
            }

            // 如果注册表中未找到，尝试从卸载信息中查找
            try
            {
                using (var uninstallKey = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall"))
                {
                    if (uninstallKey != null)
                    {
                        foreach (var subKeyName in uninstallKey.GetSubKeyNames())
                        {
                            using (var subKey = uninstallKey.OpenSubKey(subKeyName))
                            {
                                if (subKey != null)
                                {
                                    var displayName = subKey.GetValue("DisplayName") as string;
                                    if (displayName != null && displayName.Contains("Creo") && displayName.Contains("Parametric"))
                                    {
                                        var installLocation = subKey.GetValue("InstallLocation") as string;
                                        if (!string.IsNullOrEmpty(installLocation) && Directory.Exists(installLocation))
                                        {
                                            var exePath = Path.Combine(installLocation, "Parametric", "bin", "parametric.exe");
                                            if (File.Exists(exePath))
                                            {
                                                return exePath;
                                            }

                                            exePath = Path.Combine(installLocation, "bin", "parametric.exe");
                                            if (File.Exists(exePath))
                                            {
                                                return exePath;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"从卸载信息读取失败: {ex.Message}");
            }

            // 如果注册表中都未找到，尝试常见的默认安装路径
            string[] defaultPaths = new[]
            {
                Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "PTC"),
                Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86), "PTC")
            };

            foreach (var ptcBase in defaultPaths)
            {
                if (Directory.Exists(ptcBase))
                {
                    // 查找所有 Creo 版本目录
                    var creoDirs = Directory.GetDirectories(ptcBase, "Creo*");
                    foreach (var creoDir in creoDirs)
                    {
                        var exePath = Path.Combine(creoDir, "Parametric", "bin", "parametric.exe");
                        if (File.Exists(exePath))
                        {
                            return exePath;
                        }
                    }
                }
            }

            // 如果都未找到，返回 null
            return null;
        }

        /// <summary>
        /// 结构体传参
        /// </summary>
        private void TestAddPartByParams()
        {
            var p = new PartParams
            {
                Length = double.Parse(textLength.Text),
                Width = double.Parse(textWidth.Text),
                Height = double.Parse(textHeight.Text),
                DraftAngle = double.Parse(textDraftAngle.Text),
                FilletRadius = double.Parse(textFilletRadius.Text)
            };

            var partResult = CreatePart(wrapperPtr, ref p);

            MessageBox.Show(partResult ? "模型生成成功" : "生成失败");
        }

        /// <summary>
        /// json传参
        /// </summary>
        private void TestAddPartByJson()
        {
            var partData = new CreoData
            {
                Length = double.Parse(textLength.Text),
                Width = double.Parse(textWidth.Text),
                Height = double.Parse(textHeight.Text),
                DraftAngle = double.Parse(textDraftAngle.Text),
                FilletRadius = double.Parse(textFilletRadius.Text)
            };
            var json = JsonConvert.SerializeObject(partData);
            var jsonResult = CreatePartFromJson(wrapperPtr, json);

            MessageBox.Show(jsonResult ? "模型生成成功" : "生成失败");
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(creoPath))
            {
                MessageBox.Show("未找到 Creo Parametric 安装路径！\n请检查 Creo 是否已正确安装。",
                    "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            bool ret = InitCreo(wrapperPtr, creoPath);
            if (!ret)
            {
                MessageBox.Show($"Creo 启动失败！\n路径: {creoPath}",
                    "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                // 先关闭 Creo（如果正在运行）
                if (wrapperPtr != IntPtr.Zero)
                {
                    try
                    {
                        CloseCreo(wrapperPtr);
                    }
                    catch (Exception ex)
                    {
                        // 记录错误但不阻止关闭
                        System.Diagnostics.Debug.WriteLine($"关闭 Creo 时出错: {ex.Message}");
                    }
                }
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"FormClosing 错误: {ex.Message}");
            }
            finally
            {
                // 确保释放 wrapper 对象
                if (wrapperPtr != IntPtr.Zero)
                {
                    try
                    {
                        Wrapper_Delete(wrapperPtr);
                    }
                    catch (Exception ex)
                    {
                        System.Diagnostics.Debug.WriteLine($"删除 Wrapper 时出错: {ex.Message}");
                    }
                    finally
                    {
                        wrapperPtr = IntPtr.Zero;
                    }
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            TestAddPartByParams();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            TestAddPartByJson();
        }
    }
}
