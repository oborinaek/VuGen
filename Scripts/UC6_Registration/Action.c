#include "rand.c"
Action()
{	
	char login[10]; 
    char password[10]; 
    char FirstName[10]; 
    char LastName[10];
    char Street[17]; 
    char City[17]; 

    generate_random_string(login, 9); 
    generate_random_string(password, 9); 
    generate_random_string(FirstName, 9); 
    generate_random_string(LastName, 9);
    generate_random_string(Street, 16); 
    generate_random_string(City, 16);

    lr_save_string(login, "login");
    lr_save_string(password, "password");
    lr_save_string(FirstName, "Firstname");
    lr_save_string(LastName, "LastName");
    lr_save_string(Street, "Street");
    lr_save_string(City, "City");
    
    lr_start_transaction("UC6_Register");
    
    web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_header("Priority", "u=2");
    
    lr_start_transaction("open_web_tours");

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_auto_header("Priority", 
		"u=0, i");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_reg_save_param_ex("ParamName=usSession", "LB=userSession\" value\=\"", "RB=\"", LAST);
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	
	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	web_websocket_send("ID=1", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1728403128973\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 1 received buffer WebSocketReceive0*/

	lr_end_transaction("open_web_tours",LR_AUTO);

	lr_start_transaction("sign_up");
	
	web_reg_find("Text=First time registering? Please complete the form below.",LAST);

	web_add_auto_header("Priority", 
		"u=4");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	lr_think_time(12);

	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("sign_up",LR_AUTO);

	lr_start_transaction("registration");

	web_add_auto_header("Origin", 
		"http://localhost:1080");
	
	web_reg_find("Text=Thank you, <b>{login}</b>, for registering and welcome to the Web Tours family.",LAST);

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(37);

	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value={Firstname}", ENDITEM, 
		"Name=lastName", "Value={LastName}", ENDITEM, 
		"Name=address1", "Value={Street}", ENDITEM, 
		"Name=address2", "Value={City}", ENDITEM, 
		"Name=register.x", "Value=53", ENDITEM, 
		"Name=register.y", "Value=13", ENDITEM, 
		LAST);

	lr_end_transaction("registration",LR_AUTO);

	lr_start_transaction("login_reg");
	
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",LAST);

	web_revert_auto_header("Origin");

	lr_think_time(9);

	web_url("button_next.gif", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("login_reg",LR_AUTO);

	lr_think_time(6);

	lr_start_transaction("logout");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("UC6_Register",LR_AUTO);

	return 0;
}