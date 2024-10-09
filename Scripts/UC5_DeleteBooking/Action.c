Action()
{
	int i;
	lr_start_transaction("UC5_DeleteBooking");
	lr_start_transaction("open_web_tours");

	web_set_sockets_option("SSL_VERSION", "AUTO");

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

	lr_start_transaction("login");
	
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Priority", 
		"u=4");

	lr_think_time(14);

	web_submit_data("login.pl", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value={usSession}", ENDITEM, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=login.x", "Value=54", ENDITEM, 
		"Name=login.y", "Value=13", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("open_itinerary");
	
	web_reg_find("Text=<b>Itinerary</font></b>",LAST);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("open_itinerary",LR_AUTO);

	lr_think_time(9);
	
	lr_start_transaction("delete");
	
	 lr_save_string("", "c_buffer");

    for (i=1;i<=atoi(lr_eval_string("{c_flightids_count}"));i++)
    {
    	lr_save_string(lr_paramarr_random("c_cgifields"),"c_rand");

		lr_param_sprintf("c_buffer", "%s%d=on&", lr_eval_string("{c_buffer}"), atoi(lr_eval_string("{c_rand}")));
        lr_param_sprintf("c_buffer","%sflightID=%s&",lr_eval_string("{c_buffer}"),lr_paramarr_idx("c_flightids",i));

        lr_param_sprintf("c_buffer","%s.cgifields=%s&",lr_eval_string("{c_buffer}"),lr_paramarr_idx("c_cgifields",i));
    }


    lr_save_string(lr_eval_string("{c_buffer}removeFlights.x=57&removeFlights.y=10&"), "c_wcr");

    lr_save_string(lr_eval_string(lr_eval_string("{c_flightids_{c_flightids_count}}")),"c_cancelflight");


    web_reg_find("Text={c_cancelflight}", "Fail=Found", LAST);



	web_add_header("Origin", 
		"http://localhost:1080");

	web_custom_request("itinerary.pl_2",
    "URL=http://localhost:1080/cgi-bin/itinerary.pl",
    "Method=POST",
    "Resource=0",
    "RecContentType=text/html",
    "Referer=http://localhost:1080/cgi-bin/itinerary.pl",
    "Snapshot=t23.inf",
    "Mode=HTTP",
    "Body={c_wcr}",
    LAST);

	lr_end_transaction("delete",LR_AUTO);

	lr_think_time(5);

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
	
	lr_end_transaction("UC5_DeleteBooking",LR_AUTO);

	return 0;
}