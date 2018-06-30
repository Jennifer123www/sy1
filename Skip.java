/**
* ���ߣ������
* ���ڣ�2018/5/20
* �汾��3
* ���ܣ�΢��С������һ�����ĸ�������
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
	private JFrame frame;				//����
	private JLabel lblNewLabel;			//������ʾͼƬ��Label
	private BufferedImage image;		//�ֻ�����
	private int skipTime = 0;			//��Ծ����
	private int x = 0,y = 0;            //���궨λ
	private double t = 2.05;		    //����ʱ�� = distance 
	/**
	 * Launch the application.��������
	 */
	public static void main(String[] args)     //��������
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
				catch (Exception e)            //�쳣�������
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
		image = Control.getScreen();         //����Control���getScreen����
		Control.getFoot(image);
		Control.getTarget(image);
		ImageIcon imageIcon = new ImageIcon(image);
		
		frame = new JFrame();
		frame.setBounds(100, 0, imageIcon.getIconWidth(), imageIcon.getIconHeight());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		lblNewLabel = new JLabel("�ֻ���Ļ");
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
		catch (IOException e)                      //�쳣�������
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
				catch (InterruptedException e1) //���쳣�Ĵ�����
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
