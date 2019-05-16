//package Toolmain;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Desktop;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.LayoutManager;
import java.awt.Rectangle;
import java.awt.Toolkit;
//import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Writer;
import java.net.URI;
import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.concurrent.TimeUnit;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.filechooser.FileSystemView;


public class CARGo extends JFrame implements ActionListener{
	
	JLabel label,tool;
	JButton select_button, save_button, run_button, refresh_button;
	JPanel toppanel,leftpanel,centerpanel,rightpanel,downpanel,rbpanel,btpanel;
	JTextArea text, output1;
	Boolean successful_execution;
	JFileChooser fc;
	Boolean fileSelected;

	public CARGo() {
		/*new: more panels added*/
		toppanel=new JPanel(); //panel to contain afsr tool label
		leftpanel=new JPanel(); //panel to contain input text area
	    centerpanel=new JPanel(); //panel to TDA radiobutton and text area for output
		rightpanel=new JPanel(); //panel to BUA radiobutton and text area for output
		downpanel=new JPanel(new BorderLayout()); //panel to all buttons
		rbpanel=new JPanel();
		btpanel=new JPanel();
		/*new: more panels added*/
		
		
		successful_execution=false;
		/*new:  colors are created*/
		Color button_color=new Color(60, 88, 132);//(0, 20, 40);//blue
		Color panel_color=new Color(197, 216, 247);//light blue
		Color font_color=Color.WHITE;
		Font font =new Font("Serif", Font.PLAIN, 20);
		Font font1 = new Font("Arial",Font.BOLD, 14);
		Font font2 = new Font("Serif",Font.BOLD, 16);
		
		/*new:  colors are created*/
		//Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();  
		/*new: background colors are set*/
		toppanel.setBackground(panel_color);
		leftpanel.setBackground(panel_color);
		centerpanel.setBackground(panel_color);
		rightpanel.setBackground(panel_color);
		downpanel.setBackground(panel_color);
		rbpanel.setBackground(panel_color);
		btpanel.setBackground(panel_color);
		/*new: background colors are set*/
		
		label=new JLabel("CARGo TOOL");
     	label.setFont(new Font("Serif", Font.BOLD, 36));
		label.setForeground(button_color);
		toppanel.add(label);
		toppanel.add(Box.createRigidArea(new Dimension(0, 65)));
		
		//button to load the initial goal model
		select_button=new JButton("Select");
		select_button.setFont(font);
		select_button.setBackground(button_color);
		select_button.setForeground(font_color);
		select_button.addActionListener(this);
		btpanel.add(select_button);
		
		
		//action listener for load button
		fc=new JFileChooser();
		
		select_button.addActionListener(new ActionListener() {
			String path;
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				fc.setDialogTitle("Select an input goal model");
				int result = fc.showOpenDialog(centerpanel);
				if(result == JFileChooser.APPROVE_OPTION) {
					fileSelected = true;
					 File file = fc.getSelectedFile();
                    path=file.getPath();
					 try {
				          BufferedReader input = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
				          text.read(input, "READING FILE :-)");
				        } catch (Exception e1) {
				          e1.printStackTrace();
				        }
				      }
				else {
				        System.out.println("Operation is CANCELLED :(");
				      }	
		  }
		});
		
		/*new:  one button added to modify the input text on the text area and to reflect it to the original goal.xgrl*/
		//button to modify the initial goal model and to copy it to the original goal.xgrl from where mainfunc.exe will get it
		save_button=new JButton("Save As");
		save_button.setFont(font);
		save_button.addActionListener(this);
		save_button.setBackground(button_color);
		save_button.setForeground(font_color);
		btpanel.add(save_button);
		
		fc=new JFileChooser();
		
