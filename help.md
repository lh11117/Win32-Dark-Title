# 在python中使用
请先[下载dll](https://github.com/lh11117/Win32-Dark-Title/releases/tag/1.0)，以及确保python版本为32位
<br><br><br>
在python中，你可以通过以下代码使用dll
<code>
import ctypes
dll = ctypes.cdll.LoadLibrary('./win32_dark_title_dll.dll')   #请将dll放置于python代码同目录
dll.set_dark_title(hwnd)   #设置深色标题栏
dll.set_light_title(hwnd)  #设置浅色色标题栏</code>
<br>
其中，hwnd是窗口句柄。
<br><br>
在python tkinter中，可以通过以下代码获取窗口hwnd：
<br>
<code>hwnd = int(window.frame(),16)   #window是tkinte的窗口对象</code>
<br><br>
那如何判断是否为深色模式呢？<br>运行<code>dll.is_dark()</code>后，会返回一个数字。
<br>
如下表显示：
<br>
<table border="1">
<tr>
<td>0</td>
<td>深色模式</td>
</tr>
<tr>
<td>1</td>
<td>浅色模式</td>
</tr>
<tr>
<td>-1</td>
<td>获取失败</td>
</tr>
</table>
<br><br>
这个代码只能修改标题栏颜色，<code>不能修改窗口背景色和相关窗口主题</code>，需要自行ui库使用相关函数！
