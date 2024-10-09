Action()
{
	
	lr_start_transaction("UC3_BuyTicket");

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

	lr_think_time(11);

	lr_start_transaction("open_flights");
	
	web_reg_save_param_ex("ParamName=City","LB=option value=\"","RB=\"","Ordinal=ALL",LAST);

	web_reg_find("Text=\<td align\=\"left\"\>Departure City :\</td> \<td\>\<select name\=\"depart\" \>",LAST);
	

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("open_flights",LR_AUTO);

	lr_start_transaction("search");
	
	web_reg_save_param_ex("ParamName=outboundFlight","LB=outboundFlight\" value\=\"","RB=\"","Ordinal=ALL",LAST);
	
	lr_save_string(lr_paramarr_random("City"),"DepartureCity");
	do {
    	lr_save_string(lr_paramarr_random("City"),"ArrivalCity");
	} while (strcmp(lr_eval_string("{DepartureCity}"), lr_eval_string("{ArrivalCity}")) == 0);
	
	web_reg_find("Text=Flight departing from <B>{DepartureCity}</B> to <B>{ArrivalCity}</B> on <B>{departDate}</B>",LAST);

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	lr_think_time(24);

	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={DepartureCity}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={ArrivalCity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={Preference}", ENDITEM, 
		"Name=seatType", "Value={Type}", ENDITEM, 
		"Name=findFlights.x", "Value=75", ENDITEM, 
		"Name=findFlights.y", "Value=13", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

	lr_end_transaction("search",LR_AUTO);


	lr_think_time(20);

	lr_start_transaction("select_flight");
	
	lr_save_string(lr_paramarr_random("outboundFlight"),"Flight");
		web_reg_find("Text=<b>Payment Details</font></b>",LAST);

	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={Flight}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={Preference}", ENDITEM, 
		"Name=seatPref", "Value={Type}", ENDITEM, 
		"Name=reserveFlights.x", "Value=41", ENDITEM, 
		"Name=reserveFlights.y", "Value=5", ENDITEM, 
		LAST);

	lr_end_transaction("select_flight",LR_AUTO);

	web_revert_auto_header("Origin");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(23);
	
	lr_start_transaction("booking");
	
	web_reg_find("Text=Thank you for booking through Web Tours.",LAST);

	web_submit_data("reservations.pl_3", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={FirstName}", ENDITEM, 
		"Name=lastName", "Value={LastName}", ENDITEM, 
		"Name=address1", "Value={Street}", ENDITEM, 
		"Name=address2", "Value={City}", ENDITEM, 
		"Name=pass1", "Value={FirstName} {LastName}", ENDITEM, 
		"Name=creditCard", "Value={Card}", ENDITEM, 
		"Name=expDate", "Value={ExpCard}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value={Type}", ENDITEM, 
		"Name=seatPref", "Value={Preference}", ENDITEM, 
		"Name=outboundFlight", "Value={Flight}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=52", ENDITEM, 
		"Name=buyFlights.y", "Value=3", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);

	lr_end_transaction("booking",LR_AUTO);

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
	lr_end_transaction("UC3_BuyTicket",LR_AUTO);
	
	return 0;
}