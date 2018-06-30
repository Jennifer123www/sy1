/**
* ���ߣ������
* ���ڣ�2018/5/20
* �汾��3
* ���ܣ�΢��С������һ�����ĸ�������
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
	private static int footX = 0, footY = 0;		//С�˵ײ�����
	private static int targetX = 0,targetY = 0;		//Ŀ�귽����������
	//��ȡ����
	public static BufferedImage getScreen()
	{
		//����
		try 
		{
			//�ֻ��������洢��SD��
			Process process = Runtime.getRuntime().exec("adb shell screencap /sdcard/screen.png");
			process.waitFor();
			//����ͼ�������ԣ��Ա�������ķ���
			process = Runtime.getRuntime().exec("adb pull /sdcard/screen.png screen.png");
			process.waitFor();
		} 
		catch (IOException | InterruptedException e) 
		{
			//�쳣����
			e.printStackTrace();
		}
		//�����ļ�
		File file = new File("screen.png");
		if (file == null || !file.exists()) 
		{
			System.out.println("��ȡ����ʧ��");
			return null;
		}
		
		//����ͼƬ
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
	
	//������Ļ
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
//		BufferedImage image = getScreen();		//��Ļ��ͼ
		Color footColor = new Color(54,60,102);		//С�˵ײ���ɫ
		int top = (int)(image.getHeight() * 0.5);		//ɨ�跶Χ����
		int bottom = (int) (image.getHeight() * 0.7);	//ɨ�跶Χ�ײ���X��
		/*
		 * �Ե�����ɨ��С�˽���λ��
		 */
		for(int i = bottom;i > top;i--)
		{
			for(int j = 0;j < image.getWidth();j++)
			{
				if(Math.abs(image.getRGB(j, i) - footColor.getRGB()) < 200) {
					footX = j;
					footY = i - 10;
					i = top;		//�������ѭ��
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
		int top = (int)(image.getHeight() * 0.35);			//ɨ�跶Χ����
		int bottom = (int)(image.getHeight() * 0.48);		//ɨ�跶Χ�ײ�
		Color headColor = new Color(56, 54, 71);
		/*
		 * �Զ�����ɨ��Ŀ�귽�鶥��λ��
		 */
		for(int i = top;i < bottom;i++)
		{
			Color bgColor = new Color(image.getRGB(10, i));		//ȡ����ɫ
			{
				if (j >= footX - 30 && j <= footX + 30) 
				{
					continue;
				}
				Color color = new Color(image.getRGB(j, i));
				int t = 0;
				t = Math.abs(bgColor.getRGB() - color.getRGB());

				//�ж��뱳��ɫ��ͬ������С��ͷ
				if ((t > 200000))// && !(Math.abs(headColor.getRGB() - color.getRGB()) < 8200000))
				{
					targetX = j;
					targetY = i;
					i = bottom;			//�������ѭ��
					System.out.println("t=" + t);
					break;
				}
			}
		}
		
		int x = targetX;		//��ɨ����ʼ����
		int y = targetY;		//ֱ�������У�y���꣩
		int flag = 0;			//������������־
		for(int i = y + 1;i < y + 101 && flag < 8;i++)
		{
			System.out.print("i = " + i);
			for(int j = x;j < image.getWidth();j++)
			{
				Color bgColor = new Color(image.getRGB(image.getWidth() - 10, i));		//取背景色
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
