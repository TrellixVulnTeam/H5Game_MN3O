package com.pwrd.binghuo;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentLinkedDeque;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletHandler;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;

public class Main {
	
	public static class Configure
	{
		public String MysqlConnectionString = "";
		public String MysqlUser = "";
		public String MysqlPswd = "";
		public int ListenPort = 8080;
		public int ThreadNum = 8;
	}
	
	/*
	 * public class SampleStatge
		{
		    public const int StartGame = 1;
		    public const int BootStage = 2;
		    public const int ConnectToServer = 3;
		    public const int CreateCharacter = 4;
		    public const int EnterScene = 5;
		}
	 */
		
	public static class ReportObject {
		public int date = 0;
		public String time = "";
		public String agent = "";
		public String userid = "";
		public String uuid = "";
		public String server = "";
		public int stage = 0;
		public int detail_stage = 0;
		public String filename = "";
		public String desc = "";
		
		public static int getDateString() {
			java.util.Date d = Calendar.getInstance().getTime();  
	        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");  
	        return Integer.parseInt(sdf.format(d));  
		}
		
		public static String getDateTimeString() {
			java.util.Date d = Calendar.getInstance().getTime();  
	        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");  
	        return sdf.format(d);  
		}
		
		public ReportObject(HttpServletRequest request) {
			this.date = getDateString();
			this.time = getDateTimeString();
			this.agent = request.getParameter("agent");
			this.userid = request.getParameter("userid");
			this.uuid = request.getParameter("uuid");
			this.server = request.getParameter("server");
			this.stage = Integer.parseInt(request.getParameter("stage"));
			this.detail_stage = Integer.parseInt(request.getParameter("detail_stage"));
			this.filename = request.getParameter("filename");
			this.desc = request.getParameter("desc");
			
			if(this.agent.length() == 0)
				this.agent = "173";
		}
		
		public static String bytesToHexString(byte[] src){   
		    StringBuilder stringBuilder = new StringBuilder("");   
		    if (src == null || src.length <= 0) {   
		        return null;   
		    }   
		    for (int i = 0; i < src.length; i++) {   
		        int v = src[i] & 0xFF;   
		        String hv = Integer.toHexString(v);   
		        if (hv.length() < 2) {   
		            stringBuilder.append(0);   
		        }   
		        stringBuilder.append(hv);   
		    }   
		    return stringBuilder.toString();   
		}   
		
		public static String md5(String str) {
			MessageDigest mdInst;
			try {
				mdInst = MessageDigest.getInstance("MD5");
				mdInst.update(str.getBytes());
				return bytesToHexString(mdInst.digest());
			} catch (NoSuchAlgorithmException e) {
				e.printStackTrace();
			}
			return "";
		}
		
		public static Boolean check(HttpServletRequest request) {
			java.util.Map<String, String[]> params = request.getParameterMap();
			
			if(!params.containsKey("userid")
					|| !params.containsKey("uuid")
					|| !params.containsKey("server")
					|| !params.containsKey("stage")
					|| !params.containsKey("sign")) {
				return false;
			}
			
			String sign = request.getParameter("sign").toLowerCase();
			String hashinput = request.getParameter("userid") + request.getParameter("uuid") 
					+ request.getParameter("server") + request.getParameter("stage") + S_Secret;
			String mysign = md5(hashinput).toLowerCase();
			
			if(!mysign.equals(sign)) {
				System.out.println("mysign=" + mysign + " sign=" + sign + " inputmd5:" + hashinput);
				return false;
			}
			
			return true;
		}
		
		public static String S_PrepareSql = "INSERT INTO report(`id`,`date`,`time`,`agent`,"
				+ "`userid`,`uuid`,`server`,`stage`,`detail_stage`,`filename`,`desc`)"
				+ " VALUES (0,?,?,?,?,?,?,?,?,?,?)";
	
		public void setValues(PreparedStatement ps) throws SQLException {
			ps.setInt(1, this.date);
			ps.setString(2, this.time);
			ps.setString(3, this.agent);
			ps.setString(4, this.userid);
			ps.setString(5, this.uuid);
			ps.setString(6, this.server);
			ps.setInt(7, this.stage);
			ps.setInt(8, this.detail_stage);
			ps.setString(9, this.filename);
			ps.setString(10, this.desc);
		}
	}
	
