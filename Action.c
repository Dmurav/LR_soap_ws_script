char *replaceWord(const char *s, const char *oldW, const char *newW) 
{ 
    char *result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
  
    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) 
    { 
        if (strstr(&s[i], oldW) == &s[i]) 
        { 
            cnt++; 
  
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
  
    // Making new string of enough length 
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) 
    { 
        // compare the substring with the result 
        if (strstr(s, oldW) == s) 
        { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
}
	
Action()
{
	/*
	web_service_call( "StepName=LatLonListCityNames_101",
		"SOAPMethod=ndfdXML|ndfdXMLPort|LatLonListCityNames",
		"ResponseParam=response",
		"Service=ndfdXML",
		"ExpectedResponse=SoapResult",
		"Snapshot=t1580731582.inf",
		BEGIN_ARGUMENTS,
		"displayLevel=1",
		END_ARGUMENTS,
		BEGIN_RESULT,
		"listCityNamesOut=Param_listCityNamesOut",
		END_RESULT,
		LAST);
	*/
	
	int i;
	char *res;
	int len = 0;
	char *res_copy;
	char* old1 = "&lt;";
	char* new1 = "<";
	char* old2 = "&gt;";
	char* new2 = ">";
	char *replaced;

	web_service_call( "StepName=NDFDgen_101",
		"SOAPMethod=ndfdXML|ndfdXMLPort|NDFDgen",
		"ResponseParam=response",
		"Service=ndfdXML",
		"ExpectedResponse=SoapResult",
		"Snapshot=t1580741915.inf",
		BEGIN_ARGUMENTS,
		"latitude={latitude}",
		"longitude={longitude}",
		"product=time-series",
		"startTime=2020-02-07T11:00",
		"endTime=2020-02-07T12:00",
		"Unit=",
		"xml:weatherParameters="
			"<weatherParameters>"
				"<maxt>TRUE</maxt>"
				"<mint>TRUE</mint>"
				"<temp></temp>"
				"<dew>TRUE</dew>"
				"<pop12></pop12>"
				"<qpf></qpf>"
				"<sky></sky>"
				"<snow></snow>"
				"<wspd>TRUE</wspd>"
				"<wdir></wdir>"
				"<wx></wx>"
				"<waveh></waveh>"
				"<icons></icons>"
				"<rh>TRUE</rh>"
				"<appt></appt>"
				"<incw34></incw34>"
				"<incw50></incw50>"
				"<incw64></incw64>"
				"<cumw34></cumw34>"
				"<cumw50></cumw50>"
				"<cumw64></cumw64>"
				"<critfireo></critfireo>"
				"<dryfireo></dryfireo>"
				"<conhazo></conhazo>"
				"<ptornado></ptornado>"
				"<phail></phail>"
				"<ptstmwinds></ptstmwinds>"
				"<pxtornado></pxtornado>"
				"<pxhail></pxhail>"
				"<pxtstmwinds></pxtstmwinds>"
				"<ptotsvrtstm></ptotsvrtstm>"
				"<pxtotsvrtstm></pxtotsvrtstm>"
				"<tmpabv14d></tmpabv14d>"
				"<tmpblw14d></tmpblw14d>"
				"<tmpabv30d></tmpabv30d>"
				"<tmpblw30d></tmpblw30d>"
				"<tmpabv90d></tmpabv90d>"
				"<tmpblw90d></tmpblw90d>"
				"<prcpabv14d></prcpabv14d>"
				"<prcpblw14d></prcpblw14d>"
				"<prcpabv30d></prcpabv30d>"
				"<prcpblw30d></prcpblw30d>"
				"<prcpabv90d></prcpabv90d>"
				"<prcpblw90d></prcpblw90d>"
				"<precipa_r></precipa_r>"
				"<sky_r></sky_r>"
				"<td_r></td_r>"
				"<temp_r></temp_r>"
				"<wdir_r></wdir_r>"
				"<wspd_r></wspd_r>"
				"<wwa></wwa>"
				"<tstmprb></tstmprb>"
				"<tstmcat></tstmcat>"
				"<wgust></wgust>"
				"<iceaccum></iceaccum>"
				"<maxrh></maxrh>"
				"<minrh></minrh>"
			"</weatherParameters>",
		END_ARGUMENTS,
		BEGIN_RESULT,
		END_RESULT,
		LAST);


	lr_xml_extract("XML={response}",
	               //"Query=/Envelope/Body/NDFDgenResponse/*[local-name()='dwmlOut'][1]/text()[1]",
	               "Query=/SOAP-ENV:Envelope/SOAP-ENV:Body/ns1:NDFDgenResponse/dwmlOut/text()",
	               "XMLFragmentParam=Result",
	               LAST);
	
	
	res = lr_eval_string("{Result}");
	//res_copy = lr_eval_string("{Result}");
	//lr_output_message(lr_eval_string("Extracted: {Result}"));
	
	replaced = replaceWord(res, old1, new1);
	replaced = replaceWord(replaced, old2, new2);
	//lr_output_message(old1);
	//lr_output_message(new1);
	//lr_output_message(replaced);
	
	lr_save_string(replaced, "AnotherResult");
	
	lr_xml_extract("XML={AnotherResult}",
	               "Query=/dwml/data/parameters/temperature/value/text()",
	               "XMLFragmentParam=maxTemp",
	               LAST);
	
	lr_xml_extract("XML={AnotherResult}",
	               "Query=/dwml/data/parameters/humidity[1]/value/text()",
	               "XMLFragmentParam=maxHumidity",
	               LAST);
	
	lr_output_message(lr_eval_string("maxTemp: {maxTemp}"));
	lr_output_message(lr_eval_string("maxHumidity: {maxHumidity}"));
	
 	return 0;
}
