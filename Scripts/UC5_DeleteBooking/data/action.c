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

	lr_end_transaction("1_transaction",LR_AUTO);

	web_websocket_send("ID=1", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1728485829053\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 1 received buffer WebSocketReceive0*/

	lr_start_transaction("2_transaction");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Priority", 
		"u=4");

	web_submit_data("login.pl", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value=140015.242203321HcAcADtpAcAiDDDDtDcVcpcAtVcf", ENDITEM, 
		"Name=username", "Value=mickeyMouse", ENDITEM, 
		"Name=password", "Value=cheese123", ENDITEM, 
		"Name=login.x", "Value=73", ENDITEM, 
		"Name=login.y", "Value=8", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);

	lr_end_transaction("2_transaction",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("3_transaction");

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("3_transaction",LR_AUTO);

	lr_start_transaction("4_transaction");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_submit_data("itinerary.pl", 
		"Action=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=flightID", "Value=1280178236-7875-MM", ENDITEM, 
		"Name=2", "Value=on", ENDITEM, 
		"Name=flightID", "Value=128021511-1600-MM", ENDITEM, 
		"Name=removeFlights.x", "Value=51", ENDITEM, 
		"Name=removeFlights.y", "Value=7", ENDITEM, 
		"Name=.cgifields", "Value=1", ENDITEM, 
		"Name=.cgifields", "Value=2", ENDITEM, 
		LAST);

	lr_end_transaction("4_transaction",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("5_transaction");

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("5_transaction",LR_AUTO);

	return 0;
}