	public static class ReportThread extends Thread
	{
		private Connection m_connection = null;
		private ConcurrentLinkedDeque<Object> m_list = new ConcurrentLinkedDeque<Object>();
		
		public void post(Object o) {
			m_list.push(o);
		}
		@Override
		public void run() {
			try {
				while(!this.isInterrupted()) {
					this.handleReports();
					sleep(1);
				}
			} catch(Exception e) {
				e.printStackTrace();
			}
		}
		
		public void makeMysqlConnection() throws Exception {
			Class.forName("com.mysql.jdbc.Driver");
			m_connection = DriverManager.getConnection(S_Configure.MysqlConnectionString,S_Configure.MysqlUser,S_Configure.MysqlPswd);
			if(m_connection.isClosed())
				throw new Exception("connect to mysql failed");
		}
		
		private void handleReports() {
			try {
				if(m_connection == null || m_connection.isClosed()) {
					this.makeMysqlConnection();
				}
			} catch(Exception e) {
				e.printStackTrace();
				return;
			}
			
			while(m_list.size() > 0) {
				Object r = m_list.removeFirst();
				this.handleReport(r);
			}
		}
		
		private void handleReport(Object r) {
			try {
				if(r instanceof ReportObject) {
					ReportObject ro = (ReportObject)r;
					PreparedStatement ps = m_connection.prepareStatement(ReportObject.S_PrepareSql);
					ro.setValues(ps);
					ps.execute();
				}
			} catch(Exception e) {
				e.printStackTrace();
			}
		}
	}

	public static Configure S_Configure = new Configure();
	public static ReportThread[] S_Threads = null;
	public static String S_Secret = "!@#Binghuo20140618)(*";

	public static void loadConfigures() {
		File f = new File("./binghuo.conf");
		String json = "";
		String line;
		try {
			FileInputStream s = new FileInputStream(f);
			InputStreamReader reader = new InputStreamReader(s,"utf-8");
			BufferedReader bufferedreader = new BufferedReader(reader);
			while((line = bufferedreader.readLine()) != null) {
				json = json + line; 
			}
			bufferedreader.close();			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		JSONObject jsonobj = (JSONObject) JSON.parse(json);

		S_Configure.MysqlConnectionString = (String)jsonobj.get("MysqlConnectionString");
		S_Configure.MysqlUser = (String)jsonobj.get("MysqlUser");
		S_Configure.MysqlPswd = (String)jsonobj.get("MysqlPswd");
		S_Configure.ListenPort = (int)jsonobj.get("ListenPort");
		S_Configure.ThreadNum = (int)jsonobj.get("ThreadNum");
		
		S_Threads = new ReportThread[S_Configure.ThreadNum];
	}
	
	@SuppressWarnings("serial")
	public static class ReportServlet extends HttpServlet 
	{
		
		public static void sendResponse(HttpServletResponse response,Object jsonobj) throws IOException {
			String jsonstr = JSON.toJSONString(jsonobj);
			response.setContentType("text/plain;charset=utf-8");
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().println(jsonstr);
		}
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    		Map<String,Object> json = new HashMap<String,Object>(); 

    		if(!ReportObject.check(request)) {
        		json.put("ret", 1);
        		json.put("msg","invalid parameters");
        		sendResponse(response,json);
        		return;
        	}
        	
        	int index = (int) (System.currentTimeMillis() % S_Threads.length);
        	S_Threads[index].post(new ReportObject(request));
        	
    		json.put("ret", 0);
    		json.put("msg","ok");
    		sendResponse(response,json);
        }
    }
	public static void main(String[] args) throws Exception {
		
		loadConfigures();
		
		for(int i = 0; i < S_Configure.ThreadNum; ++i) {
			ReportThread thread = new ReportThread();
			thread.makeMysqlConnection();
			thread.start();
			
			S_Threads[i] = thread;
		}		
		
		ServletHandler handler = new ServletHandler();
        handler.addServletWithMapping(ReportServlet.class, "/report");

		Server server = new Server(S_Configure.ListenPort);
		server.setHandler(handler);
		server.start();
		server.join();
	}

}
