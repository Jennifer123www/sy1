/**
* 作者：王秀杰
* 日期：2018/5/20
* 版本：3
* 功能：微信小程序“跳一跳”的辅助程序
*/
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JLabel;
import java.awt.BorderLayout;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Skip 
{
	private JFrame frame;				//窗体
	private JLabel lblNewLabel;			//用于显示图片的Label
	private BufferedImage image;		//手机截屏
	private int skipTime = 0;			//跳跃次数
	private int x = 0,y = 0;            //坐标定位
	private double t = 2.05;		    //按键时间 = distance 
	/**
	 * Launch the application.主调函数
	 */
	public static void main(String[] args)     //主调函数
	{
		EventQueue.invokeLater(new Runnable() 
		{
			public void run() 
			{
				try 
				{
					Skip window = new Skip();
					window.frame.setVisible(true);
				} 
				catch (Exception e)            //异常处理机制
				{
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Skip() 
	{
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() 
	{
		image = Control.getScreen();         //引用Control类的getScreen方法
		Control.getFoot(image);
		Control.getTarget(image);
		ImageIcon imageIcon = new ImageIcon(image);
		
		frame = new JFrame();
		frame.setBounds(100, 0, imageIcon.getIconWidth(), imageIcon.getIconHeight());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		lblNewLabel = new JLabel("手机屏幕");
		lblNewLabel.addMouseListener(new MouseAdapter() 
		{
			@Override
			public void mouseClicked(MouseEvent e) 
			{
				Thread skip = new Thread(new SkipRun());
				skip.start();
			}
		});
		lblNewLabel.setIcon(imageIcon);
		frame.getContentPane().add(lblNewLabel, BorderLayout.CENTER);
	}

	protected void skip() 
	{
		double distance = Control.getDistance(image);
		System.out.println(distance);
		Control.mouseon((int)(distance * t));
		try 
		{
			ImageIO.write(image, "png", new File("debug" + skipTime++ + ".png"));
		} 
		catch (IOException e)                      //异常处理机制
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	class SkipRun implements Runnable{
		public void run() 
		{
			// TODO Auto-generated method stub
			while(true) 
			{
				skip();
				try 
				{
					Thread.sleep(2000);
				} 
				catch (InterruptedException e1) //对异常的处理方法
				{
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				image = Control.getScreen();
				lblNewLabel.setIcon(new ImageIcon(image));
			}
		}
	}
}