		save_button.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e)
			{
				JFileChooser fx = new JFileChooser();			
				fx.showSaveDialog(centerpanel);
				File myfile = fx.getSelectedFile();						  

				try {
		            BufferedWriter bf = new BufferedWriter(new FileWriter(myfile));
		            bf.write(text.getText());
		            bf.flush();
		            bf.close();
		        } catch (IOException ex) {
		            ex.printStackTrace();
		        }				
			}
				});
		
		
        /*new:  one button added to modify the input text on the text area and to reflect it to the original goal.xgrl*/
        
		
		//display place for initial goal model
		//System.out.println(screenSize.width+"  "+screenSize.height);
		//text = new JTextArea(screenSize.width/54, screenSize.height/16);
		text=new JTextArea(25,40);
		text.setEditable(true);
		text.setText("Input Goal Model");
		text.setFont(font1);
		/*new: input text area made scroll-able */
		JScrollPane scroll = new JScrollPane (text);
	    leftpanel.add(scroll);
	    /*new: input text area made scroll-able */
		
		//button to run the code
		run_button=new JButton("Semantic Reconciliation and Conflict Resolution");
		run_button.setFont(font);
		run_button.setBackground(button_color);
		run_button.setForeground(font_color);
		run_button.addActionListener(this);
		btpanel.add(run_button);
		
		

		/*new: adding radiobuttons*/
		JRadioButton r1=new JRadioButton("Top Down");
		r1.setFont(font2);
		r1.setForeground(button_color);
		r1.setBackground(panel_color);

		JRadioButton r2=new JRadioButton("Bottom Up");
		r2.setFont(font2);
		r2.setForeground(button_color);
		r2.setBackground(panel_color);
		
		ButtonGroup bg=new ButtonGroup();    
		bg.add(r1);bg.add(r2);
		rbpanel.add(r1);
		rbpanel.add(r2);
	
		/*new: adding radiobuttons*/
		
		//button to display the output
				refresh_button=new JButton("Refresh");
				refresh_button.setFont(font);
				refresh_button.setBackground(button_color);
				refresh_button.setForeground(font_color);
				refresh_button.addActionListener(new ActionListener() {
					
					@Override
					public void actionPerformed(ActionEvent e) {
						// TODO Auto-generated method stub
						text.setText("Input Goal Model");
						output1.setText("Output Goal Model");
	            		bg.clearSelection();
						successful_execution=false;
					}
				});
				btpanel.add(refresh_button);
				

		
		//display place for final goal model in TDA
		//System.out.println(screenSize.width/54+","+screenSize.height/16);
		//output1=new JTextArea(screenSize.width/54, screenSize.height/16);
		output1=new JTextArea(25,40);
		output1.setEditable(true);
		output1.setText("Output Goal Model");
		output1.setFont(font1);
		//rightpanel.add(Box.createRigidArea(new Dimension(0, 5))); 
		/*new: output text area made scroll-able */
		JScrollPane scroll1 = new JScrollPane (output1);
	    rightpanel.add(scroll1);
	    /* output text area made scroll-able */
		run_button.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e1) {
				// TODO Auto-generated method stub
				   Process process = null;
				   successful_execution=true;
		           int exitval=255;
		    //=================================================================       
		           File f1=new File("goal.xgrl");
		           try{
				   if(!f1.exists())
					   f1.createNewFile();
		           }
		           catch(Exception e)
		           {
		        	   e.printStackTrace();
		           }
			//===================================================================
				   /*new: Saving text in goal.xgrl*/
				   
				   BufferedWriter outFile1 = null;
				      try {
				    	  outFile1 = new BufferedWriter(new FileWriter("goal.xgrl"));
				    	  text.write(outFile1);  //write the input text to goal.xgrl file 
				    	  } catch (IOException ex) {
				         ex.printStackTrace();
				          } finally {
				         if (outFile1 != null) {
				            try {
				               outFile1.close();
				            } catch (IOException ecd) {
				               		            }
				         }
				      }
				      
				      
				      /*new: sSaving text in goal.xgrl*/
				     
				   try {
		           if(r1.isSelected()) //if TDA is selected
		        	 {	          
				          
		        	      String[] cmd= new String[]{"mainfunc1","goal.xgrl"};
		        	      ProcessBuilder probuilder= new ProcessBuilder(cmd);
		        		  process = probuilder.start();
		        		  InputStream is=process.getInputStream();
		        		  OutputStream os=process.getOutputStream();
		        		  InputStream err=process.getErrorStream();
		        		  is.close();
		        		  os.close();
		        		  err.close();
		        	      try{ exitval=process.waitFor();//normal termination returns 0
		        	      System.out.println("Exit value="+exitval);
		        	      }catch(InterruptedException e){e.printStackTrace();}
		        	 }
		           
		           else if(r2.isSelected()) //if BUA is selected
		             {	
		        	   
		        	   String[] cmd= new String[]{"mainfunc2","goal.xgrl"};
		        	      ProcessBuilder probuilder= new ProcessBuilder(cmd);
		        		  process = probuilder.start();
		        		  InputStream is=process.getInputStream();
		        		  OutputStream os=process.getOutputStream();
		        		  InputStream err=process.getErrorStream();
		        		  is.close();
		        		  os.close();
		        		  err.close();
		        	      try{exitval=process.waitFor();//normal termination returns 0
		        	      System.out.println("Exit value="+exitval);
		        	      }catch(InterruptedException e){e.printStackTrace();}
		             }  
		        
		           else //if none of them is selected
		        	   {   //showing error message in a dialog box
		        		   JOptionPane.showMessageDialog(null, "No approach is selected!!!!");
		        		   successful_execution=false; //unsuccessful execution
		        	   }
		           } catch (IOException e2) {
		               e2.printStackTrace();
		           }
				   
				   if(exitval!=0) successful_execution=false;//unsuccessful execution
				   
				   /*delete all opm files*/
				   String dir=System.getProperty("user.dir");
				    File folder = new File(dir);
	                File fList[] = folder.listFiles();
	                for (File f : fList) {
	                    if (f.getName().endsWith(".opm")) {
	                        f.delete(); 
	                    }}   
	                
	                /*delete all opm files*/
					   
	                
				   //generate output
				   /*new: After executing mainfunc.exe, output goal model will be automatically pasted to the output text area*/
		   		   if(successful_execution)  //if one of the radiobuttons is selected
		   		   {        
		   			
		           try {
		        	       File fx=fc.getSelectedFile();
				           String p=fx.getParent();
				           new File(p+"\\output").mkdir();
		        	      
				          if(r1.isSelected()){// only 1st output text area is written 
				        	 
				        	  Files.deleteIfExists(Paths.get(p+"\\output\\output_goalTDA.xgrl"));
					          Path temp = Files.move 
					        	        (Paths.get("output_goalTDA.xgrl"),  
					        	        Paths.get(p+"\\output\\output_goalTDA.xgrl")); 
					        	  
					        	        if(temp != null) 
					        	        { 
					        	            System.out.println("File renamed and moved successfully"); 
					        	        } 
					        	        else
					        	        { 
					        	        	output1.setText("Failed to move the file"); 
					        	        } 
					        	        BufferedReader input = new BufferedReader(new InputStreamReader(new FileInputStream(p.toString()+"\\output\\output_goalTDA.xgrl")));
								        output1.read(input, "READING FILE :-)");
							  
								        Files.deleteIfExists(Paths.get(p+"\\output\\AFSRlogsTDA.txt"));
								        Path temp2=Files.move 
							        	        (Paths.get("AFSRlogsTDA.txt"),  
							        	        Paths.get(p+"\\output\\AFSRlogsTDA.txt")); 					        	  
							        	        if(temp != null) 
							        	        { 
							        	            System.out.println("The Log File renamed and moved successfully"); 
							        	        } 
							        	        else
							        	        { 
							        	        	output1.setText("Log Failed to move the file"); 
							        	        } 
								          
					                  
					       }
				          else  // only 2nd output area is written
				          {
				        	  Files.deleteIfExists(Paths.get(p+"\\output\\output_goalBUA.xgrl"));
					          Path temp = Files.move 
					        	        (Paths.get("output_goalBUA.xgrl"),  
					        	        Paths.get(p+"\\output\\output_goalBUA.xgrl"));
					                  
					        	        if(temp != null) 
					        	        { 
					        	            System.out.println("File renamed and moved successfully"); 
					        	        } 
					        	        else
					        	        { 
					        	        	output1.setText("Failed to move the file"); 
					        	        } 
					        	        BufferedReader input = new BufferedReader(new InputStreamReader(new FileInputStream(p.toString()+"\\output\\output_goalBUA.xgrl")));
								        output1.read(input, "READING FILE :-)");
								        
						     Files.deleteIfExists(Paths.get(p+"\\output\\AFSRlogsBUA.txt"));  	        
							 Path temp2=Files.move 
					        	        (Paths.get("AFSRlogsBUA.txt"),  
					        	        Paths.get(p+"\\output\\AFSRlogsBUA.txt")); 					        	  
					        	        if(temp != null) 
					        	        { 
					        	            System.out.println("The Log File renamed and moved successfully"); 
					        	        } 
					        	        else
					        	        { 
					        	            output1.setText("Log Failed to move the file"); 
					        	        } 
								        
				          }			          
				          Files.delete(Paths.get("goal.xgrl"));
				          
				        } catch (Exception e12) {
				          e12.printStackTrace();
				        }
		           /*new: After executing mainfunc.exe, output goal model will be automatically pasted to the output text area*/
		   		   }
		   		   else
		   			   output1.setText("Unsuccessful Execution..Output has not been generated.. ");
		           
		           
			}});

		/*new: more panels added*/		
		this.add(toppanel,BorderLayout.PAGE_START); //adding panel to my jframe
		this.add(leftpanel,BorderLayout.LINE_START); //adding panel to my jframe
		this.add(centerpanel,BorderLayout.CENTER); //adding panel to my jframe
		this.add(rightpanel,BorderLayout.LINE_END); //adding panel to my jframe	
		downpanel.add(rbpanel,BorderLayout.PAGE_START);
		downpanel.add(btpanel,BorderLayout.PAGE_END);
		this.add(downpanel,BorderLayout.PAGE_END); //adding panel to my jframe	
		
		/*new: more panels added*/
		
		this.setVisible(true);
		/*new: window size set*/
		this.setBounds(85, 50, 1200, 600);
		this.setMaximizedBounds(new Rectangle(85, 50, 1000, 500));
		/*new: window size set*/
		//System.out.println(screenSize.width/16+"  "+screenSize.height/15+"  "+(screenSize.width-screenSize.width/8)+"  "+(screenSize.height-screenSize.height/6));
        //this.setBounds(new Rectangle(screenSize.width/16, screenSize.height/15, screenSize.width-screenSize.width/8, screenSize.height-screenSize.height/6));
        this.setResizable(false);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
public static void main(String[] args) {
	new CARGo();
}
@Override
public void actionPerformed(ActionEvent e) {
	// TODO Auto-generated method stub
	
}
}
