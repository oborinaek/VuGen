Action()
{

	lr_start_transaction("1_transaction");

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Priority", 
		"u=0, i");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

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
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1728488880917\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 1 received buffer WebSocketReceive0*/

	lr_end_transaction("1_transaction",LR_AUTO);

	lr_start_transaction("2_transaction");

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

	lr_end_transaction("2_transaction",LR_AUTO);

	lr_start_transaction("3_transaction");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(37);

	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=user1", ENDITEM, 
		"Name=password", "Value=1234", ENDITEM, 
		"Name=passwordConfirm", "Value=1234", ENDITEM, 
		"Name=firstName", "Value=Lena", ENDITEM, 
		"Name=lastName", "Value=Obor", ENDITEM, 
		"Name=address1", "Value=Street1", ENDITEM, 
		"Name=address2", "Value=London", ENDITEM, 
		"Name=register.x", "Value=81", ENDITEM, 
		"Name=register.y", "Value=3", ENDITEM, 
		LAST);

	lr_think_time(15);

	web_submit_data("login.pl_3", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=user100102", ENDITEM, 
		"Name=password", "Value=1234", ENDITEM, 
		"Name=passwordConfirm", "Value=1234", ENDITEM, 
		"Name=firstName", "Value=Lena", ENDITEM, 
		"Name=lastName", "Value=Obor", ENDITEM, 
		"Name=address1", "Value=Street1", ENDITEM, 
		"Name=address2", "Value=London", ENDITEM, 
		"Name=register.x", "Value=53", ENDITEM, 
		"Name=register.y", "Value=13", ENDITEM, 
		LAST);

	lr_end_transaction("3_transaction",LR_AUTO);

	lr_start_transaction("4_transaction");

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

	lr_end_transaction("4_transaction",LR_AUTO);

	lr_think_time(6);

	lr_start_transaction("5_transaction");

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("5_transaction",LR_AUTO);

	return 0;
}