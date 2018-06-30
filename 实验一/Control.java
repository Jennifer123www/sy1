/**
* 作者：王秀杰
* 日期：2018/5/20
* 版本：3
* 功能：微信小程序“跳一跳”的辅助程序
*/
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.time.Year;
import javax.imageio.ImageIO;

public class Control 
{
	private static int footX = 0, footY = 0;		//小人底部坐标
	private static int targetX = 0,targetY = 0;		//目标方块中心坐标
	//获取截屏
	public static BufferedImage getScreen()
	{
		//截屏
		try 
		{
			//手机截屏，存储到SD卡
			Process process = Runtime.getRuntime().exec("adb shell screencap /sdcard/screen.png");
			process.waitFor();
			//将截图传到电脑，以便接下来的分析
			process = Runtime.getRuntime().exec("adb pull /sdcard/screen.png screen.png");
			process.waitFor();
		} 
		catch (IOException | InterruptedException e) 
		{
			//异常处理
			e.printStackTrace();
		}
		//加载文件
		File file = new File("screen.png");
		if (file == null || !file.exists()) 
		{
			System.out.println("获取截屏失败");
			return null;
		}
		
		//加载图片
		BufferedImage image = null;
		try 
		{
			image = ImageIO.read(file);
		} 
		catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return image;
	}
	
	//长按屏幕
	public static void mouseon(int time) 
	{
		try 
		{
			Runtime.getRuntime().exec("adb shell input swipe 200 200 200 200 " + time);
		} 
		catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static double getDistance (BufferedImage image) 
	{
		getFoot(image);
		getTarget(image);
		return Math.sqrt((footX - targetX) * (footX - targetX) + (footY - targetY) * (footY - targetY));
	}
	
	public static void getFoot(BufferedImage image)
	{
//		BufferedImage image = getScreen();		//屏幕截图
		Color footColor = new Color(54,60,102);		//小人底部颜色
		int top = (int)(image.getHeight() * 0.5);		//扫描范围顶部
		int bottom = (int) (image.getHeight() * 0.7);	//扫描范围底部（X）
		/*
		 * 自底向上扫描小人脚下位置
		 */
		for(int i = bottom;i > top;i--)
		{
			for(int j = 0;j < image.getWidth();j++)
			{
				if(Math.abs(image.getRGB(j, i) - footColor.getRGB()) < 200) {
					footX = j;
					footY = i - 10;
					i = top;		//结束外层循环
					System.out.println("footX:" + footX + "," + "footY:" + footY);
					break;
				}
			}
		}
		Graphics g = image.getGraphics();
		g.setColor(Color.BLUE);
		g.fillRect(footX - 5, footY - 5, 10, 10);
	}
	
	public static void getTarget(BufferedImage image) 
	{
		int top = (int)(image.getHeight() * 0.35);			//扫描范围顶部
		int bottom = (int)(image.getHeight() * 0.48);		//扫描范围底部
		Color headColor = new Color(56, 54, 71);
		/*
		 * 自顶向下扫描目标方块顶端位置
		 */
		for(int i = top;i < bottom;i++)
		{
			Color bgColor = new Color(image.getRGB(10, i));		//取背景色
			{
				if (j >= footX - 30 && j <= footX + 30) 
				{
					continue;
				}
				Color color = new Color(image.getRGB(j, i));
				int t = 0;
				t = Math.abs(bgColor.getRGB() - color.getRGB());

				//判断与背景色不同但不是小人头
				if ((t > 200000))// && !(Math.abs(headColor.getRGB() - color.getRGB()) < 8200000))
				{
					targetX = j;
					targetY = i;
					i = bottom;			//结束外层循环
					System.out.println("t=" + t);
					break;
				}
			}
		}
		
		int x = targetX;		//行扫描起始坐标
		int y = targetY;		//直径所在行（y坐标）
		int flag = 0;			//不满足条件标志
		for(int i = y + 1;i < y + 101 && flag < 8;i++)
		{
			System.out.print("i = " + i);
			for(int j = x;j < image.getWidth();j++)
			{
				Color bgColor = new Color(image.getRGB(image.getWidth() - 10, i));		//鍙栬儗鏅壊
				Color color = new Color(image.getRGB(j, i));
				if (( Math.abs(bgColor.getRGB() - color.getRGB())) <= 703400) {
					
					System.out.println("j = " + j);
					
					if (j >= x) {
						x = j;
						targetY = i;
						flag = 0;
					}
					else {
						flag++;
						System.out.println("flag=" + flag);
					}
					break;
				}
			}
		}
		targetY = targetY - flag;
		System.out.println("targetX:" + targetX + "," + "targetY:" + targetY);
		Graphics g = image.getGraphics();
		g.setColor(Color.RED);
		g.fillRect(targetX - 5, targetY - 5, 10, 10);
		g.drawLine(footX - 30,0,footX - 30,image.getHeight());
		g.drawLine(footX + 30,0,footX + 30,image.getHeight());
	}
}
